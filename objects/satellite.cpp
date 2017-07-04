#include "Satellite.hpp"
#include "nums/RungeKuttaSolver.hpp"

Satellite::Satellite()
{
    pos = nullptr;
    rot = nullptr;
    x_position_output_ = nullptr;
    y_position_output_ = nullptr;
    z_position_output_ = nullptr;
    r_output_ = nullptr;
    p_simulator_ = nullptr;
    local_to_world_matrix_ = toMatrix();
    InitializeState();
}

void Satellite::SetPositionFunction( QVector3D (AbstractOdeSolver::*fun)()  )
{
    pos = fun;
}
void Satellite::SetRotationFunction( double (AbstractOdeSolver::*fun)()  )
{
    rot = fun;
}

void Satellite::InitializeState()
{
    ResetOrientation();
    local_to_world_matrix_ = toMatrix();

    // set state variables
    x_ = 0.0;
    y_ = 0.0;
    z_ = 0.0;
}

void Satellite::ResetOrientation()
{
    xRot = 0;
    yRot = 0;
    zRot = 0;
    setScale(r_);
}

bool Satellite::SetupDefaultMesh(QVector4D texSignature)
{
    int stacks = 32;
    int slices = 32;

    for( int i = 0; i <= stacks; ++i )
    {
        // V texture coordinate.
        float V = i / (float)stacks;
        float phi = pi - V * pi;

        for ( int j = 0; j <= slices; ++j )
        {
            // U texture coordinate.
            float U = j / (float)slices;
            float theta = U * _2pi;

            float X = cos(theta) * sin(phi);
            float Y = cos(phi);
            float Z = sin(theta) * sin(phi);

            position_buffer_.push_back ( Vertex(QVector3D(X, Y, Z), texSignature, QVector3D(X, Y, Z), QVector2D(U,V) ));

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

    return true;
}

void Satellite::InitializeOutputs()
{
    if (pos)
    {
        x_position_output_ = new Output(output_layout_, 0, 1, "X Position: ", "km");
        y_position_output_ = new Output(output_layout_, 0, 1, "Y Position: ", "km");
        z_position_output_ = new Output(output_layout_, 0, 1, "Z Position: ", "km");
        r_output_ = new Output(output_layout_, 0, 1, "Distance to the origin: ", "km");
    }
}

double Satellite::r() const
{
    return r_*spatial_scale;
}

void Satellite::setR(double r)
{
    r_ = r/spatial_scale;
}

void Satellite::setPosition(QVector3D pos)
{
    x_ = pos.x();
    y_ = pos.y();
    z_ = pos.z();
}

void Satellite::UpdateState(double dt)
{
    if (p_simulator_) {
        p_simulator_->UpdateState(dt);
        if (pos) {
            setPosition((p_simulator_->*pos)());
        }
        ResetOrientation();
        if (rot != nullptr) {
            rotate((p_simulator_->*rot)()*180/M_PI, 0.0f, 1.0f, 0.0f);
        }

        setTranslation(x_/spatial_scale, z_/spatial_scale, y_/spatial_scale);
        local_to_world_matrix_ = toMatrix();
        UpdateOutputs();
    }
}

void Satellite::UpdateOutputs()
{
    if (x_position_output_)
    {
        x_position_output_->setValue(x_);
    }
    if (y_position_output_)
    {
        y_position_output_->setValue(y_);
    }
    if (z_position_output_)
    {
        z_position_output_->setValue(z_);
    }
    if (r_output_)
    {
        r_output_->setValue(sqrt(x_*x_+y_*y_+z_*z_));
    }
}

