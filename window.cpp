// window.cpp

#include <QtWidgets>
#include <QOpenGLContext>
#include <window.h>
#include <ui_window.h>
#include <iostream>

//#include "cst/transferfunction.h"
//#include "cst/pfd.h"

//class MyOpenGLWidget;
class MainViewWidget;

Window::Window(QWidget *parent)
    //: QMainWindow(parent)
    : QWidget(parent)
    , simulation()
    , orbital_simulation()
//  , ui(new Ui::Window)
{
    //ui->setupUi(this);

    // create menu bar
    QMenuBar* menu_bar = new QMenuBar(this);
    QAction* car_sim = new QAction("2D Car Simulation", this);
    QAction* orbit_sim = new QAction("Satellite Tracking", this);
    QAction* orbit_sim2 = new QAction("Restricted 3 Body Problem", this);
    //QAction* orbit_sim3 = new QAction("Satellite and Ground Tracking", this);

    //menu_bar->setNativeMenuBar(true);
    menu = new QMenu("Simulation");
    menu_bar->addMenu(menu);
    menu->addAction(car_sim);
    menu->addAction(orbit_sim);
    menu->addAction(orbit_sim2);
    //menu->addAction(orbit_sim3);
    menu_bar->addAction(menu->menuAction());

    connect(menu, SIGNAL(triggered(QAction*)), this, SLOT(setup_simulation(QAction*)));


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
        current_simulation->StartSimulation1();
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
        current_simulation->StartSimulation2();
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


void Window::setup_simulation(QAction *action)
{

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(updateState()));


    topLeftLayout = new QHBoxLayout;
    leftLayout = new QVBoxLayout;

    leftLayout->addLayout(topLeftLayout);

    menu->setEnabled(false);

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

    mainLayout = new QHBoxLayout;
    right_layout = new QVBoxLayout;
    right_layout->setSizeConstraint(QLayout::SetFixedSize);

    //clearWidgets(right_layout);

    if (action->text() == "2D Car Simulation")
    {
        current_simulation = &simulation;
    }
    if (action->text() == "Satellite Tracking")
    {
        current_simulation = &orbital_simulation;
        orbital_simulation.InitializeSimulation();
    }
    if (action->text() == "Restricted 3 Body Problem")
    {
        current_simulation = &restricted_3body;
        restricted_3body.InitializeSimulation();
    }
    if (action->text() == "Satellite and Ground Tracking")
    {
        current_simulation = &sat_simulation;
        sat_simulation.InitializeSimulation();
    }

    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(right_layout);

    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    //QSizePolicy fSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    this->setSizePolicy(sizePolicy);

    current_simulation->InitializeObjects(right_layout);

    if (action->text() == "Satellite Tracking")
    {
        orbital_simulation.InitializeGUI();
    }
    if (action->text() == "Restricted 3 Body Problem")
    {
        restricted_3body.InitializeGUI();
    }
    if (action->text() == "Satellite and Ground Tracking")
    {
        sat_simulation.InitializeGUI();
    }
    topLeftLayout->addWidget(current_simulation);

        //QMainWindow window;
//        window.setCentralWidget(chartView);
//        window.resize(400, 300);
//        window.show();

    this->setLayout(mainLayout);

}


//void Window::clearWidgets(QLayout * layout) {
//   if (! layout)
//      return;
//   while (auto item = layout->takeAt(0)) {
//      delete item->widget();
//      clearWidgets(item->layout());
//   }
//}

//void Window::keyPressEvent(QKeyEvent *e)
//{
//    if (e->key() == Qt::Key_Escape)
//        close();
//    else
//        QWidget::keyPressEvent(e);
//}



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

//        leftLayout->addWidget(rotXSlider);
//        leftLayout->addWidget(rotYSlider);
//        leftLayout->addWidget(rotZSlider);
