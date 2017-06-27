#ifndef CONTROL_H
#define CONTROL_H

#include <QSlider>
#include <QVBoxLayout>
#include <QOpenGLWidget>
#include <QLabel>
#include <iostream>

#include "Objects/Controllable.hpp"

/* This class represents a controllable input.  Currently all controls that can be set from the GUI are set
 * using a slider so the class is  inhertied from QSlider class
 */

//class Controllable;

class Control : public QSlider
{
    Q_OBJECT
public:
    /* Constructor specifies a pointer to the layout on which to draw the slider, a pointer to the widget with the simulation that
     * the control will modify, a pointer to the simulation object SimObject that the control will modify,
     * min and max slider values, scale to go from slider values to the actual units of the control variable,
     * default value of the slider, label for the control variable and label for the units
     */
    Control(QVBoxLayout *layout = NULL, QOpenGLWidget *drawing_widget = NULL, Controllable* controllable = NULL,
            double min = 0, double max = 100, double scale = 1, double default_value = 0, QString label = "", QString units = "")
    : QSlider(Qt::Horizontal, layout->parentWidget())
    {
       scale_ = scale;
       setRange(min, max);
       p_controllable_ = controllable;
       setValue(default_value);

       // Add the control to the control panel
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

       // Connect the valueChanged signal of the slider to the setFValue function
       connect(this, SIGNAL(valueChanged(int)), SLOT(setFValue(int)));
    }
    ~Control();
    double value();

public Q_SLOTS:
    // Called on value changed
    void setFValue(int);

private:
    // Pointer to the label of the control
    QLabel* value_label;
    // Previous value of the control
    double old_value = 0;
    // Current value of the control
    double m_value = 0;
    // Scale factor to convert from slider values to actual values
    double scale_;
    // Pointer to the simulation window for drawing control effects
    QOpenGLWidget* drawing_widget_;
    // Pointer to the simulated object
    Controllable* p_controllable_;
};

#endif // CONTROL_H
