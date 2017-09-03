#ifndef ORBITALSIMULATION_H
#define ORBITALSIMULATION_H

#include "Simulation.hpp"

#include "Common/Textures.hpp"
#include "Objects/Satellite.hpp"
#include "Nums/TwoBodySolver.hpp"

/* This is a helper class for orbital simulations, which can be inherited from
 * by new simulation plugins.  It contains objects/methods
 * by default, a vector of satellite objects and methods to add new satellites
 * TODO: change some of the objects to private
 */
class OrbitalSimulation
{
public:
    OrbitalSimulation();

    // 3D objects
    vector<Satellite*> satellites;

    // Pointer to the graphics program
    QOpenGLShaderProgram* p_program_;

    // Pointer to the simulation object
    Simulation* p_sim;

    QVBoxLayout* p_info_layout_;  // pointer to the information panel of the gui

    void AddSatellite(Satellite& planet);
    void InitializeObjects(QVBoxLayout *controls_layout, QVBoxLayout *outputs_layout, QOpenGLShaderProgram* shader,
                           Textures *textures_);
    void InitializeObjects(QVBoxLayout* info_layout);

private:
    void qNormalizeAngle(int &angle);
};

#endif // ORBITALSIMULATION_H

