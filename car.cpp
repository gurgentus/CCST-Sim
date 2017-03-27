#include "car.h"

Car::Car()
    : m_LocalToWorldMatrix(1)
    , m_InverseLocalToWorldMatrix(1)
{
}

void Car::setModels()
{
    m_modelToWorld = m_program->uniformLocation("modelToWorld");
    m_program->setUniformValue(m_modelToWorld, QMatrix4x4(toPosRotMatrix));
    //m_program->setUniformValue("stage1", GRASS_TEXTURE);
    //m_program->setUniformValue("stage2", ROCK_TEXTURE);
    //m_program->setUniformValue("stage3", ROAD_TEXTURE);
}

bool Car::setupDefaultMesh()
{


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
            m_PositionBuffer.push_back ( Vertex(QVector3D(X, Y, Z), QVector4D( 0.0f, 0.0f, 0.0f, 1.0f ), QVector3D(X, Y, Z), QVector2D(U,V) ));

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

    std::cout << "Car loaded" << std::endl;
    return true;
}

