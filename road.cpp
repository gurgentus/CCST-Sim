#include "road.h"
#include <cmath>

Road::Road()
{
}

double Road::distanceToRoad(double x, double z)
{
     return std::abs(std::sqrt(x*x+z*z)-200.25);
}

bool Road::SetupDefaultMesh()
{

    int slices = 320;

    for ( int j = 0; j <= slices; ++j )
    {
        // U texture coordinate.
        float U = j / (float)slices;
        float theta = U * _2pi;

        float X_in = 200*cos(theta);
        float Z_in = 200*sin(theta);

        float X_out = 200.5*cos(theta);
        float Z_out = 200.5*sin(theta);

        float Y = 0.51;

        position_buffer_.push_back ( Vertex(QVector3D(X_in, Y, Z_in), QVector4D( 1, 0, 0, 0 ), QVector3D(0, 1, 0), QVector2D(-1,U) ));
        position_buffer_.push_back ( Vertex(QVector3D(X_out, Y, Z_out), QVector4D( 1, 0, 0, 0 ), QVector3D(0, 1, 0), QVector2D(1,U) ));

    }


    for( int i = 0; i < 2*slices; i=i+2 )
    {
        index_buffer_.push_back( i + 3 );
        index_buffer_.push_back( i + 1 );
        index_buffer_.push_back( i + 2 );
        index_buffer_.push_back( i + 2 );
        index_buffer_.push_back( i + 1 );
        index_buffer_.push_back( i  );
    }

    SetupMesh();

    std::cout << "Road loaded" << std::endl;
    return true;
}

