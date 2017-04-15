#include "planet.h"

Planet::Planet()
{
    InitializeState();
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
    speedControl = new Control(control_layout_, drawingWidget, this, 1, 100, 1, 10, "Simulation Speed: ", "");
}
void Planet::UpdateControls()
{
    if (speedControl != nullptr)
    {
        sim_speed_ = (double)speedControl->m_value;
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
    p_simulator_->update_state(sim_speed_*dt);
    setPosition(p_simulator_->position());
    ResetOrientation();
    setTranslation(x_, y_, z_);
    local_to_world_matrix_ = toMatrix();
}

