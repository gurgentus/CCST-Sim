#ifndef SBODY_H
#define SBODY_H

#include <QVector3D>
#include <QMatrix4x4>
#include "mesh.h"
#include "textures.h"
#include "control.h"
#include "transform3d.h"
//#include "myopenglwidget.h"

class MyOpenGLWidget;

class SBody: public Transform3D
{
    friend class Wing;
public:
    SBody();
    ~SBody();

    // sets the
    void setControlPanel(QVBoxLayout* layout, MyOpenGLWidget* drawingWidget);
    virtual void initializeControls();
    virtual void updateControls();

    QMatrix4x4 toPosRotMatrix;

protected:
    float size;
    int m_modelToWorld;

    glm::mat4x4 m_LocalToWorldMatrix;
    glm::mat4x4 m_InverseLocalToWorldMatrix;

    // pointers to controls and the drawing area for this object
    Control* sizeControl;
    QVBoxLayout* controlLayout;
    MyOpenGLWidget* drawingWidget;

};



#endif // SBODY_H
