// window.cpp

#include <QtWidgets>
#include <QOpenGLContext>
#include "window.h"
#include "ui_window.h"
#include <iostream>

//#include "cst/transferfunction.h"
//#include "cst/pfd.h"

//class MyOpenGLWidget;
class MainViewWidget;

Window::Window(QWidget *parent)
    : QWidget(parent)
    , simulation(parent)
    , orbital_simulation()
//  , ui(new Ui::Window)
{
    //ui->setupUi(this);
    int sim_type = 1;

    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);

    QHBoxLayout *topLeftLayout = new QHBoxLayout;
    QVBoxLayout *leftLayout = new QVBoxLayout;

    if (sim_type == 1)
    {
        orbital_simulation.setSizePolicy(sizePolicy);
//        QSlider* rotXSlider = new QSlider(Qt::Horizontal);
//        rotXSlider->setLayoutDirection(Qt::LeftToRight);
//        rotXSlider->setRange(0,360);
//        QSlider* rotYSlider = new QSlider(Qt::Horizontal);
//        rotYSlider->setLayoutDirection(Qt::LeftToRight);
//        rotYSlider->setRange(0,360);
//        QSlider* rotZSlider = new QSlider(Qt::Horizontal);
//        rotZSlider->setLayoutDirection(Qt::LeftToRight);
//        rotZSlider->setRange(0,360);

//        connect(&orbital_simulation, SIGNAL(xRotationChanged(int)), rotXSlider, SLOT(setValue(int)));
//        connect(&orbital_simulation, SIGNAL(yRotationChanged(int)), rotYSlider, SLOT(setValue(int)));
//        connect(&orbital_simulation, SIGNAL(zRotationChanged(int)), rotZSlider, SLOT(setValue(int)));

        topLeftLayout->addWidget(&orbital_simulation);

//        leftLayout->addWidget(rotXSlider);
//        leftLayout->addWidget(rotYSlider);
//        leftLayout->addWidget(rotZSlider);
        current_simulation = &orbital_simulation;
    }
    else
    {
        simulation.setSizePolicy(sizePolicy);
        topLeftLayout->addWidget(&simulation);
        current_simulation = &simulation;
    }
    leftLayout->addLayout(topLeftLayout);

    // Create the button, make "this" the parent
    m_button1 = new QPushButton("Simulation 1", this);
    m_button1->setGeometry(QRect(QPoint(100, 100),
    QSize(200, 50)));
    connect(m_button1, SIGNAL (released()), this, SLOT (handleButton1()));
    leftLayout->addWidget(m_button1);

    // Create the button, make "this" the parent
    m_button2 = new QPushButton("Simulation 2", this);
    m_button2->setGeometry(QRect(QPoint(100, 100),
    QSize(200, 50)));
    connect(m_button2, SIGNAL (released()), this, SLOT (handleButton2()));
    leftLayout->addWidget(m_button2);


    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(leftLayout);

    QSizePolicy fSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    if (sim_type == 1)
    {
        mainLayout->addLayout(orbital_simulation.right_layout);
    }
    else
    {
        mainLayout->addLayout(simulation.right_layout);
    }

    setLayout(mainLayout);
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(updateState()));

//    std::cout << std::endl;
//    std::vector<ComplexNumber> pols;
//    TransferFunction p(tf1*tf2/(TransferFunction({1},{1})+tf1*tf2));
//    p.poles(pols);
//    for (std::vector<ComplexNumber>::iterator it = pols.begin(); it != pols.end(); ++it)
//    {
//        std::cout << *it;
//        std::cout << std::endl;
//    }

}

Window::~Window()
{
//    delete ui;
}

void Window::handleButton1()
{
    if (m_button1->text() == "Stop Simulation 1")
    {
        timer->stop();
        m_button1->setText("Simulation 1");
        std::cout << "stopping simulation" << std::endl;
    }
    else
    {
        current_simulation->currentSim = 1;
        current_simulation->start_simulation1();
        timer->start(100);
        m_button1->setText("Stop Simulation 1");
        std::cout << "starting simulation" << std::endl;
    }
}
void Window::handleButton2()
{
    if (m_button2->text() == "Stop Simulation 2")
    {
        timer->stop();
        m_button2->setText("Simulation 2");
        std::cout << "stopping simulation" << std::endl;
    }
    else
    {
        current_simulation->currentSim = 2;
        current_simulation->start_simulation2();
        timer->start(100);
        m_button2->setText("Stop Simulation 2");
        std::cout << "starting simulation" << std::endl;
    }
}

void Window::updateState()
{
    // dt in seconds
    double dt = qobject_cast<QTimer*>(sender())->interval() / 1000.0;
    current_simulation->UpdateState(dt);
}


//void Window::keyPressEvent(QKeyEvent *e)
//{
//    if (e->key() == Qt::Key_Escape)
//        close();
//    else
//        QWidget::keyPressEvent(e);
//}
