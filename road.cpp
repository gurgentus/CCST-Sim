#include "road.h"
#include <cmath>

Road::Road()
    : m_LocalToWorldMatrix(1)
    , m_InverseLocalToWorldMatrix(1)
{
}

void Road::setModels()
{
    //m_modelToWorld = m_program->uniformLocation("modelToWorld");
    //m_program->setUniformValue(m_modelToWorld, QMatrix4x4(glm::value_ptr(m_LocalToWorldMatrix)).transposed() );
    //m_program->setUniformValue("stage1", GRASS_TEXTURE);
    //m_program->setUniformValue("stage2", ROCK_TEXTURE);
    m_program->setUniformValue("stage3", ROAD_TEXTURE);
}

double Road::distanceToRoad(double x, double z)
{
     return std::abs(std::sqrt(x*x+z*z)-210);
}

bool Road::setupDefaultMesh()
{

    int slices = 32;

    float V = 0;

    //m_PositionBuffer.push_back ( Vertex(QVector3D(0, 0, 0), QVector3D( 1.0f, 0.0f, 0.0f ), QVector3D(1, 0, 0), QVector2D(0,0) ));

    for ( int j = 0; j <= slices; ++j )
    {
        // U texture coordinate.
        float U = j / (float)slices;
        float theta = U * _2pi;

        float X_in = 200*cos(theta);
        float Z_in = 200*sin(theta);

        float X_out = 220*cos(theta);
        float Z_out = 220*sin(theta);

        float Y = 0.1;

        m_PositionBuffer.push_back ( Vertex(QVector3D(X_in, Y, Z_in), QVector4D( 1, 0, 0, 0 ), QVector3D(0, 1, 0), QVector2D(-1,U) ));
        m_PositionBuffer.push_back ( Vertex(QVector3D(X_out, Y, Z_out), QVector4D( 1, 0, 0, 0 ), QVector3D(0, 1, 0), QVector2D(1,U) ));

    }


    for( int i = 0; i < 2*slices; i=i+2 )
    {
        m_IndexBuffer.push_back( i + 3 );
        m_IndexBuffer.push_back( i + 1 );
        m_IndexBuffer.push_back( i + 2 );
        m_IndexBuffer.push_back( i + 2 );
        m_IndexBuffer.push_back( i + 1 );
        m_IndexBuffer.push_back( i  );





    }

    setupMesh();

    std::cout << "Road loaded" << std::endl;
    return true;
}

