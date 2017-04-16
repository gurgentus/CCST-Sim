#include "orbitalsimulation.h"

OrbitalSimulation::OrbitalSimulation()
    : Simulation()
{
    earth_.SetShaderProgram(&shader);
    moon_.SetShaderProgram(&shader);
    moon_.setP_simulator(&simulator);
    moon_.setR(1);
    moon_.setTranslation(QVector3D(10,10,0));
    moon_.local_to_world_matrix_ = moon_.toMatrix();
    earth_.setR(3);
}

void OrbitalSimulation::InitializeObjects(QVBoxLayout* info_layout)
{
    instructions->setText("Move slider to change simulation speed");
    info_layout->addWidget(instructions);
    InitializeObjects(info_layout, info_layout, &shader, &textures_, &earth_, &moon_);
    simulator.simulate();
}

void OrbitalSimulation::InitializeObjects(QVBoxLayout *layout, QVBoxLayout *output_layout, QOpenGLShaderProgram* shader,
                                       Textures* textures, Planet* earth, Planet* moon)
{

    //earth_.InitializeControls();
    moon_.SetControlOutputPanel(layout, output_layout, this);
    moon_.InitializeOutputs();
    moon_.InitializeControls();
    earth_.SetControlOutputPanel(layout, output_layout, this);

    Simulation::InitializeObjects(shader, textures);
}


void OrbitalSimulation::UpdateState(double dt)
{
      moon_.UpdateState(dt);
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
    qNormalizeAngle(angle);
    if (angle != earth_.xRot) {
        earth_.xRot = angle;
        //Q_EMIT xRotationChanged(angle);
        earth_.rotate(earth_.xRot, 1.0f, 0.0f, 0.0f);
        //myOpenGLWidget.update();
    }
}

void OrbitalSimulation::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != earth_.yRot) {
        earth_.yRot = angle;
        //Q_EMIT yRotationChanged(angle);
        earth_.rotate(earth_.yRot, 0.0f, 1.0f, 0.0f);
        //myOpenGLWidget.update();
    }
}

void OrbitalSimulation::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != earth_.zRot) {
        earth_.zRot = angle;
        //Q_EMIT zRotationChanged(angle);
        earth_.rotate(earth_.zRot, 0.0f, 0.0f, 1.0f);
        //myOpenGLWidget.update();
    }
}

void OrbitalSimulation::start_simulation1()
{
    earth_.InitializeState();
    moon_.InitializeState();
}
void OrbitalSimulation::start_simulation2()
{
}

void OrbitalSimulation::initializeGL()
{
    Simulation::initializeGL();
    if ( !textures_.loadTexture( ":/Data/Textures/rock.png", CAR_TEXTURE ) )
    {
        std::cerr << "Failed to load terrain texture for road!" << std::endl;
    }
    if ( !textures_.loadTexture( ":/Data/Textures/snow.jpg", CAR2_TEXTURE ) )
    {
        std::cerr << "Failed to load terrain texture for road!" << std::endl;
    }
    if ( !textures_.loadTexture( ":/Data/Textures/earth.dds", EARTH_TEXTURE ) )
    {
        std::cerr << "Failed to load terrain texture for earth!" << std::endl;
    }
    if ( !textures_.loadTexture( ":/Data/Textures/moon.dds", MOON_TEXTURE ) )
    {
        std::cerr << "Failed to load terrain texture for moon!" << std::endl;
    }
    if ( !earth_.SetupDefaultMesh(QVector4D( 1.0f, 1.0f, 1.0f, 1.0f )) )
    {
        std::cerr << "Failed to load the earth!" << std::endl;
    }
    if ( !moon_.SetupDefaultMesh(QVector4D( 0.0f, 0.0f, 1.0f, 1.0f )) )
    {
        std::cerr << "Failed to load the moon!" << std::endl;
    }

    // Set global information
    //glEnable(GL_DEPTH_TEST | GL_CULL_FACE);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    earth_.SetModels();
    moon_.SetModels();
    p_program_->release();

}



void OrbitalSimulation::paintGL()
{
    Simulation::paintGL();

    p_program_->bind();
    p_textures_->bindTexture(CAR_TEXTURE);
    p_textures_->bindTexture(CAR2_TEXTURE);
    p_program_->setUniformValue("stage1", CAR_TEXTURE);
    p_program_->setUniformValue("stage2", CAR2_TEXTURE);
    p_program_->setUniformValue("stage3", CAR_TEXTURE);
    p_program_->setUniformValue("car", CAR_TEXTURE);
    p_program_->setUniformValue("car2", CAR_TEXTURE);

    earth_.SetModels();
    earth_.Draw();

    moon_.SetModels();
    moon_.Draw();

    p_program_->release();

}


void OrbitalSimulation::update()
{
    if (Input::keyPressed(Qt::Key_T))
    {
        moon_.UpdateState(1);
    }
    Simulation::update();
}

