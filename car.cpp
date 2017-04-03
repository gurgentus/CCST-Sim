#include "car.h"

Car::Car()
{
    orient();
    toPosRotMatrix = toMatrix();

    angle = 0;
    xi = 1.5*pi;
    xi_old = 1.5*pi;
    x = 201*cos(angle);
    y = 201*sin(angle);
}

void Car::orient()
{
    setRotation(-90,1,0,0);
    setScale(0.01f);

}

void Car::setModels()
{
    m_modelToWorld = m_program->uniformLocation("modelToWorld");
    m_program->setUniformValue(m_modelToWorld, QMatrix4x4(toPosRotMatrix));
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

            m_PositionBuffer.push_back ( Vertex(QVector3D(X, Y, Z), QVector4D( 0.0f, 1.0f, 0.0f, 1.0f ), QVector3D(X, Y, Z), QVector2D(U,V) ));

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

void Car::updateState(double dt, double velocity)
{
    // lead car
    angle = angle + (velocity/200.0)*dt;
    xi_old = xi;
    xi = xi-angle*180/3.14;
    x = 201*cos(angle);
    y = -201*sin(angle);

}

void Car::updateState2(double dt, double gap)
{
    // controlled car
    double u = 150*(gap - 20);
    angle = angle + (20/200.0)*dt;
    x = x + u*cos(xi)*dt*dt/2;
    y = y + u*sin(xi)*dt*dt/2;
    std::cout << xi << " " << gap << " " << u << std::endl;


}
