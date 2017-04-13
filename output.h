#ifndef OUTPUT_H
#define OUTPUT_H

#include <QVBoxLayout>
#include <QOpenGLWidget>
#include <QLabel>
#include <iostream>

class Output : public QLabel
{
    Q_OBJECT
public:
    Output(QVBoxLayout *layout = NULL, double value = 0, double scale = 1, QString label = "", QString units = "")
        : QLabel(QString::number(value*scale), layout->parentWidget())
    {
       QLabel *label1 = new QLabel(label, this);
       QLabel *label2 = new QLabel(units, this);
       //setText(label);
       QGridLayout *output_layout = new QGridLayout;
       output_layout->addWidget(label1, 0, 0, 1, 1);
       output_layout->addWidget(this, 0, 1, 1, 2);
       output_layout->addWidget(label2, 0, 3, 1, 1);
       layout->addLayout(output_layout);
       output_layout->setColumnStretch(4,10);
    }
};

#endif // OUTPUT_H

