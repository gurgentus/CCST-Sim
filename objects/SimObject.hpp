#ifndef SBODY_H
#define SBODY_H

#include <QVector3D>
#include <QMatrix4x4>

#include "Objects/Mesh.hpp"
#include "Common/Textures.hpp"
#include "Common/Control.hpp"
#include "Common/Transform3d.hpp"
#include "Common/Output.hpp"
#include "Nums/TwoBodySolver.hpp"
#include "Objects/Controllable.hpp"

class QOpenGLWidget;

class SimObject: public Transform3D, public Controllable
{
public:
    SimObject();
    ~SimObject();

    // sets pointers to the control and output panels and the main opengl window from the main widget for any updates
    void SetControlOutputPanel(QVBoxLayout* control_layout, QVBoxLayout* output_layout, QOpenGLWidget* drawingWidget);

    // virtual functions to initialize the state, controls, and outputs
    virtual void InitializeState();
    virtual void InitializeControls();

    // gets called on changes to the control
    virtual void UpdateControls();

    // set/get methods
    AbstractOdeSolver *p_simulator() const;
    void setP_simulator(AbstractOdeSolver *p_simulator);
    double getSpatial_scale() const;
    void setSpatial_scale(double value);

protected:
    // convenience method that resets orientation before applying rotations
    virtual void ResetOrientation();

    // scaling factor for drawing the object
    double spatial_scale = 1;
    // simulation speed

    // size of the object
    float size = 1;

    // pointers to controls and the drawing area for this object
    Control* sizeControl;
    QVBoxLayout* control_layout_;
    QVBoxLayout* output_layout_;

    QOpenGLWidget* drawingWidget;

    // pointer to simulator if needed
    AbstractOdeSolver* p_simulator_;
};



#endif // SBODY_H
