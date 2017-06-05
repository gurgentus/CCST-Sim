#include "planet.h"
#include "nums/RungeKuttaSolver.hpp"

Planet::Planet()
{
    InitializeState();
}

void Planet::SetPositionFunction( QVector3D (AbstractOdeSolver::*fun)()  )
{
    pos = fun;
}

void Planet::InitializeState()
{
    ResetOrientation();
    local_to_world_matrix_ = toMatrix();
    //local_to_world_matrix_.setToIdentity();

    // set state variables
    x_ = 0;
    y_ = 0;
    z_ = 0;

    sim_speed_ = 1;
}

void Planet::ResetOrientation()
{
    xRot = 0;
    yRot = 0;
    zRot = 0;
    //g_fSunRotation = 0.0f;
    //m_transform.translate(0.0f, 0.0f, -5.0f);
    //m_transform.rotate(g_fSunRotation, 0, -1, 0);
    //m_transform.translate(2.5f, 0, 0);
    //setFocusPolicy( Qt::StrongFocus );
    setScale(r_);
}

bool Planet::SetupDefaultMesh(QVector4D texSignature)
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

    std::cout << "Planet loaded" << std::endl;
    return true;
}

void Planet::InitializeControls()
{
    speedControl = new Control(control_layout_, drawingWidget, this, 1, 100000, 1, 10, "Simulation Speed: ", "");
}

void Planet::InitializeOutputs()
{
    x_position_output_ = new Output(output_layout_, 0, 1, "Relative X Position: ", "km");
    y_position_output_ = new Output(output_layout_, 0, 1, "Relative Y Position: ", "km");
    z_position_output_ = new Output(output_layout_, 0, 1, "Relative Z Position: ", "km");
    r_output_ = new Output(output_layout_, 0, 1, "Distance to the origin: ", "km");
    e_output_ = new Output(output_layout_, 0, 1, "Eccentricity", "");
    t_output_ = new Output(output_layout_, 0, 1, "Time", "days");

}

void Planet::UpdateControls()
{
    if (speedControl != nullptr)
    {
        sim_speed_ = (double)speedControl->value();
    }
}


double Planet::r() const
{
    return r_;
}

void Planet::setR(double r)
{
    r_ = r;
}

void Planet::setPosition(QVector3D pos)
{
    x_ = pos.x();
    y_ = pos.y();
    z_ = pos.z();
}

void Planet::UpdateState(double dt)
{
    double scale = 10000;

    p_simulator_->UpdateState(sim_speed_*dt);
    setPosition((p_simulator_->*pos)());
    //QVector3D vel = p_simulator_->velocity();
    //u_ = vel.x();
    //v_ = vel.y();
    //w_ = vel.z();
    ResetOrientation();
    setTranslation(x_/scale, y_/scale, z_/scale);
    local_to_world_matrix_ = toMatrix();
    UpdateOutputs();
}

void Planet::UpdateOutputs()
{
    if (x_position_output_ != nullptr)
    {
        x_position_output_->setText(QString::number(x_));
    }
    if (y_position_output_ != nullptr)
    {
        y_position_output_->setText(QString::number(y_));
    }
    if (z_position_output_ != nullptr)
    {
        z_position_output_->setText(QString::number(z_));
    }
    if (r_output_ != nullptr)
    {
        r_output_->setText(QString::number(sqrt(x_*x_+y_*y_+z_*z_)));
    }
    if (e_output_ != nullptr)
    {
        //double e = p_simulator_->eccentricity();
        //e_output_->setText(QString::number(e));
    }
    if (t_output_ != nullptr)
    {

        t_output_->setText(QString::number(p_simulator_->time()/(3600*24)));
    }
}

