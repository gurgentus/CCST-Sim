#include "airplane.h"

Airplane::Airplane()
{
}


bool Airplane::SetupDefaultMesh(QVector4D texSignature = QVector4D( 0.0f, 1.0f, 0.0f, 1.0f ))
{
    setupCapMesh();
    setupSphereMesh();
    setupFuselageMesh();
}

void Airplane::setupCapMesh()
{
    //loadDefaultTextures();

    int slices = 32;

    float V = 0;

    m_PositionBuffer.push_back ( Vertex(QVector3D(0, 0, 0), QVector3D( 1.0f, 0.0f, 0.0f ), QVector3D(1, 0, 0), QVector2D(0,0) ));

    for ( int j = 0; j <= slices; ++j )
    {
        // U texture coordinate.
        float U = j / (float)slices;
        float theta = U * _2pi;

        float X = 0;
        float Y = cos(theta);
        float Z = sin(theta);

        m_PositionBuffer.push_back ( Vertex(QVector3D(X, Y, Z), QVector3D( 1.0f, 0.0f, 0.0f ), QVector3D(0, Y, Z), QVector2D(U,V) ));

    }


    for( int i = 1; i <= slices; ++i )
    {
        m_IndexBuffer.push_back( 0 );
        m_IndexBuffer.push_back( i  );
        m_IndexBuffer.push_back( i + 1 );
    }

    setupMesh();

}

void Airplane::setupFuselageMesh()
{
    //loadDefaultTextures();


    int stacks = 32;
    int slices = 32;

    for( int i = 0; i <= stacks; ++i )
    {
        // V texture coordinate.
        float V = i / (float)stacks;

        for ( int j = 0; j <= slices; ++j )
        {
            // U texture coordinate.
            float U = j / (float)slices;
            float theta = U * _2pi;

            float X = i;
            float Y = cos(theta);
            float Z = sin(theta);

            m_PositionBuffer.push_back ( Vertex(QVector3D(X, Y, Z), QVector3D( 1.0f, 0.0f, 0.0f ), QVector3D(0, Y, Z), QVector2D(Y,V) ));

        }
    }

    for( int i = 0; i < slices * stacks + slices; ++i )
    {
        m_IndexBuffer.push_back( i );
        m_IndexBuffer.push_back( i + slices + 1  );
        m_IndexBuffer.push_back( i + slices );

        m_IndexBuffer.push_back( i + slices + 1  );
        m_IndexBuffer.push_back( i );
        m_IndexBuffer.push_back( i + 1 );
    }

    setupMesh();


}

void Airplane::setupSphereMesh()
{
    //loadDefaultTextures();

    int stacks = 32;
    int slices = 32;

    for( int i = 0; i <= stacks; ++i )
    {
        // V texture coordinate.
        float V = i / (float)stacks;
        float phi = V * pi;

        for ( int j = 0; j <= slices; ++j )
        {
            // U texture coordinate.
            float U = j / (float)slices;
            float theta = U * _2pi;

            float X = cos(theta) * sin(phi);
            float Y = cos(phi);
            float Z = sin(theta) * sin(phi);

            //positions.push_back( vec3( X, Y, Z) * radius );
            m_PositionBuffer.push_back ( Vertex(QVector3D(X, Y, Z), QVector3D( 1.0f, 0.0f, 0.0f ), QVector3D(X, Y, Z), QVector2D(U,V) ));
            //positions.push_back( Vertex(QVector3D(X, Y, Z)*radius, QVector3D( 1.0f, 0.0f, 0.0f )) );
            //normals.push_back( vec3(X, Y, Z) );
            //textureCoords.push_back( vec2(U, V) );
        }
    }



    for( int i = 0; i < slices * stacks + slices; ++i )
    {
        m_IndexBuffer.push_back( i );
        m_IndexBuffer.push_back( i + slices + 1  );
        m_IndexBuffer.push_back( i + slices );

        m_IndexBuffer.push_back( i + slices + 1  );
        m_IndexBuffer.push_back( i );
        m_IndexBuffer.push_back( i + 1 );
    }

    setupMesh();


}
