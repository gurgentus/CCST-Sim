#ifndef SIMULATIONINTERFACE_HPP
#define SIMULATIONINTERFACE_HPP

#include <QtOpenGL>
#include <QtPlugin>
#include <QOpenGLWidget>
#include <QScrollArea>
#include <QOpenGLFunctions>
#include <QOpenGLTexture>

#include "Common/Textures.hpp"

class Simulation;
class QWidget;
class QString;
class QStringList;

class SimulationInterface
{
public:
    virtual ~SimulationInterface() {}

    virtual QStringList Simulations() const = 0;

    // Virtual methods that need to be implemented for custom simulations
    virtual void InitializeObjects(QVBoxLayout* info_layout) = 0;
    virtual void InitializeSimulation(Simulation& sim) = 0;
    virtual void InitializeGUI() = 0;
    virtual void UpdateState(double dt) = 0;
    virtual void StartSimulation1() = 0;
    virtual void StartSimulation2() = 0;
    virtual void StopSimulation1() = 0;
    virtual void StopSimulation2() = 0;
    virtual void InitializeGraphics() = 0;
    virtual void RenderGraphics() = 0;
    virtual bool is_initialized() = 0;
    virtual bool is_running() = 0;
};

#define SimulationInterface_iid  "org.gensim.SimulationInterface"

Q_DECLARE_INTERFACE(SimulationInterface, SimulationInterface_iid)

#endif // SIMULATIONINTERFACE_HPP
