#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QSlider>
#include <QVBoxLayout>

#include "Sims/Simulation.hpp"
#include "SimulationInterface.hpp"

namespace Ui {
class Window;
}
class QScrollArea;

class Window : public QWidget
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = 0);

// list of functions corresponding to gui choices
public Q_SLOTS:
    void About();   // Help->About dialog text
    void TimerTick();   // called on every timer tick
    void ChangeSim();   // called on selection of a new simulation from the menu
    void HandleButton1();   // called on Start Simulation 1 button press
    void HandleButton2();   // called on Start Simulation 2 button press

private:
    // Methods responsible for reading plugins and populating the main menu
    void CreateActions();
    void CreateMenus();
    void LoadPlugins();
    void PopulateMenus(QObject *plugin);
    void AddToMenu(QObject *plugin, const QStringList &texts, QMenu *menu,
                   const char *member, QActionGroup *actionGroup = 0);

    // Default simulation object that inherits OpenGLWidget and contains methods
    // to interface with OpenGL.  All of the plugins are passed a pointer to
    // this object and use it as a light wrapper to call graphics functionality
    Simulation sim;

    // Pointer to the SimulationInterface that is implemented in the plugin.
    // Allows the main code to call plugin functionality.
    SimulationInterface* i_sim;

    // Time object for keeping simulation time
    QTimer* timer;

    // For dynamic plugin loading
    QDir plugins_dir;
    QStringList plugin_file_names;

    // GUI elements
    QMenu *file_menu;
    QMenu *simulations_menu;
    QMenu *help_menu;

    QAction *exit_action;
    QAction *start_sim_action;
    QAction *about_act;
    QAction *about_plugins_act;

    QActionGroup *sim_action_group;

    QScrollArea *scroll_area;

    QPushButton* m_button1;
    QPushButton* m_button2;

    //Simulation* current_simulation;
    //QPushButton* m_button;
    //int current_sim = 0;
    //QWidget *widget;
    //QMenu* menu;

    QHBoxLayout *mainLayout;
    QVBoxLayout *leftLayout;
    QHBoxLayout *topLeftLayout;
    QVBoxLayout *right_layout;

};

#endif // WINDOW_H
