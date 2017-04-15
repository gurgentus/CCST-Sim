#include "car.h"

Car::Car()
{
    InitializeState();
}

void Car::InitializeState()
{
    ResetOrientation();
    local_to_world_matrix_ = toMatrix();

    // set state variables
    angle_ = 0;
    dw_ = 0;
    xi_ = 1.5*pi;
    xi_old_ = 1.5*pi;
    T_ = 0;
    v_ = 1;
    x_ = 200.1*cos(angle_);
    y_ = 200.1*sin(angle_);
    total_error_ = 0;
}

void Car::InitializeControls()
{
    speedControl = new Control(control_layout_, drawingWidget, this, 1, 100, 1, 10, "Lead Car Speed: ", "m/s");
}
void Car::UpdateControls()
{
    if (speedControl != nullptr)
    {
        UpdateSpeed(0.1*(double)speedControl->m_value);
    }
}

void Car::ResetOrientation()
{
    setRotation(-90,1,0,0);
    setScale(0.001f);

}

bool Car::SetupDefaultMesh(QVector4D texSignature)
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

            position_buffer_.push_back ( Vertex(QVector3D(X, Y, Z), QVector4D( 0.0f, 1.0f, 0.0f, 1.0f ), QVector3D(X, Y, Z), QVector2D(U,V) ));

        }
    }



    for( int i = 0; i < slices * stacks + slices; ++i )
    {
        index_buffer_.push_back( i );
        index_buffer_.push_back( i + slices + 1  );
        index_buffer_.push_back( i + slices );

        index_buffer_.push_back( i + slices + 1  );
        index_buffer_.push_back( i );
        index_buffer_.push_back( i + 1 );
    }

    SetupMesh();

    std::cout << "Car loaded" << std::endl;
    return true;
}

void Car::SteerLeft()
{
    dw_ += 0.01;
}

void Car::SteerRight()
{
    dw_ -= 0.01;
}

// this controls the lead car location (not using real physics)
void Car::UpdateState(double dt, double radius)
{
    // lead car
    angle_ = angle_ + (v_/radius)*dt;
    xi_old_ = xi_;
    xi_ = xi_-angle_*180/3.14;
    x_ = radius*cos(angle_);
    y_ = -radius*sin(angle_);

    ResetOrientation();
    rotate(xi_-xi_old_, 0,1,0);
    setTranslation(QVector3D(x_, 0.51, -y_));
    local_to_world_matrix_ = toMatrix();

}

void Car::UpdateSpeed(double speed)
{
    v_ = speed;
}

double Car::x() const
{
    return x_;
}

void Car::setX(double x)
{
    x_ = x;
}

double Car::y() const
{
    return y_;
}

void Car::setY(double y)
{
    y_ = y;
}

double Car::xi() const
{
    return xi_;
}

void Car::setXi(double xi)
{
    xi_ = xi;
}

double Car::dw() const
{
    return dw_;
}

void Car::setDw(double dw)
{
    dw_ = dw;
}


