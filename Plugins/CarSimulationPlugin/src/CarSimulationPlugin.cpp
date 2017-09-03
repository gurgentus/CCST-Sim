#include "CarSimulationPlugin.hpp"
#include "Common/Input.hpp"
#include <cmath>

CarSimulationPlugin::CarSimulationPlugin()
    : terrain_(32, 2)
{
}

// Returns the list of simulations to show in the simulator menu
QStringList CarSimulationPlugin::Simulations() const
{
    return QStringList() << tr("Car Simulation");
}

void CarSimulationPlugin::InitializeObjects(QVBoxLayout *info_layout)
{
    QLabel* instructions = new QLabel();
    instructions->setText("Press A to steer left; Press D to steer right.");
    info_layout->addWidget(instructions);

    p_info_layout_ = info_layout;

    InitializeObjects(p_info_layout_, p_info_layout_, p_sim->p_program_, p_sim->p_textures_);

    p_sim->p_sim_button1->setEnabled(true);
    p_sim->p_sim_button2->setEnabled(false);

}

// Called on timer time-outs
void CarSimulationPlugin::UpdateState(double dt)
{
    lead_car_.UpdateState(dt, 200.1);

    car_.Sense(lead_car_);
    car_.UpdateState2(dt);

    p_sim->camera_.setRotation(180, 0,1,0);;
    p_sim->camera_.rotate((car_.xi()-1.5*M_PI)*180/M_PI, 0,1,0);
    p_sim->camera_.setTranslation(QVector3D(car_.x()-0.5*cos(car_.xi()), 0.6,
                                                               -car_.y()+0.5*sin(car_.xi())));
}

void CarSimulationPlugin::InitializeSimulation(Simulation& sim)
{
    p_sim = &sim;
}

// Initializes the 3D objects and connects to the control and output panels of the GUI
void CarSimulationPlugin::InitializeObjects(QVBoxLayout *controls_layout, QVBoxLayout *outputs_layout, QOpenGLShaderProgram* shader,
                                       Textures* textures)
{
    p_program_ = shader;
    p_sim->SetControlOutputPanel(controls_layout, outputs_layout);
    terrain_.SetShaderProgram(p_program_);
    terrain_.setRoad(&road_);
    road_.SetShaderProgram(p_program_);
    lead_car_.SetShaderProgram(p_program_);
    car_.SetShaderProgram(p_program_);

    car_.SetControlOutputPanel(controls_layout, outputs_layout, p_sim);
    lead_car_.SetControlOutputPanel(controls_layout, outputs_layout, p_sim);
}

// Initializes Textures and Meshes
void CarSimulationPlugin::InitializeGraphics()
{
    if ( !p_sim->textures_.loadTexture( ":/Data/Textures/grass.jpg", GRASS_TEXTURE ) )
    {
        std::cerr << "Failed to load terrain texture for grass!" << std::endl;
    }
    if ( !p_sim->textures_.loadTexture( ":/Data/Textures/rock.png", ROCK_TEXTURE ) )
    {
        std::cerr << "Failed to load terrain texture for rock!" << std::endl;
    }
    if ( !p_sim->textures_.loadTexture( ":/Data/Textures/snow.jpg", SNOW_TEXTURE ) )
    {
        std::cerr << "Failed to load terrain texture for snow!" << std::endl;
    }
    if ( !p_sim->textures_.loadTexture( ":/Data/Textures/road.jpg", ROAD_TEXTURE ) )
    {
        std::cerr << "Failed to load terrain texture for road!" << std::endl;
    }
    if ( !p_sim->textures_.loadTexture( ":/Data/Textures/car1.jpeg", CAR_TEXTURE ) )
    {
        std::cerr << "Failed to load terrain texture for road!" << std::endl;
    }
    if ( !p_sim->textures_.loadTexture( ":/Data/Textures/car2.jpeg", CAR2_TEXTURE ) )
    {
        std::cerr << "Failed to load terrain texture for road!" << std::endl;
    }
    if ( !road_.SetupDefaultMesh(QVector4D( 0.0f, 0.0f, 1.0f, 0.0f )) )
    {
        std::cerr << "Failed to load the road!" << std::endl;
    }
    if ( !car_.LoadMesh(":/Data/Objects/coop.obj", QVector4D( 0.0f, 1.0f, 0.0f, 0.0f )) )
    {
        std::cerr << "Failed to load the car!" << std::endl;
    }
    if ( !lead_car_.LoadMesh(":/Data/Objects/coop.obj", QVector4D( 0.0f, 0.0f, 1.0f, 1.0f )) )
    {
        std::cerr << "Failed to load the lead car!" << std::endl;
    }
    if ( !terrain_.SetupDefaultMesh() )
    {
        std::cerr << "Failed to load heightmap for terrain!" << std::endl;
    }
    p_sim->p_program_->release();
}

void CarSimulationPlugin::InitializeGUI()
{
    p_sim->camera_.setRotation(180, 0,1,0);;
    p_sim->camera_.rotate((car_.xi()-1.5*M_PI)*180/M_PI, 0,1,0);
    p_sim->camera_.setTranslation(QVector3D(car_.x()-0.5*cos(car_.xi()), 0.6,
                                                               -car_.y()+0.5*sin(car_.xi())));

    lead_car_.InitializeControls();
    car_.InitializeControls();
    car_.InitializeOutputs();

    is_initialized_ = true;
}

// Renders the 3D objects
void CarSimulationPlugin::RenderGraphics()
{
    p_sim->p_program_->bind();

    p_sim->p_textures_->bindTexture(GRASS_TEXTURE);
    p_sim->p_textures_->bindTexture(ROCK_TEXTURE);
    p_sim->p_textures_->bindTexture(ROAD_TEXTURE);
    p_sim->p_textures_->bindTexture(CAR_TEXTURE);
    p_sim->p_textures_->bindTexture(CAR2_TEXTURE);

    p_sim->p_program_->setUniformValue("stage1", GRASS_TEXTURE);
    p_sim->p_program_->setUniformValue("stage2", ROCK_TEXTURE);
    p_sim->p_program_->setUniformValue("stage3", ROAD_TEXTURE);
    p_sim->p_program_->setUniformValue("stage4", CAR_TEXTURE);
    p_sim->p_program_->setUniformValue("stage5", CAR2_TEXTURE);

    road_.SetModels();
    road_.Draw();

    car_.SetModels();
    car_.Draw();

    lead_car_.SetModels();
    lead_car_.Draw();

    terrain_.SetModels();
    terrain_.Draw();

    p_sim->p_program_->release();

}

void CarSimulationPlugin::UpdateControls()
{
}

// Check if A or D keys were pressed, if yes
// steer the car
void CarSimulationPlugin::CheckKeyboardInput()
{
    if (Input::keyPressed(Qt::Key_A))
    {
      car_.SteerLeft();
    }
    if (Input::keyPressed(Qt::Key_D))
    {
      car_.SteerRight();
    }
}

bool CarSimulationPlugin::is_initialized()
{
    return is_initialized_;
}

bool CarSimulationPlugin::is_running()
{
    return is_running_;
}

// Starts the simulation corresponding to the first button
void CarSimulationPlugin::StartSimulation1()
{
    lead_car_.InitializeState();
    car_.InitializeState();
    is_running_ = true;
}

// Starts the simulation corresponding to the second button
void CarSimulationPlugin::StartSimulation2()
{
    lead_car_.InitializeState();
    car_.InitializeState();
    is_running_ = true;
}

void CarSimulationPlugin::StopSimulation1()
{
    is_running_ = false;
}

void CarSimulationPlugin::StopSimulation2()
{
}
