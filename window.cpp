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
    myOpenGLWidget.initializeObjects(rightLayout, &shader, &textures, &g_Terrain, &road);

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
//       QWidget * w;
//       QScrollArea * area;
//       //ButtonGroup * group;

//       layout->addWidget(w = new QLabel(">>"), 0, 0);
//       w->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
//       w->setStyleSheet("border: 1px solid green");

//       layout->addWidget(area = new AdjustingScrollArea, 0, 1);
//       area->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
//       area->setStyleSheet("QScrollArea { border: 1px solid blue }");
//       //area->setWidget(group = new ButtonGroup);
//       layout->setColumnStretch(1, 1);

//       layout->addWidget(w = new QLabel("<<"), 0, 2);
//       w->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
//       w->setStyleSheet("border: 1px solid green");

//       layout->addWidget(w = new QPushButton("Add a widget"), 1, 0, 1, 3);
//       //connect(w, SIGNAL(clicked()), group, SLOT(addButton()));
}

Window::~Window()
{
//    delete ui;
}

QVBoxLayout* Window::getControlLayout()
{
    return rightLayout;
}

//void Window::keyPressEvent(QKeyEvent *e)
//{
//    if (e->key() == Qt::Key_Escape)
//        close();
//    else
//        QWidget::keyPressEvent(e);
//}
