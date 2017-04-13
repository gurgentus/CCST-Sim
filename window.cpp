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
    , terrain_(32, 2)
    , myOpenGLWidget(parent)
    , shader()
    , textures()
//  , ui(new Ui::Window)
{
    //ui->setupUi(this);

    right_layout = new QVBoxLayout; //new QVBoxLayout;
    QLabel* instructions = new QLabel("Press A to steer left; Press D to steer right.");
    //bottom_right_layout = new QVBoxLayout;

    //MyOpenGLWidget* myOpenGLWidget = new MyOpenGLWidget(parent);
    terrain_.SetShaderProgram(&shader);
    terrain_.setRoad(&road_);
    road_.SetShaderProgram(&shader);
    lead_car_.SetShaderProgram(&shader);
    car_.SetShaderProgram(&shader);
    myOpenGLWidget.InitializeObjects(right_layout, right_layout, &shader, &textures, &terrain_, &road_, &car_, &lead_car_);
    right_layout->addWidget(instructions);
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


    mainLayout->addLayout(right_layout);
//    mainLayout->addLayout(bottom_right_layout);
//    mainLayout->addLayout(fill_right_layout);
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
        currentSim = 1;
        lead_car_.InitializeState();
        car_.InitializeState();
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
        currentSim = 2;
        lead_car_.InitializeState();
        car_.InitializeState();
        timer->start(100);
        m_button2->setText("Stop Simulation 2");
        std::cout << "starting simulation" << std::endl;
    }
}

void Window::updateState()
{
    // dt in seconds
    double dt = qobject_cast<QTimer*>(sender())->interval() / 1000.0;
    // mps to angular velocity
    simTime = simTime + (0.1/200.0)*dt;
    lead_car_.UpdateState(dt, 200.1);

    if (currentSim == 1)
    {
        car_.Sense(lead_car_);
        car_.UpdateState1(dt);
    }
    if (currentSim == 2)
    {
        car_.Sense(lead_car_);
        car_.UpdateState2(dt);
    }

    myOpenGLWidget.camera_.setRotation(180, 0,1,0);;
    myOpenGLWidget.camera_.rotate((car_.xi()-1.5*pi)*180/pi, 0,1,0);
    myOpenGLWidget.camera_.setTranslation(QVector3D(car_.x()-0.5*cos(car_.xi()), 0.6, -car_.y()+0.5*sin(car_.xi())));

}


//void Window::keyPressEvent(QKeyEvent *e)
//{
//    if (e->key() == Qt::Key_Escape)
//        close();
//    else
//        QWidget::keyPressEvent(e);
//}
