#include "sbody.h"
#include <iostream>

SBody::SBody()
    : m_LocalToWorldMatrix(1)
    , m_InverseLocalToWorldMatrix(1)
{
    size = 1;
    sizeControl = nullptr;
    controlLayout = nullptr;
    drawingWidget = nullptr;
    toPosRotMatrix.setToIdentity();
}


SBody::~SBody()
{
}

void SBody::initializeControls()
{
    sizeControl = new Control(controlLayout, drawingWidget);
    sizeControl->setValue(1);
}

void SBody::setControlPanel(QVBoxLayout* layout, MyOpenGLWidget *drawingWidget)
{
   controlLayout = layout;
   this->drawingWidget = drawingWidget;
}

void SBody::updateControls()
{

    if (sizeControl != nullptr)// && (sizeControl->m_value != sizeControl->old_value))
    {

        //toPosRotMatrix.setToIdentity();
        //scaleToSize((float)sizeControl->m_value);
        //sizeControl->old_value = sizeControl->m_value;
    }
}


