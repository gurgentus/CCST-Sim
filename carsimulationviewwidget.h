#ifndef CARSIMULATIONVIEWWIDGET_H
#define CARSIMULATIONVIEWWIDGET_H

#include "mainviewwidget.h"

class CarSimulationViewWidget : public MainViewWidget
{
public:
    explicit CarSimulationViewWidget(QWidget *parent = 0);
    void InitializeObjects(QVBoxLayout *layout, QVBoxLayout *control_layout, QOpenGLShaderProgram* shader,
                           Textures *textures, Terrain* terrain, Road* road, AdaptiveCar *car, Car *leadCar);

};

#endif // CARSIMULATIONVIEWWIDGET_H
