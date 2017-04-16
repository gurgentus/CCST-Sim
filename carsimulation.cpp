#include "carsimulation.h"

CarSimulation::CarSimulation()
    : terrain_(32, 2)
, Simulation()
{
    terrain_.SetShaderProgram(&shader);
    terrain_.setRoad(&road_);
    road_.SetShaderProgram(&shader);
    lead_car_.SetShaderProgram(&shader);
    car_.SetShaderProgram(&shader);
    setFocusPolicy( Qt::StrongFocus );
}

void CarSimulation::InitializeObjects(QVBoxLayout *info_layout)
{
    instructions->setText("Press A to steer left; Press D to steer right.");
    info_layout->addWidget(instructions);
    InitializeObjects(info_layout, info_layout, &shader, &textures_, &terrain_, &road_, &car_, &lead_car_);
}

void CarSimulation::UpdateState(double dt)
{
    lead_car_.UpdateState(dt, 200.1);

    if (currentSim == 1)
    {
        car_.Sense(lead_car_);
        car_.UpdateState1(dt);
    }
    if (currentSim == 2)
    {
        car_.Sense(lead_car_);
        car_.UpdateState2(dt);
    }

    camera_.setRotation(180, 0,1,0);;
    camera_.rotate((car_.xi()-1.5*pi)*180/pi, 0,1,0);
    camera_.setTranslation(QVector3D(car_.x()-0.5*cos(car_.xi()), 0.6,
                                                               -car_.y()+0.5*sin(car_.xi())));
}

void CarSimulation::start_simulation1()
{
    lead_car_.InitializeState();
    car_.InitializeState();
}
void CarSimulation::start_simulation2()
{
    lead_car_.InitializeState();
    car_.InitializeState();
}

void CarSimulation::InitializeObjects(QVBoxLayout *layout, QVBoxLayout *output_layout, QOpenGLShaderProgram* shader,
                                       Textures* textures, Terrain* terrain, Road *road, AdaptiveCar* car, Car* leadCar)
{
    car_.SetControlOutputPanel(layout, output_layout, this);
    car_.InitializeControls();
    car_.InitializeOutputs();

    lead_car_.SetControlOutputPanel(layout, output_layout, this);
    lead_car_.InitializeControls();

    Simulation::InitializeObjects(shader, textures);

}

void CarSimulation::initializeGL()
{
    Simulation::initializeGL();

    if ( !textures_.loadTexture( ":/Data/Textures/grass.jpg", GRASS_TEXTURE ) )
    {
        std::cerr << "Failed to load terrain texture for grass!" << std::endl;
    }
    if ( !textures_.loadTexture( ":/Data/Textures/rock.png", ROCK_TEXTURE ) )
    {
        std::cerr << "Failed to load terrain texture for rock!" << std::endl;
    }
    if ( !textures_.loadTexture( ":/Data/Textures/snow.jpg", SNOW_TEXTURE ) )
    {
        std::cerr << "Failed to load terrain texture for snow!" << std::endl;
    }
    if ( !textures_.loadTexture( ":/Data/Textures/road.jpg", ROAD_TEXTURE ) )
    {
        std::cerr << "Failed to load terrain texture for road!" << std::endl;
    }
    if ( !textures_.loadTexture( ":/Data/Textures/car1.jpeg", CAR_TEXTURE ) )
    {
        std::cerr << "Failed to load terrain texture for road!" << std::endl;
    }
    if ( !textures_.loadTexture( ":/Data/Textures/car2.jpeg", CAR2_TEXTURE ) )
    {
        std::cerr << "Failed to load terrain texture for road!" << std::endl;
    }
    if ( !road_.SetupDefaultMesh(QVector4D( 1.0f, 0.0f, 0.0f, 0.0f )) )
    {
        std::cerr << "Failed to load the road!" << std::endl;
    }

    if ( !car_.LoadMesh(":/Data/Objects/coop.obj", QVector4D( 0.0f, 1.0f, 0.0f, 1.0f )) )
    {
        std::cerr << "Failed to load the car!" << std::endl;
    }
    if ( !lead_car_.LoadMesh(":/Data/Objects/coop.obj", QVector4D( 0.0f, 1.0f, 1.0f, 1.0f )) )
    {
        std::cerr << "Failed to load the lead car!" << std::endl;
    }
    if ( !terrain_.SetupDefaultMesh() )
    {
        std::cerr << "Failed to load heightmap for terrain!" << std::endl;
    }



    // Set global information
    //glEnable(GL_DEPTH_TEST | GL_CULL_FACE);
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

    terrain_.SetModels();
    road_.SetModels();
    car_.SetModels();
    lead_car_.SetModels();
    p_program_->release();

}

void CarSimulation::paintGL()
{
    Simulation::paintGL();

    textures_.bindAllTextures();

    p_program_->bind();
    p_program_->setUniformValue("stage1", GRASS_TEXTURE);
    p_program_->setUniformValue("stage2", ROCK_TEXTURE);
    p_program_->setUniformValue("stage3", ROAD_TEXTURE);
    p_program_->setUniformValue("car", CAR_TEXTURE);
    p_program_->setUniformValue("car2", CAR2_TEXTURE);

    road_.SetModels();
    road_.Draw();

    car_.SetModels();
    car_.Draw();

    lead_car_.SetModels();
    lead_car_.Draw();

    terrain_.SetModels();
    terrain_.Draw();

    p_program_->release();
}

void CarSimulation::update()
{
    if (Input::keyPressed(Qt::Key_A))
    {
      car_.SteerLeft();
    }
    if (Input::keyPressed(Qt::Key_D))
    {
      car_.SteerRight();
    }
    Simulation::update();
}
