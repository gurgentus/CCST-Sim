#ifndef SBODY_H
#define SBODY_H

#include <QVector3D>
#include <QMatrix4x4>
#include "mesh.h"
#include "textures.h"
#include "control.h"
#include "transform3d.h"

class QOpenGLWidget;

class SBody: public Transform3D
{
    friend class Wing;
public:
    SBody();
    ~SBody();

    // sets the
    void SetControlOutputPanel(QVBoxLayout* control_layout, QVBoxLayout* output_layout, QOpenGLWidget* drawingWidget);
    virtual void InitializeControls();
    virtual void InitializeOutputs();
    virtual void UpdateControls();
    virtual void InitializeState();
    virtual void ResetOrientation();

protected:
    float size;
    // pointers to controls and the drawing area for this object
    Control* sizeControl;
    QVBoxLayout* control_layout_;
    QVBoxLayout* output_layout_;
    QOpenGLWidget* drawingWidget;

};



#endif // SBODY_H
