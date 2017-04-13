#include "control.h"

#include <iostream>
#include <QTimer>
#include <cmath>
#include "myopenglwidget.h"
#include <string>
//#include <Python.h>


//void Control::addToLayout(SBody* body)
//{

//    //m_slider = new QSlider(Qt::Horizontal);
//    //m_slider->setRange(0,10);
//    //m_slider->setValue(1);
//    //QObject::connect(m_slider, SIGNAL(valueChanged(int)), this, SLOT(setValue(float)));
//    //m_slider->connect(this, SIGNAL(valueChanged()), m_slider, SLOT(setValue(int)));
//    //layout->addWidget(this);
//}

Control::~Control()
{
    //delete timer;
}

void Control::setFValue(int value)
{           
    old_value = m_value;
    m_value = value*scale_;
    sbody_->UpdateControls();
    value_label->setText(QString::number(value*scale_));

}

//void Control::valueChanged()
//{

//}
