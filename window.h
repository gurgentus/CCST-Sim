// window.h

#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QSlider>
#include <QVBoxLayout>
#include <common/textures.h>

#include <carsimulation.h>
#include <orbitalsimulation.h>

namespace Ui {
class Window;
}

class Window : public QWidget //QMainWindow
{
    Q_OBJECT
public:
    explicit Window(QWidget *parent = 0);
    ~Window();
    //QVBoxLayout* getControlLayout();
public Q_SLOTS:
    void updateState();
    void handleButton1();
    void handleButton2();
    void setup_simulation(QAction*action);
private:
    Ui::Window *ui;
    QTimer* timer;
    double simTime = 0;

    CarSimulation simulation;
    OrbitalSimulation orbital_simulation;
    Simulation* current_simulation;
    QPushButton* m_button;
    QPushButton* m_button1;
    QPushButton* m_button2;
    int current_sim = 0;

    constexpr static const float pi = 3.1415926535897932384626433832795f;
    constexpr static const float _2pi = 2.0f * pi;

    QWidget *widget;

    QMenu* menu;

    QHBoxLayout *mainLayout;
    QVBoxLayout *leftLayout;
    QHBoxLayout *topLeftLayout;
    QVBoxLayout *right_layout;

//    void clearWidgets(QLayout * layout);

};

#endif // WINDOW_H
