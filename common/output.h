#ifndef OUTPUT_H
#define OUTPUT_H

#include <QVBoxLayout>
#include <QOpenGLWidget>
#include <QLabel>

/* This class represents an output of the simulation/dynamics. The class is  inhertied from QLabel class
 * for easy update in the output panel of the GUI.
 */

class Output : public QLabel
{
    Q_OBJECT
public:
    /* Constructor specifies a pointer to the layout on which to draw the output label, default value,
     * scale factor, label of the output, units of the output for display
     */
    Output(QVBoxLayout *layout = NULL, double value = 0, double scale = 1, QString label = "", QString units = "")
        : QLabel(QString::number(value*scale), layout->parentWidget())
    {
       // label to display the output value
       QLabel *label1 = new QLabel(label, this);
       // label to display the units
       QLabel *label2 = new QLabel(units, this);

       // place the output display in the output panel
       QGridLayout *output_layout = new QGridLayout;
       output_layout->addWidget(label1, 0, 0, 1, 1);
       output_layout->addWidget(this, 0, 1, 1, 2);
       output_layout->addWidget(label2, 0, 3, 1, 1);
       layout->addLayout(output_layout);
       output_layout->setColumnStretch(4,10);
    }
};

#endif // OUTPUT_H

