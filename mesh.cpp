#include "mesh.h"
#include <stdio.h>
#include <iostream>

Mesh::Mesh()
{
}

Mesh::~Mesh()
{

}

//Mesh::Mesh(vector<QOpenGLTexture*> textures)
//{

//}

//Mesh::Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<QOpenGLTexture*> textures)
//{
//    this->vertices = vertices;
//    this->indicies = indices;
//    m_textures = textures;
//}


void Mesh::draw()
{
  // Render using our shader
  VAO.bind();
  //glDrawElements(GL_TRIANGLES, 6336, GL_UNSIGNED_INT, 0);
  glDrawElements(GL_TRIANGLES, m_IndexBuffer.size(), GL_UNSIGNED_INT, 0);
  //glDrawArrays(GL_TRIANGLES, 0, sizeof(sg_vertexes) / sizeof(sg_vertexes[0]));
  VAO.release();


    // Draw the earth.
  //   glBindTexture( GL_TEXTURE_2D, g_EarthTexture );
  //   glUseProgram( g_TexturedDiffuseShaderProgram );

     // Set the light position to the position of the Sun.
  //   glUniform4fv( g_uniformLightPosW, 1, glm::value_ptr(modelMatrix[3]) );
  //   glUniform4fv( g_uniformLightColor, 1, glm::value_ptr(white) );
  //   glUniform4fv( g_uniformAmbient, 1, glm::value_ptr(ambient) );

     //modelMatrix = glm::rotate( glm::radians(g_fEarthRotation), glm::vec3(0,1,0) ) * glm::scale(glm::vec3(12.756f) );
  //   glm::vec4 eyePosW = glm::vec4( g_Camera.GetPosition(), 1 );
  //   mvp = g_Camera.GetProjectionMatrix() * g_Camera.GetViewMatrix() * modelMatrix;

  //   glUniformMatrix4fv( g_uniformMVP, 1, GL_FALSE, glm::value_ptr(mvp) );
  //   glUniformMatrix4fv( g_uniformModelMatrix, 1, GL_FALSE, glm::value_ptr(modelMatrix) );
  //   glUniform4fv( g_uniformEyePosW, 1, glm::value_ptr( eyePosW ) );

     // Material properties.
  //   glUniform4fv( g_uniformMaterialEmissive, 1, glm::value_ptr(black) );
  //   glUniform4fv( g_uniformMaterialDiffuse, 1, glm::value_ptr(white) );
  //   glUniform4fv( g_uniformMaterialSpecular, 1, glm::value_ptr(white) );
  //   glUniform1f( g_uniformMaterialShininess, 50.0f );

  //   glDrawElements( GL_TRIANGLES, numIndicies, GL_UNSIGNED_INT, BUFFER_OFFSET(0) );
}

void Mesh::setShaderProgram(QOpenGLShaderProgram* texturedDiffuseShaderProgram)
{
    m_program = texturedDiffuseShaderProgram;
}

bool Mesh::setupMesh(PositionBuffer vertexBuffer, IndexBuffer indexBuffer)
{
    m_PositionBuffer = vertexBuffer;
    m_IndexBuffer = indexBuffer;
    return setupMesh();

}

// original source for the functionality:
// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/
bool Mesh::loadMesh(const std::string& filename, QVector4D texSignature)
{
    std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
    std::vector< glm::vec3 > temp_vertices;
    std::vector< glm::vec2 > temp_uvs;
    std::vector< glm::vec3 > temp_normals;

    //FILE * file = fopen(path, "r");
    std::cout << filename << std::endl;
    QFile q_file(QString::fromStdString(filename));
    //if( !fs::exists(filename) )
    if( !q_file.exists() )
    {
        std::cerr << "Could not find file: " << q_file.fileName().toStdString() << std::endl;
        return false;
    }
    q_file.open(QFile::ReadOnly);

//    int fd = q_file.handle();
//    qDebug() <<fd;
//    FILE* file = fdopen(fd, "r");

    QTextStream in(&q_file);
    while (!in.atEnd())
    {
          QString q_line = in.readLine();
          QByteArray array = q_line.toLocal8Bit();
          char* line = array.data();

          char lineHeader[128];
          // read the first word of the line
          int res = sscanf(line, "%s", lineHeader);

        // else : parse lineHeader
        if ( strcmp( lineHeader, "v" ) == 0 ){
            glm::vec3 vertex;
            sscanf(line, "%s %f %f %f\n", &lineHeader, &vertex.x, &vertex.y, &vertex.z );
            temp_vertices.push_back(vertex);
        }else if ( strcmp( lineHeader, "vt" ) == 0 ){
            glm::vec2 uv;
            sscanf(line, "%s %f %f\n", &lineHeader, &uv.x, &uv.y );
            temp_uvs.push_back(uv);
        }else if ( strcmp( lineHeader, "vn" ) == 0 ){
            glm::vec3 normal;
            sscanf(line, "%s %f %f %f\n", &lineHeader, &normal.x, &normal.y, &normal.z );
            temp_normals.push_back(normal);
        }else if ( strcmp( lineHeader, "f" ) == 0 ){
            std::string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];

            int matches = sscanf(line, "%s%d/%d/%d %d/%d/%d %d/%d/%d\n", &lineHeader, &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
            if (matches != 10){
                printf("File can't be read by our simple parser : ( Try exporting with other options\n");
                return false;
            }
            vertexIndices.push_back(vertexIndex[0]);
            vertexIndices.push_back(vertexIndex[1]);
            vertexIndices.push_back(vertexIndex[2]);
            uvIndices    .push_back(uvIndex[0]);
            uvIndices    .push_back(uvIndex[1]);
            uvIndices    .push_back(uvIndex[2]);
            normalIndices.push_back(normalIndex[0]);
            normalIndices.push_back(normalIndex[1]);
            normalIndices.push_back(normalIndex[2]);
        }
    }
    q_file.close();

    // For each vertex of each triangle
    for( unsigned int i=0; i<vertexIndices.size(); i++ ){
        unsigned int vertexIndex = vertexIndices[i];
        unsigned int uvIndex = uvIndices[i];
        unsigned int normalIndex = normalIndices[i];
        glm::vec3 vertex = temp_vertices[ vertexIndex-1 ];
        glm::vec2 uv = temp_uvs[uvIndex - 1];
        glm::vec3 normal = temp_normals[normalIndex - 1];
        m_PositionBuffer.push_back (Vertex(QVector3D(vertex.x, vertex.y, vertex.z), texSignature,
                                           QVector3D(normal.x, normal.y, normal.z), QVector2D(uv.x,uv.y) ));
        m_IndexBuffer.push_back(i);

    }



    return setupMesh();
}

bool Mesh::setupMesh()
{
    //m_modelToWorld = program->uniformLocation("modelToWorld");
    //m_mesh->loadDefaultTextures();

    QOpenGLBuffer m_vertex;
    QOpenGLBuffer m_index(QOpenGLBuffer::IndexBuffer);



    // Create Vertex Array Object
    VAO.create();
    VAO.bind();


    m_vertex.create();
    if ( !m_vertex.bind() )
     {
     qWarning() << "Could not bind vertex buffer to the context";
     return false;
     }
    m_vertex.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vertex.allocate(m_PositionBuffer.data(), m_PositionBuffer.size() * Vertex::stride());
    //m_vertex.allocate(&(m_PositionBuffer[0]), m_PositionBuffer.size() * Vertex::stride());

    //m_vertex[0].allocate(positions.data(), positions.size() * sizeof(vec3));

    m_program->enableAttributeArray(POSITION_ATTRIBUTE);
    m_program->setAttributeBuffer(POSITION_ATTRIBUTE, GL_FLOAT, Vertex::positionOffset(), Vertex::PositionTupleSize, Vertex::stride());
    m_program->enableAttributeArray(COLOR_ATTRIBUTE);
    m_program->setAttributeBuffer(COLOR_ATTRIBUTE, GL_FLOAT, Vertex::colorOffset(), Vertex::ColorTupleSize, Vertex::stride());
    m_program->enableAttributeArray(NORMAL_ATTRIBUTE);
    m_program->setAttributeBuffer(NORMAL_ATTRIBUTE, GL_FLOAT, Vertex::normalOffset(), Vertex::NormalTupleSize, Vertex::stride());
    m_program->enableAttributeArray(TEXCOORD0_ATTRIBUTE);
    m_program->setAttributeBuffer(TEXCOORD0_ATTRIBUTE, GL_FLOAT, Vertex::texCoordOffset(), Vertex::TexCoordTupleSize, Vertex::stride());

    m_index.create();

    if ( !m_index.bind() )
     {
     qWarning() << "Could not bind index buffer to the context";
     return false;
     }

    m_index.setUsagePattern(QOpenGLBuffer::StaticDraw);
    //m_index.allocate(m_IndexBuffer.data(), m_IndexBuffer.size()*sizeof(GLuint));
    m_index.allocate(&(m_IndexBuffer[0]), sizeof(GLuint) * m_IndexBuffer.size());

    // Release (unbind) all
    VAO.release();
    m_vertex.release();
    m_index.release();
    std::cout << "Mesh setup finished" << std::endl;
    return true;
}


void Mesh::cleanup()
{
    VAO.destroy();
}
