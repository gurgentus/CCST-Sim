#include "SimObject.hpp"
#include <iostream>

SimObject::SimObject()
{
    size = 1;
    sizeControl = nullptr;
    control_layout_ = nullptr;
    drawingWidget = nullptr;
}


SimObject::~SimObject()
{
}

void SimObject::SetControlOutputPanel(QVBoxLayout* control_layout, QVBoxLayout *output_layout, QOpenGLWidget *drawingWidget)
{
   control_layout_ = control_layout;
   output_layout_ = output_layout;
   this->drawingWidget = drawingWidget;
}

void SimObject::InitializeControls()
{
    //sizeControl = new Control(control_layout_, drawingWidget);
    //sizeControl->setValue(1);
}

//void SimObject::InitializeOutputs()
//{
//}

void SimObject::UpdateControls()
{

    if (sizeControl != nullptr)// && (sizeControl->m_value != sizeControl->old_value))
    {

        //toPosRotMatrix.setToIdentity();
        //scaleToSize((float)sizeControl->m_value);
        //sizeControl->old_value = sizeControl->m_value;
    }
}


void SimObject::InitializeState()
{

}

void SimObject::ResetOrientation()
{

}

double SimObject::getSpatial_scale() const
{
    return spatial_scale;
}

void SimObject::setSpatial_scale(double value)
{
    spatial_scale = value;
}

AbstractOdeSolver *SimObject::p_simulator() const
{
    return p_simulator_;
}

void SimObject::setP_simulator(AbstractOdeSolver *p_simulator)
{
    p_simulator_ = p_simulator;
}

