#ifndef SBODY_H
#define SBODY_H

#include <QVector3D>
#include <QMatrix4x4>
#include "mesh.h"
#include "textures.h"
#include "control.h"
#include "transform3d.h"
#include "nums/simulator.h"
#include "output.h"

class QOpenGLWidget;

class SBody: public Transform3D
{
    friend class Wing;
public:
    SBody();
    ~SBody();

    // sets pointers to the control and output panels and the main opengl window from the main widget for any updates
    void SetControlOutputPanel(QVBoxLayout* control_layout, QVBoxLayout* output_layout, QOpenGLWidget* drawingWidget);

    // virtual functions to initialize the state, controls, and outputs
    virtual void InitializeState();
    virtual void InitializeControls();
    virtual void InitializeOutputs();

    // gets called on changes to the control
    virtual void UpdateControls();


    // set/get methods
    Simulator *p_simulator() const;
    void setP_simulator(Simulator *p_simulator);

protected:
    // convenience method that resets orientation before applying rotations
    virtual void ResetOrientation();

    // size of the object
    float size;

    // pointers to controls and the drawing area for this object
    Control* sizeControl;
    QVBoxLayout* control_layout_;
    QVBoxLayout* output_layout_;
    QOpenGLWidget* drawingWidget;

    // pointer to simulator if needed
    Simulator* p_simulator_;
};



#endif // SBODY_H
