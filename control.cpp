#include "control.h"

#include <iostream>
#include <QTimer>
#include <cmath>
#include "myopenglwidget.h"

#include <Python.h>


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

    std::cout << "updated " << value << " ";
    if (tfControl == true)
    {
        timer->stop();
        decrease = false;
        init_value = m_value;
        stepResponse(value-init_value);
    }
    else
    {
        old_value = m_value;
        m_value = value;
    }
    //QOpenGLWidget::update();
    //this->parentWidget()->parentWidget()->update();
    //this->parent()->update();
}

void Control::updateFromTF()
{
    //std::cout << "timeout" << std::endl;
    double vold = pfd.evaluateInverseLaplaceTransform(elapsedTime);
    elapsedTime = elapsedTime + qobject_cast<QTimer*>(sender())->interval() / 10.0;
    double v = pfd.evaluateInverseLaplaceTransform(elapsedTime);

    old_value = m_value;
    if (decrease == true)
    {
        m_value = init_value - v;
    }
    else
    {
        m_value = init_value + v;
    }

    std::cout << vold - v << std::endl;
    dWidget->update();
    std::cout << v << std::endl;

    if (std::abs(vold - v) < 0.001)
    {
        timer->stop();
        std::cout << "steady" << std::endl;
    }
}

void Control::setTfControl(bool flag)
{
    tfControl = flag;
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(updateFromTF()));
}

void Control::stepResponse(double ss)
{
    if (ss < 0)
    {
        decrease = true;
    }
    //std::cout << "SS: " << std::abs(ss)  << std::endl;
    if (std::abs(ss) > 0.01)
    {
        TransferFunction comp({1},{1,4,5,1.0/std::abs(ss),0});
        std::cout << comp << std::endl;
        comp.pfd(pfd);
        std::cout << pfd;
        pfd.printInverseLaplaceTransform();
        std::cout << "SS: " << ss << std::endl;
        //std:: cout << std::endl << pfd.evaluateInverseLaplaceTransform(2.1) << std::endl;
        //timer = new QTimer();
        //connect(timer, &QTimer::timeout, openGL, &GLWidget::animate);
        elapsedTime = 0;
        //timer->setInterval(10000);

        timer->start(100);
    }

//    TransferFunction tf1({1/0.0012047},{1,0.3,225});
//    TransferFunction tf2({0.08059, 1.78277, 23.3135},{1,0});

//    std::cout << tf1 << std::endl;
//    std::cout << tf2 << std::endl;


}

//void Control::valueChanged()
//{

//}
