#include "sbody.h"
#include <iostream>

SBody::SBody()
{
    size = 1;
    sizeControl = nullptr;
    control_layout_ = nullptr;
    drawingWidget = nullptr;
}


SBody::~SBody()
{
}

void SBody::SetControlOutputPanel(QVBoxLayout* control_layout, QVBoxLayout *output_layout, QOpenGLWidget *drawingWidget)
{
   control_layout_ = control_layout;
   output_layout_ = output_layout;
   this->drawingWidget = drawingWidget;
}

void SBody::InitializeControls()
{
    sizeControl = new Control(control_layout_, drawingWidget);
    sizeControl->setValue(1);
}

void SBody::InitializeOutputs()
{
}

void SBody::UpdateControls()
{

    if (sizeControl != nullptr)// && (sizeControl->m_value != sizeControl->old_value))
    {

        //toPosRotMatrix.setToIdentity();
        //scaleToSize((float)sizeControl->m_value);
        //sizeControl->old_value = sizeControl->m_value;
    }
}


void SBody::InitializeState()
{

}

void SBody::ResetOrientation()
{

}

