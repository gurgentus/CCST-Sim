#include "car.h"

Car::Car()
{
    orient();
    toPosRotMatrix = toMatrix();

    angle = 0;
    dw = 0;
    xi = 1.5*pi;
    xi_old = 1.5*pi;
    T = 0;
    v = 0;
    x = 200.1*cos(angle);
    y = 200.1*sin(angle);
}

void Car::orient()
{
    setRotation(-90,1,0,0);
    setScale(0.001f);

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
    x = 200.1*cos(angle);
    y = -200.1*sin(angle);

}

void Car::updateState2(double dt, double gap)
{
    // controlled car
    // controller.update(t, gap)
    // T = controller.pid_control()

    T = 10*(gap - 0.5);
    xi = xi + 2*(v*sin(dw/2.0)/4.0)*dt;

    x = x + v*cos(xi)*dt;
    y = y + v*sin(xi)*dt;
    v = v + dt*(T*cos(dw)*cos(dw))/100.0;
    if (v > 2)
    {
        v = 2;
    }
    std::cout << dw << " " << xi << " " << gap << " " << v << std::endl;


}
