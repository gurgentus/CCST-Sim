#ifndef CONTROL_H
#define CONTROL_H

#include <QSlider>
#include <QVBoxLayout>
#include <QOpenGLWidget>
#include <QLabel>
//#include "myopenglwidget.h"
#include <iostream>

//class MyOpenGLWidget;
class SBody;

class Control : public QSlider
{
    Q_OBJECT
public:
    Control(QVBoxLayout *layout = NULL, QOpenGLWidget *drawing_widget = NULL, SBody* sbody = NULL,
            double min = 0, double max = 100, double scale = 1, double default_value = 0, QString label = "", QString units = "")
    : QSlider(Qt::Horizontal, layout->parentWidget())
    {
       scale_ = scale;
       setRange(min, max);
       //setSingleStep(step);
       QLabel *label1 = new QLabel(QString::number(min*scale)+" " + units, this);
       QLabel *label2 = new QLabel(label, this);
       value_label = new QLabel(QString::number(default_value), this);
       QLabel *label3 = new QLabel(units, this);
       QLabel *label4 = new QLabel(QString::number(max*scale)+" " + units, this);
       QGridLayout *control_layout = new QGridLayout;
       control_layout->addWidget(this, 0, 0, 1, 6);
       control_layout->addWidget(label1, 1, 0, 1, 1);
       control_layout->addWidget(label2, 1, 1, 1, 1);
       control_layout->addWidget(value_label, 1, 2, 1, 2);
       control_layout->addWidget(label3, 1, 4, 1, 1);
       control_layout->addWidget(label4, 1, 5, 1, 1);
       control_layout->setRowStretch(2,10);
       control_layout->setColumnStretch(2,10);
       layout->addLayout(control_layout);

       drawing_widget_ = drawing_widget;
       connect(this, SIGNAL(valueChanged(int)), SLOT(setFValue(int)));
       sbody_ = sbody;
       setValue(default_value);
    }
    ~Control();
    QLabel* value_label;
    double old_value = 0;
    double m_value = 0;
    int init_value = 0;
    bool decrease = false;
    double scale_;

public Q_SLOTS:
    // slots for xyz-rotation slider
    void setFValue(int);


//signals:
//    void valueChanged(int);

private:
    QOpenGLWidget* drawing_widget_;
    SBody* sbody_;
    //void onChange();

};

#endif // CONTROL_H
