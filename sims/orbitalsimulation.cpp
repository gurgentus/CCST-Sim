#include "orbitalsimulation.h"

OrbitalSimulation::OrbitalSimulation()
    : Simulation()
{
}

void OrbitalSimulation::AddPlanet(Planet& planet)
{
    planet.SetShaderProgram(&shader);
    planets.push_back(&planet);
}

void OrbitalSimulation::InitializeObjects(QVBoxLayout* info_layout)
{
    instructions->setText("Move slider to change simulation speed");
    info_layout->addWidget(instructions);
    InitializeObjects(info_layout, info_layout, &shader, &textures_);
    //simulator.simulate();

    for (int i=0; i< planets.size(); i++)
    {
        if (planets[i]->p_simulator() != nullptr)
        {
             planets[i]->p_simulator()->InitialConditions();
        }
    }
}

void OrbitalSimulation::InitializeObjects(QVBoxLayout *layout, QVBoxLayout *output_layout, QOpenGLShaderProgram* shader,
                                       Textures* textures)
{
    for (unsigned long i=0; i< planets.size(); i++)
    {
        planets[i]->SetControlOutputPanel(layout, output_layout, this);
    }
    Simulation::InitializeObjects(shader, textures);
}


void OrbitalSimulation::UpdateState(double dt)
{

    for (unsigned long  i=0; i< planets.size(); i++)
    {
        if (planets[i]->p_simulator() != nullptr)
        {
             planets[i]->UpdateState(dt);
        }
    }

//    moon_.setTranslation(QVector3D(10,10,0));
//    ResetOrientation();
//    rotate(xi_-xi_old_, 0,1,0);
//    setTranslation(QVector3D(x_, 0.51, -y_));
//    moon_.local_to_world_matrix_ = moon_.toMatrix();
}

void OrbitalSimulation::qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360)
        angle -= 360 * 16;
}

void OrbitalSimulation::setXRotation(int angle)
{
//    qNormalizeAngle(angle);
//    if (angle != earth_.xRot) {
//        earth_.xRot = angle;
//        //Q_EMIT xRotationChanged(angle);
//        earth_.rotate(earth_.xRot, 1.0f, 0.0f, 0.0f);
//        //myOpenGLWidget.update();
//    }
}

void OrbitalSimulation::setYRotation(int angle)
{
//    qNormalizeAngle(angle);
//    if (angle != earth_.yRot) {
//        earth_.yRot = angle;
//        //Q_EMIT yRotationChanged(angle);
//        earth_.rotate(earth_.yRot, 0.0f, 1.0f, 0.0f);
//        //myOpenGLWidget.update();
//    }
}

void OrbitalSimulation::setZRotation(int angle)
{
//    qNormalizeAngle(angle);
//    if (angle != earth_.zRot) {
//        earth_.zRot = angle;
//        //Q_EMIT zRotationChanged(angle);
//        earth_.rotate(earth_.zRot, 0.0f, 0.0f, 1.0f);
//        //myOpenGLWidget.update();
//    }
}

void OrbitalSimulation::StartSimulation1()
{
    for (unsigned long i=0; i< planets.size(); i++)
    {
        planets[i]->InitializeState();
        planets[i]->p_simulator()->InitialConditions();
    }
}
void OrbitalSimulation::StartSimulation2()
{
}

void OrbitalSimulation::initializeGL()
{
    Simulation::initializeGL();
    if ( !textures_.loadTexture( ":/Data/Textures/car2.jpeg", CAR_TEXTURE ) )
    {
        std::cerr << "Failed to load terrain texture for road!" << std::endl;
    }
    if ( !textures_.loadTexture( ":/Data/Textures/car1.jpeg", CAR2_TEXTURE ) )
    {
        std::cerr << "Failed to load terrain texture for road!" << std::endl;
    }
    if ( !textures_.loadTexture( ":/Data/Textures/earth.jpg", EARTH_TEXTURE ) )
    {
        std::cerr << "Failed to load terrain texture for earth!" << std::endl;
    }
    if ( !textures_.loadTexture( ":/Data/Textures/moon.jpg", MOON_TEXTURE ) )
    {
        std::cerr << "Failed to load terrain texture for moon!" << std::endl;
    }

    // Set global information
    //glEnable(GL_DEPTH_TEST | GL_CULL_FACE);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    for (unsigned long i=0; i < planets.size(); i++)
    {
        if (i==1)
        {
            if ( !planets[1]->SetupDefaultMesh(QVector4D( 0.0f, 0.0f, 1.0f, 1.0f )) )
            {
                std::cerr << "Failed to load the earth!" << std::endl;
            }
        }
        else
        {
            if (i==2)
            {
                if ( !planets[i]->LoadMesh(":/Data/Objects/nasa.obj", QVector4D( 0.0f, 1.0f, 0.0f, 1.0f  )) )
                {
                    std::cerr << "Failed to load the car!" << std::endl;
                }
            }
            else
            {
                if ( !planets[i]->SetupDefaultMesh(QVector4D(  1.0f, 1.0f, 1.0f, 1.0f )) )
                {

                    std::cerr << "Failed to load the earth!" << std::endl;
                }
            }
        }
        planets[i]->SetModels();
    }
    p_program_->release();

}



void OrbitalSimulation::paintGL()
{
    Simulation::paintGL();

    p_program_->bind();
    p_textures_->bindTexture(EARTH_TEXTURE);
    p_textures_->bindTexture(MOON_TEXTURE);
    p_textures_->bindTexture(CAR_TEXTURE);
    p_program_->setUniformValue("stage1", CAR_TEXTURE);
    p_program_->setUniformValue("stage2", EARTH_TEXTURE);
    p_program_->setUniformValue("stage3", CAR_TEXTURE);
    p_program_->setUniformValue("car", CAR_TEXTURE);
    p_program_->setUniformValue("car2", MOON_TEXTURE);

    for (unsigned long i=0; i< planets.size(); i++)
    {
        planets[i]->SetModels();
        planets[i]->Draw();
    }
    p_program_->release();

}


void OrbitalSimulation::update()
{
//    if (Input::keyPressed(Qt::Key_T))
//    {
//        moon_.UpdateState(1);
//    }
    Simulation::update();
}

