// original version of this file was based on: https://www.3dgep.com/multi-textured-terrain-in-opengl/#Resources
//#include "TerrainPCH.h"
#include "Terrain.h"

// Enable mutitexture blending across the terrain
#ifndef ENABLE_MULTITEXTURE
#define ENABLE_MULTITEXTURE 1
#endif

// Enable the blend constants based on the slope of the terrain
#ifndef ENABLE_SLOPE_BASED_BLEND
#define ENABLE_SLOPE_BASED_BLEND 1
#endif

#define BUFFER_OFFSET(i) ((char*)NULL + (i))

inline float GetPercentage( float value, const float min, const float max )
{
    value = glm::clamp( value, min, max );
    return ( value - min ) / ( max - min );
}

// Get's the size of the file in bytes.
inline int GetFileLength( std::istream& file )
{
    int pos = file.tellg();
    file.seekg(0, std::ios::end );
    int length = file.tellg();
    // Restore the position of the get pointer
    file.seekg(pos);

    return length;
}

inline void DeleteVertexBuffer( GLuint& vboID )
{
    if ( vboID != 0 )
    {
        glDeleteBuffersARB( 1, &vboID );
        vboID = 0;
    }
}

inline void DeleteTexture( QOpenGLTexture* texID )
{
    if ( texID != NULL )
    {
        //glDeleteTextures( 1, &texID );
        //texID = 0;
        delete texID;

    }
}

// Convert data from the char buffer to a floating point value between 0..1
// depending on the storage value of the original data
// NOTE: This only works with (LSB,MSB) data storage.
inline float GetHeightValue( const unsigned char* data, unsigned char numBytes )
{
    switch ( numBytes )
    {
    case 1:
        {
            return (unsigned char)(data[0]) / (float)0xff;
        }
        break;
    case 2:
        {
            return (unsigned short)(data[1] << 8 | data[0] ) / (float)0xffff;
        }
        break;
    case 4:
        {
            return (unsigned int)(data[3] << 24 | data[2] << 16 | data[1] << 8 | data[0] ) / (float)0xffffffff;
        }
        break;
    default:
        {
            assert(false);  // Height field with non standard pixle sizes
        }
        break;
    }

    return 0.0f;
}

Terrain::Terrain( float heightScale /* = 500.0f */, float blockScale /* = 2.0f */ )
    : m_HeightmapDimensions(0,0)
    , m_fHeightScale( heightScale )
    , m_fBlockScale( blockScale )
{
    std::cout << "TEST" << std::endl;
    // memset( m_GLTextures, 0, sizeof(m_GLTextures) );
}


Terrain::~Terrain()
{
    //Terminate();
}

void Terrain::setRoad(Road* road)
{
    m_pRoad = road;
}

void Terrain::setModels()
{
    //m_program->bind();
    m_modelToWorld = m_program->uniformLocation("modelToWorld");
    m_program->setUniformValue(m_modelToWorld, QMatrix4x4(glm::value_ptr(m_LocalToWorldMatrix)).transposed() );
    //m_program->release();

}

bool Terrain::setupDefaultMesh()
{
    return LoadHeightmap( ":/Data/Terrain/terrain0-16bbp-257x257.raw", 16, 257, 257 );

}

//bool Terrain::LoadHeightmap( QFile file, unsigned char bitsPerPixel, unsigned int width, unsigned int height )
bool Terrain::LoadHeightmap( const std::string& filename, unsigned char bitsPerPixel, unsigned int width, unsigned int height )
{
    QFile file(QString::fromStdString(filename));

    //if( !fs::exists(filename) )
    if( !file.exists() )
    {
        std::cerr << "Could not find file: " << file.fileName().toStdString() << std::endl;
        return false;
    }

    //fs::ifstream ifs;
    //ifs.open( filename, fs::ifstream::binary );
    file.open(QFile::ReadOnly);
    QByteArray byteArray = file.readAll();


    const unsigned int bytesPerPixel = bitsPerPixel / 8;
    const unsigned int expectedFileSize = ( bytesPerPixel * width * height );
    const unsigned int fileSize = file.size(); // GetFileLength( ifs );

    if ( expectedFileSize != fileSize )
    {
        std::cerr << "Expected file size [" << expectedFileSize << " bytes] differs from actual file size [" << fileSize << " bytes]" << std::endl;
        return false;
    }

    unsigned char* heightMap = (unsigned char*)byteArray.data();

    unsigned int numVerts = width * height;

    m_HeightmapDimensions = glm::uvec2(width, height);

    // Size of the terrain in world units
    float terrainWidth = ( width - 1 ) * m_fBlockScale;
    float terrainHeight = ( height - 1 ) * m_fBlockScale;

    float halfTerrainWidth = terrainWidth * 0.5f;
    float halfTerrainHeight = terrainHeight * 0.5f;

    for ( unsigned int j = 0; j < height; ++j )
    {
        for ( unsigned i = 0; i < width; ++i )
        {
            unsigned int index = ( j * width ) + i;
            assert( index * bytesPerPixel < fileSize );

            float heightValue = GetHeightValue( &heightMap[index * bytesPerPixel], bytesPerPixel );

            float S = ( i / (float)(width - 1) );
            float T = ( j / (float)(height - 1) );

            float X = ( S * terrainWidth ) - halfTerrainWidth;
            float Z = ( T * terrainHeight ) - halfTerrainHeight;

            // make a road

            float Y = heightValue * m_fHeightScale;
            if (m_pRoad != NULL)
            {
                if (m_pRoad->distanceToRoad(X,Z) < 3)
                {
                    Y = 0.5;
                }
            }

            // std::cout <<m_fHeightScale << std::endl;
            // Blend 3 textures depending on the height of the terrain
            float tex0Contribution = 1.0f - GetPercentage( heightValue, 0.0f, 0.75f );
            float tex2Contribution = 1.0f - GetPercentage( heightValue, 0.75f, 1.0f );
            //std::cout << tex0Contribution << " " << tex2Contribution << std::endl;
#if ENABLE_MULTITEXTURE
            m_PositionBuffer.push_back ( Vertex(QVector3D(X, Y, Z), QVector4D( tex0Contribution, 0, tex0Contribution, tex2Contribution ), QVector3D(1, 0, 0), QVector2D(S,T) ));
#else
            m_PositionBuffer.push_back ( Vertex(QVector3D(X, Y, Z), QVector4D( 1, 0, 0, 0 ), QVector3D(1, 0, 0), QVector2D(S,T) ));
#endif
            //std::cout << m_PositionBuffer[1000].position().x() << std::endl;

//            m_NormalBuffer[index] = glm::vec3(0);
//            m_PositionBuffer[index] = glm::vec3( X, Y, Z );
//#if ENABLE_MULTITEXTURE
//            m_ColorBuffer[index] = glm::vec4( tex0Contribution, tex0Contribution, tex0Contribution, tex2Contribution );
//#else
//            //m_ColorBuffer[index] = glm::vec4(1.0f);
//            m_ColorBuffer[index] = glm::vec3(1.0f);
//#endif
//            m_Tex0Buffer[index] = glm::vec2( S, T );
        }
    }

    std::cout << "Terrain has been loaded!" << std::endl;
    //delete [] heightMap;


    //GenerateIndexBuffer();
    if ( m_HeightmapDimensions.x < 2 || m_HeightmapDimensions.y < 2 )
    {
        // Terrain hasn't been loaded, or is of an incorrect size
        return false;
    }

    const unsigned int terrainWidthInt = m_HeightmapDimensions.x;
    const unsigned int terrainHeightInt = m_HeightmapDimensions.y;

    // 2 triangles for every quad of the terrain mesh
    const unsigned int numTriangles = ( terrainWidthInt - 1 ) * ( terrainHeightInt - 1 ) * 2;

    // 3 indices for each triangle in the terrain mesh
    m_IndexBuffer.resize( numTriangles * 3 );


    unsigned int index = 0; // Index in the index buffer
    for (unsigned int j = 0; j < (terrainHeightInt - 1); ++j )
    {
        for (unsigned int i = 0; i < (terrainWidthInt - 1); ++i )
        {
            int vertexIndex = ( j * terrainWidthInt ) + i;
            // Top triangle (T0)
            m_IndexBuffer[index++] = vertexIndex;                           // V0
            m_IndexBuffer[index++] = vertexIndex + terrainWidthInt + 1;        // V3
            m_IndexBuffer[index++] = vertexIndex + 1;                       // V1
            // Bottom triangle (T1)
            m_IndexBuffer[index++] = vertexIndex;                           // V0
            m_IndexBuffer[index++] = vertexIndex + terrainWidthInt;            // V2
            m_IndexBuffer[index++] = vertexIndex + terrainWidthInt + 1;        // V3
        }
    }


    //GenerateNormals();
    //GenerateVertexBuffers();

    // Generate Normals
    for ( unsigned int i = 0; i < m_IndexBuffer.size(); i += 3 )
    {
        QVector3D v0 = m_PositionBuffer[ m_IndexBuffer[i + 0] ].position();
        QVector3D v1 = m_PositionBuffer[ m_IndexBuffer[i + 1] ].position();
        QVector3D v2 = m_PositionBuffer[ m_IndexBuffer[i + 2] ].position();

        QVector3D normal = QVector3D::normal(v1-v0, v2-v0);

        m_PositionBuffer[ m_IndexBuffer[i + 0] ].setNormal(normal);
        m_PositionBuffer[ m_IndexBuffer[i + 1] ].setNormal(normal);
        m_PositionBuffer[ m_IndexBuffer[i + 2] ].setNormal(normal);
    }

    std::cout << "about to mesh" << std::endl;
    setupMesh();

    return true;
}



//float Terrain::GetHeightAt( const glm::vec3& position )
//{
//    float height = -FLT_MAX;
//    // Check if the terrain dimensions are valid
//    if ( m_HeightmapDimensions.x < 2 || m_HeightmapDimensions.y < 2 ) return height;

//    // Width and height of the terrain in world units
//    float terrainWidth = ( m_HeightmapDimensions.x - 1) * m_fBlockScale;
//    float terrainHeight = ( m_HeightmapDimensions.y - 1) * m_fBlockScale;
//    float halfWidth = terrainWidth * 0.5f;
//    float halfHeight = terrainHeight * 0.5f;

//    // Multiple the position by the inverse of the terrain matrix
//    // to get the position in terrain local space
//    glm::vec3 terrainPos = glm::vec3( m_InverseLocalToWorldMatrix * glm::vec4(position, 1.0f) );
//    glm::vec3 invBlockScale( 1.0f/m_fBlockScale, 0.0f, 1.0f/m_fBlockScale );

//    // Calculate an offset and scale to get the vertex indices
//    glm::vec3 offset( halfWidth, 0.0f, halfHeight );

//    // Get the 4 vertices that make up the triangle we're over
//    glm::vec3 vertexIndices = ( terrainPos + offset ) * invBlockScale;

//    int u0 = (int)floorf(vertexIndices.x);
//    int u1 = u0 + 1;
//    int v0 = (int)floorf(vertexIndices.z);
//    int v1 = v0 + 1;

//    if ( u0 >= 0 && u1 < (int)m_HeightmapDimensions.x && v0 >= 0 && v1 < (int)m_HeightmapDimensions.y )
//    {
//        glm::vec3 p00 = m_PositionBuffer[ ( v0 * m_HeightmapDimensions.x ) + u0 ];    // Top-left vertex
//        glm::vec3 p10 = m_PositionBuffer[ ( v0 * m_HeightmapDimensions.x ) + u1 ];    // Top-right vertex
//        glm::vec3 p01 = m_PositionBuffer[ ( v1 * m_HeightmapDimensions.x ) + u0 ];    // Bottom-left vertex
//        glm::vec3 p11 = m_PositionBuffer[ ( v1 * m_HeightmapDimensions.x ) + u1 ];    // Bottom-right vertex

//        // Which triangle are we over?
//        float percentU = vertexIndices.x - u0;
//        float percentV = vertexIndices.z - v0;

//        glm::vec3 dU, dV;
//        if (percentU > percentV)
//        {   // Top triangle
//            dU = p10 - p00;
//            dV = p11 - p10;
//        }
//        else
//        {   // Bottom triangle
//            dU = p11 - p01;
//            dV = p01 - p00;
//        }

//        glm::vec3 heightPos = p00 + ( dU * percentU ) + ( dV * percentV );
//        // Convert back to world-space by multiplying by the terrain's world matrix
//        heightPos = glm::vec3( m_LocalToWorldMatrix * glm::vec4(heightPos, 1) );
//        height = heightPos.y;
//    }
//    return height;
//}

//void Terrain::Render()
//{


//    glMatrixMode( GL_MODELVIEW );
//    glPushMatrix();
//    glMultMatrixf( glm::value_ptr(m_LocalToWorldMatrix) );


    //
    // Texture Stage 0
    //
    // Simply output texture0 for stage 0.
    //



//    replaces:
//    --------------------------------------------------------------
//    glActiveTextureARB( GL_TEXTURE0_ARB );
//    glMatrixMode( GL_TEXTURE );
//    glPushMatrix();
//    glScalef( 32.0f, 32.0f , 1.0f );

//    glEnable( GL_TEXTURE_2D );
//    glBindTexture( GL_TEXTURE_2D, m_GLTextures[0] );

//    glClientActiveTextureARB(GL_TEXTURE0_ARB);
//    glEnableClientState( GL_TEXTURE_COORD_ARRAY );
//    glBindBufferARB( GL_ARRAY_BUFFER_ARB, m_GLTex0Buffer );
//    glTexCoordPointer( 2, GL_FLOAT, 0, BUFFER_OFFSET(0) );
//    --------------------------------------------------------------


//#if ENABLE_MULTITEXTURE
//    // Disable lighting because it changes the color of the vertices that are
//    // used for the multitexture blending.
//    glDisable( GL_LIGHTING );

//    //
//    // Texture Stage 1
//    //
//    // Perform a linear interpolation between the output of stage 0
//    // (i.e texture0) and texture1 and use the RGB portion of the vertex's
//    // color to mix the two.
//    //
//    glActiveTextureARB(GL_TEXTURE1_ARB );
//    glMatrixMode( GL_TEXTURE );
//    glPushMatrix();
//    glScalef( 32.0f, 32.0f , 1.0f );

//    glEnable( GL_TEXTURE_2D );
//    glBindTexture( GL_TEXTURE_2D, m_GLTextures[1] );

//    glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_ARB );
//    glTexEnvi( GL_TEXTURE_ENV, GL_COMBINE_RGB_ARB, GL_INTERPOLATE_ARB );

//    glTexEnvi( GL_TEXTURE_ENV, GL_SOURCE0_RGB_ARB, GL_PREVIOUS_ARB );
//    glTexEnvi( GL_TEXTURE_ENV, GL_OPERAND0_RGB_ARB, GL_SRC_COLOR );

//    glTexEnvi( GL_TEXTURE_ENV, GL_SOURCE1_RGB_ARB, GL_TEXTURE );
//    glTexEnvi( GL_TEXTURE_ENV, GL_OPERAND1_RGB_ARB, GL_SRC_COLOR );

//    glTexEnvi( GL_TEXTURE_ENV, GL_SOURCE2_RGB_ARB, GL_PRIMARY_COLOR_ARB );
//    glTexEnvi( GL_TEXTURE_ENV, GL_OPERAND2_RGB_ARB, GL_SRC_COLOR );

//    glClientActiveTextureARB(GL_TEXTURE1_ARB);
//    glEnableClientState( GL_TEXTURE_COORD_ARRAY );
//    glBindBufferARB( GL_ARRAY_BUFFER_ARB, m_GLTex1Buffer );
//    glTexCoordPointer( 2, GL_FLOAT, 0, BUFFER_OFFSET(0) );

//    //
//    // Texture Stage 2
//    //
//    // Perform a linear interpolation between the output of stage 1
//    // (i.e texture0 mixed with texture1) and texture2 and use the ALPHA
//    // portion of the vertex's color to mix the two.
//    //
//    glActiveTextureARB( GL_TEXTURE2_ARB );
//    glMatrixMode( GL_TEXTURE );
//    glPushMatrix();
//    glScalef( 32.0f, 32.0f , 1.0f );

//    glEnable( GL_TEXTURE_2D );
//    glBindTexture( GL_TEXTURE_2D, m_GLTextures[2] );

//    glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_ARB );
//    glTexEnvi( GL_TEXTURE_ENV, GL_COMBINE_RGB_ARB, GL_INTERPOLATE_ARB );

//    glTexEnvi( GL_TEXTURE_ENV, GL_SOURCE0_RGB_ARB, GL_PREVIOUS_ARB );
//    glTexEnvi( GL_TEXTURE_ENV, GL_OPERAND0_RGB_ARB, GL_SRC_COLOR );

//    glTexEnvi( GL_TEXTURE_ENV, GL_SOURCE1_RGB_ARB, GL_TEXTURE );
//    glTexEnvi( GL_TEXTURE_ENV, GL_OPERAND1_RGB_ARB, GL_SRC_COLOR );

//    glTexEnvi( GL_TEXTURE_ENV, GL_SOURCE2_RGB_ARB, GL_PRIMARY_COLOR_ARB );
//    glTexEnvi( GL_TEXTURE_ENV, GL_OPERAND2_RGB_ARB, GL_SRC_ALPHA );

//    glClientActiveTextureARB(GL_TEXTURE2_ARB);
//    glEnableClientState( GL_TEXTURE_COORD_ARRAY );
//    glBindBufferARB( GL_ARRAY_BUFFER_ARB, m_GLTex2Buffer );
//    glTexCoordPointer( 2, GL_FLOAT, 0, BUFFER_OFFSET(0) );

//#else
//    glEnable( GL_TEXTURE );
//    glEnable( GL_LIGHTING );
//#endif


//    VAO.bind();
//    glDrawElements(GL_TRIANGLES, m_IndexBuffer.size(), GL_UNSIGNED_INT, 0);
//    VAO.release();

//    replaces
//    ----------------------------------------------------------
//    glEnableClientState( GL_VERTEX_ARRAY );
//    glEnableClientState( GL_COLOR_ARRAY );
//    glEnableClientState( GL_NORMAL_ARRAY );

//    glBindBufferARB( GL_ARRAY_BUFFER_ARB, m_GLVertexBuffer );
//    glVertexPointer( 3, GL_FLOAT, 0, BUFFER_OFFSET(0) );
//    glBindBufferARB( GL_ARRAY_BUFFER_ARB, m_GLColorBuffer );
//    glColorPointer( 4, GL_FLOAT, 0, BUFFER_OFFSET(0) );
//    glBindBufferARB( GL_ARRAY_BUFFER_ARB, m_GLNormalBuffer );
//    glNormalPointer( GL_FLOAT, 0, BUFFER_OFFSET(0) );

//    glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, m_GLIndexBuffer );
//    glDrawElements( GL_TRIANGLES, m_IndexBuffer.size(), GL_UNSIGNED_INT, BUFFER_OFFSET(0) );

//    glDisableClientState( GL_NORMAL_ARRAY );
//    glDisableClientState( GL_COLOR_ARRAY );
//    glDisableClientState( GL_VERTEX_ARRAY );
//    ----------------------------------------------------------

//#if ENABLE_MULTITEXTURE
//    glActiveTextureARB(GL_TEXTURE2_ARB);
//    glPopMatrix();
//    glDisable(GL_TEXTURE_2D);
//    glClientActiveTextureARB(GL_TEXTURE2_ARB);
//    glDisableClientState( GL_TEXTURE_COORD_ARRAY );

//    glActiveTextureARB(GL_TEXTURE1_ARB);
//    glPopMatrix();
//    glDisable(GL_TEXTURE_2D);
//    glClientActiveTextureARB(GL_TEXTURE1_ARB);
//    glDisableClientState( GL_TEXTURE_COORD_ARRAY );
//#endif

//    glActiveTextureARB(GL_TEXTURE0_ARB);
//    glPopMatrix();
//    glDisable(GL_TEXTURE_2D);
//    glClientActiveTextureARB(GL_TEXTURE0_ARB);
//    glDisableClientState( GL_TEXTURE_COORD_ARRAY );

//    glMatrixMode( GL_MODELVIEW );
//    glPopMatrix();

//#if _DEBUG
//    DebugRender();
//#endif

//}

//void Terrain::RenderNormals()
//{
//    glMatrixMode( GL_MODELVIEW );
//    glPushMatrix();
//    glMultMatrixf( glm::value_ptr(m_LocalToWorldMatrix) );

//    glPushAttrib( GL_ENABLE_BIT );
//    glDisable( GL_LIGHTING );

//    glColor3f( 1.0f, 1.0f, 0.0f );// Yellow

//    glBegin( GL_LINES );
//    {
//        for ( unsigned int i = 0; i < m_PositionBuffer.size(); ++i )
//        {
//            glm::vec3 p0 = m_PositionBuffer[i];
//            glm::vec3 p1 = ( m_PositionBuffer[i] + m_NormalBuffer[i] );

//            glVertex3fv( glm::value_ptr(p0) );
//            glVertex3fv( glm::value_ptr(p1) );
//        }
//    }
//    glEnd();

//    glPopAttrib();

//    glPopMatrix();
//}

//void Terrain::DebugRender()
//{
//    RenderNormals();
//}
