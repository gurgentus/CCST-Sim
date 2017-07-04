#include "OrbitalSimulation.hpp"

OrbitalSimulation::OrbitalSimulation()
{
}

void OrbitalSimulation::AddSatellite(Satellite& planet)
{
    satellites.push_back(&planet);
}

//void OrbitalSimulation::InitializeObjects(QVBoxLayout* info_layout)
//{
//    instructions->setText("Move the slider to change the simulation speed. \nRight-click with the mouse and use the keyboard keys \nto move around and zoom in/out.");
//    info_layout->addWidget(instructions);
//    InitializeObjects(info_layout, info_layout, &shader, &textures_);

//    for (int i=0; i< planets.size(); i++)
//    {
//        if (planets[i]->p_simulator() != nullptr)
//        {
//             planets[i]->p_simulator()->InitialConditions();
//        }
//    }
//}

void OrbitalSimulation::InitializeObjects(QVBoxLayout *controls_layout, QVBoxLayout* outputs_layout, QOpenGLShaderProgram* shader,
                                       Textures* textures)
{
    p_program_ = shader;
    p_sim->SetControlOutputPanel(controls_layout, outputs_layout);
    for (unsigned long i=0; i< satellites.size(); i++)
    {
        satellites[i]->SetShaderProgram(p_program_);
        satellites[i]->SetControlOutputPanel(controls_layout, outputs_layout, p_sim);
    }

    for (unsigned long i=0; i< satellites.size(); i++)
    {
        satellites[i]->InitializeState();
        if (satellites[i]->p_simulator()) {
            satellites[i]->p_simulator()->InitialConditions();
        }
    }

    //Simulation::InitializeObjects(shader, textures);
}


//void OrbitalSimulation::UpdateState(double dt)
//{
//    for (unsigned long  i=0; i< planets.size(); i++)
//    {
//        if (planets[i]->p_simulator() != nullptr)
//        {
//             planets[i]->UpdateState(dt);
//        }
//    }

//}

void OrbitalSimulation::qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360)
        angle -= 360 * 16;
}
