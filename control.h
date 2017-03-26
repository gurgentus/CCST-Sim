#ifndef CONTROL_H
#define CONTROL_H

#include <QSlider>
#include <QVBoxLayout>
//#include "myopenglwidget.h"
#include "cst/transferfunction.h"
#include "cst/pfd.h"

class MyOpenGLWidget;

class Control : public QSlider
{
    Q_OBJECT
public:
    //explicit Control();
    Control(QVBoxLayout *layout = NULL, MyOpenGLWidget *drawingWidget = NULL)
    : QSlider(Qt::Horizontal, layout->parentWidget())
    {
        layout->addWidget(this);
        dWidget = drawingWidget;
        connect(this, SIGNAL(valueChanged(int)), SLOT(setFValue(int)));
    }
    ~Control();
    void stepResponse(double ss);
    void setTfControl(bool flag);
    int old_value = 0;
    int m_value = 0;
    int init_value = 0;
    bool decrease = false;


public Q_SLOTS:
    // slots for xyz-rotation slider
    void setFValue(int);
    void updateFromTF();

//signals:
//    void valueChanged(int);

private:
    MyOpenGLWidget* dWidget;
    double elapsedTime = 0;
    QTimer *timer;
    Pfd pfd;
    bool tfControl = false;
    //void onChange();

};

#endif // CONTROL_H
