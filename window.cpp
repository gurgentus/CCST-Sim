// window.cpp

#include <QtWidgets>
#include <QOpenGLContext>
#include "window.h"
#include "ui_window.h"
#include <iostream>
#include "cst/transferfunction.h"
#include "cst/pfd.h"

//class MyOpenGLWidget;
class MainViewWidget;

Window::Window(QWidget *parent)
    : QWidget(parent)
    , g_Terrain(30, 2)
    , myOpenGLWidget(parent)
    , shader()
    , textures()
//  , ui(new Ui::Window)
{
    //ui->setupUi(this);
    rightLayout = new QVBoxLayout;
    //MyOpenGLWidget* myOpenGLWidget = new MyOpenGLWidget(parent);
    g_Terrain.setShaderProgram(&shader);
    g_Terrain.setRoad(&road);
    road.setShaderProgram(&shader);
    leadCar.setShaderProgram(&shader);
    car.setShaderProgram(&shader);
    myOpenGLWidget.initializeObjects(rightLayout, &shader, &textures, &g_Terrain, &road, &car, &leadCar);

    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    myOpenGLWidget.setSizePolicy(sizePolicy);


    QSlider* rotXSlider = new QSlider(Qt::Horizontal);
    rotXSlider->setLayoutDirection(Qt::LeftToRight);
    rotXSlider->setRange(0,360);
    QSlider* rotYSlider = new QSlider(Qt::Horizontal);
    rotYSlider->setLayoutDirection(Qt::LeftToRight);
    rotYSlider->setRange(0,360);
    QSlider* rotZSlider = new QSlider(Qt::Horizontal);
    rotZSlider->setLayoutDirection(Qt::LeftToRight);
    rotZSlider->setRange(0,360);

    connect(&myOpenGLWidget, SIGNAL(xRotationChanged(int)), rotXSlider, SLOT(setValue(int)));
    connect(&myOpenGLWidget, SIGNAL(yRotationChanged(int)), rotYSlider, SLOT(setValue(int)));
    connect(&myOpenGLWidget, SIGNAL(zRotationChanged(int)), rotZSlider, SLOT(setValue(int)));


    QHBoxLayout *topLeftLayout = new QHBoxLayout;
    topLeftLayout->addWidget(&myOpenGLWidget);

    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->addLayout(topLeftLayout);

    // Create the button, make "this" the parent
    m_button = new QPushButton("Start Simulation", this);
    // set size and location of the button
    m_button->setGeometry(QRect(QPoint(100, 100),
    QSize(200, 50)));

    // Connect button signal to appropriate slot
    connect(m_button, SIGNAL (released()), this, SLOT (handleButton()));
    leftLayout->addWidget(m_button);

//    leftLayout->addWidget(rotXSlider);
//    leftLayout->addWidget(rotYSlider);
//    leftLayout->addWidget(rotZSlider);

    //leftLayout->addWidget(caseCheckBox);
    //leftLayout->addWidget(backwardCheckBox);

    //rightLayout->addWidget(findButton);
    //rightLayout->addWidget(closeButton);
    //rightLayout->addStretch();
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(leftLayout);

    QSizePolicy fSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    //sizePolicy.setHorizontalStretch(0);
    //sizePolicy.setVerticalStretch(0);
    //rightLayout->addStretch(1);


    mainLayout->addLayout(rightLayout);
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
//    QGridLayout * layout = new QGridLayout(this);
//    QWidget * w;
//    QScrollArea * area;
    //ButtonGroup * group;

//    leftLayout->addWidget(w = new QButton(">>"), 0, 0);
//    w->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
//    w->setStyleSheet("border: 1px solid green");

//    layout->addWidget(area = new AdjustingScrollArea, 0, 1);
//    area->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
//    area->setStyleSheet("QScrollArea { border: 1px solid blue }");
//    //area->setWidget(group = new ButtonGroup);
//    layout->setColumnStretch(1, 1);

//    layout->addWidget(w = new QLabel("<<"), 0, 2);
//    w->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
//    w->setStyleSheet("border: 1px solid green");

//    layout->addWidget(w = new QPushButton("Add a widget"), 1, 0, 1, 3);
       //connect(w, SIGNAL(clicked()), group, SLOT(addButton()));
}

Window::~Window()
{
//    delete ui;
}

void Window::handleButton()
{
    // change the text

    // resize button
    //m_button->resize(100,100);
//    if (timer != NULL)
//    {
//        delete(timer);
//    }
    if (m_button->text() == "Stop Simulation")
    {
        timer->stop();
        m_button->setText("Start Simulation");
        std::cout << "stopping simulation" << std::endl;
    }
    else
    {
        timer->start(100);
        m_button->setText("Stop Simulation");
        std::cout << "starting simulation" << std::endl;

    }


}
void Window::updateState()
{
    // dt in seconds
    double dt = qobject_cast<QTimer*>(sender())->interval() / 1000.0;
    // mps to angular velocity
    simTime = simTime + (20.0/200.0)*dt;

    //simTime = simTime + 0.01;
    //car.rotate(0.01,1,0,1);
    //car.setRotation(simTime*180/3.14, 0,1,0);
    leadCar.updateState(dt, 20);
    leadCar.orient();
    leadCar.rotate(leadCar.xi-leadCar.xi_old, 0,1,0);
    leadCar.setTranslation(QVector3D(leadCar.x, 0.1, -leadCar.y));
    leadCar.toPosRotMatrix = leadCar.toMatrix();

    car.updateState2(dt, ((cos(car.xi)*(leadCar.x - car.x) +
                           sin(car.xi)*(leadCar.y - car.y))/fabs((cos(car.xi)*(leadCar.x - car.x) +
                           sin(car.xi)*(leadCar.y - car.y))))*sqrt((leadCar.x - car.x)*(leadCar.x - car.x) + (leadCar.y - car.y)*(leadCar.y - car.y)));
    car.orient();
//    car.rotate(-simTime*180/3.14, 0,1,0);
//    car.setTranslation(QVector3D(201*cos(simTime-0.08), 0.1, 201*sin(simTime-0.08)));
    car.rotate((car.xi-1.5*pi)*180/pi, 0,1,0);
    car.setTranslation(QVector3D(car.x, 0.1, -car.y));
    car.toPosRotMatrix = car.toMatrix();


    myOpenGLWidget.m_camera.setRotation(180, 0,1,0);
    //myOpenGLWidget.m_camera.rotate(-simTime*180/3.14, 0,1,0);
    myOpenGLWidget.m_camera.rotate((car.xi-1.5*pi)*180/pi, 0,1,0);
    //myOpenGLWidget.m_camera.setTranslation(QVector3D(202*cos(simTime-0.09), 1, 202*sin(simTime-0.09)));
    myOpenGLWidget.m_camera.setTranslation(QVector3D(car.x-5*cos(car.xi), 1, -car.y+5*sin(car.xi)));

}


//void Window::keyPressEvent(QKeyEvent *e)
//{
//    if (e->key() == Qt::Key_Escape)
//        close();
//    else
//        QWidget::keyPressEvent(e);
//}
