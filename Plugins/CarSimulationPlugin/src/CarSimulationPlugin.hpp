#ifndef CARSIMULATIONPLUGIN_HPP
#define CARSIMULATIONPLUGIN_HPP

#include "SimulationInterface.hpp"

#include "Sims/Simulation.hpp"
#include "Objects/Terrain.hpp"
#include "Objects/Road.hpp"
#include "Car.hpp"
#include "Adaptivecar.hpp"

// CarSimulationPlugin class inherits from QObject and must
// implement the methods of SimulationInterface
// It also inherits the Controllable class, whose UpdateControls
// method can be used to change simulation settings
class CarSimulationPlugin : public QObject,
                            public SimulationInterface,
                            public Controllable
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.gensim.SimulationInterface")
    Q_INTERFACES(SimulationInterface)

public:
    CarSimulationPlugin();

    // 3D objects
    Terrain terrain_;
    Road road_;
    Car lead_car_;
    AdaptiveCar car_;

    QStringList Simulations() const override;

    // Pointer to the graphics program
    QOpenGLShaderProgram* p_program_;

    // Pointer to the simulation object
    Simulation* p_sim;

    QVBoxLayout* p_info_layout_;  // pointer to the information panel of the gui

    void InitializeObjects(QVBoxLayout *controls_layout, QVBoxLayout *outputs_layout, QOpenGLShaderProgram* shader,
                           Textures *textures_);

    // implement inherited method from Controllable
    void UpdateControls() override;

    // implement plugin interface methods
    void InitializeSimulation(Simulation& sim) override;
    void InitializeObjects(QVBoxLayout* info_layout) override;
    void InitializeGraphics() override;
    void InitializeGUI() override;
    void UpdateState(double dt) override;
    void PlotSimulation();

    void StartSimulation1() override;
    void StartSimulation2() override;
    void StopSimulation1() override;
    void StopSimulation2() override;

    void RenderGraphics() override;
    void CheckKeyboardInput() override;
    bool is_initialized() override;
    bool is_running() override;

private:
    bool is_initialized_ = false;
    bool is_running_ = false;
};

#endif // CARSIMULATIONPLUGIN_HPP

