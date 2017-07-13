// window.cpp

#include <iostream>

#include <QPluginLoader>
#include <QtWidgets>
#include <QOpenGLContext>
//#include <ui_window.h>

#include "Window.hpp"

class MainViewWidget;

Window::Window(QWidget *parent)
    : QWidget(parent),
      scroll_area(new QScrollArea)
{

    // Populate the top menu
    CreateActions();
    CreateMenus();
    LoadPlugins();

    setWindowTitle(tr("GenELCSim"));

    // Create a button for starting the first simulation, make "this" the parent
    m_button1 = new QPushButton("Simulation 1", this);
    m_button1->setEnabled(false);
    m_button1->setGeometry(QRect(QPoint(100, 100),
    QSize(200, 50)));
    connect(m_button1, SIGNAL (released()), this, SLOT (HandleButton1()));


    // Create a button for starting the second simulation, make "this" the parent
    m_button2 = new QPushButton("Simulation 2", this);
    m_button2->setEnabled(false);
    m_button2->setGeometry(QRect(QPoint(100, 100),
    QSize(200, 50)));
    connect(m_button2, SIGNAL (released()), this, SLOT (HandleButton2()));

    // Splitter gui element to separate the OpenGL window from the information panel
    QSplitter *splitter = new QSplitter(this);

    // Layout the GUI
    QWidget* left_area = new QWidget;
    leftLayout = new QVBoxLayout;
    left_area->setLayout(leftLayout);

    QWidget* right_area = new QWidget;
    right_layout = new QVBoxLayout;
    right_area->setLayout(right_layout);

    splitter->addWidget(left_area);
    splitter->addWidget(right_area);

    mainLayout = new QHBoxLayout;
    mainLayout->addWidget(splitter);

    leftLayout->addWidget(scroll_area);
    leftLayout->addWidget(m_button1);
    leftLayout->addWidget(m_button2);

    scroll_area->setBackgroundRole(QPalette::Dark);

    // Initialize the 3D objects on the main panel
    sim.InitializeObjects(m_button1, m_button2);
    scroll_area->setWidget(&sim);

    this->setLayout(mainLayout);

    // Create the simulation timer
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(TimerTick()));
 }

void Window::CreateActions()
{
    // Create the static menu actions

    exit_action = new QAction(tr("&Leave"), this);
    exit_action->setShortcuts(QKeySequence::Quit);
    connect(exit_action, SIGNAL(triggered()), this, SLOT(close()));

    about_act = new QAction(tr("&Info"), this);
    connect(about_act, SIGNAL(triggered()), this, SLOT(About()));

    sim_action_group = new QActionGroup(this);

}

void Window::CreateMenus()
{
    // Create the static menu items
    QMenuBar* menu_bar = new QMenuBar(this);

    file_menu = menu_bar->addMenu(tr("&File"));
    file_menu->addSeparator();
    file_menu->addAction(exit_action);

    menu_bar->addSeparator();

    help_menu = menu_bar->addMenu(tr("&Help"));
    help_menu->addAction(about_act);

    simulations_menu = menu_bar->addMenu(tr("Simulations"));
}


void Window::LoadPlugins()
{
    // Load the plugins and populate the menu with the loaded simulations

    Q_FOREACH (QObject *plugin, QPluginLoader::staticInstances())
        PopulateMenus(plugin);

    plugins_dir = QDir(qApp->applicationDirPath());

#if defined(Q_OS_WIN)
    if (plugins_dir.dirName().toLower() == "debug" || plugins_dir.dirName().toLower() == "release")
        plugins_dir.cdUp();
#elif defined(Q_OS_MAC)
    if (plugins_dir.dirName() == "MacOS") {
        plugins_dir.cdUp();
        plugins_dir.cdUp();
        plugins_dir.cdUp();
    }
#endif
    plugins_dir.cd("plugins");
    Q_FOREACH (QString file_name, plugins_dir.entryList(QDir::Files)) {
        QPluginLoader loader(plugins_dir.absoluteFilePath(file_name));
        QObject *plugin = loader.instance();
        if (plugin) {
            PopulateMenus(plugin);
            plugin_file_names += file_name;
        }
    }

    simulations_menu->setEnabled(!simulations_menu->actions().isEmpty());
}

void Window::PopulateMenus(QObject *plugin)
{
    // Populate the menu with the simulation from the plugin
    SimulationInterface *i_sim = qobject_cast<SimulationInterface*>(plugin);
    if (i_sim)
        AddToMenu(plugin, i_sim->Simulations(), simulations_menu, SLOT(ChangeSim()));//, sim_action_group);

}

void Window::AddToMenu(QObject *plugin, const QStringList &sim_names,
                           QMenu *menu, const char *member,
                           QActionGroup *actionGroup)
{
    Q_FOREACH (QString name, sim_names)
    {
        QAction *action = new QAction(name, plugin);
        connect(action, SIGNAL(triggered()), this, member);
        menu->addAction(action);

//        QAction *action = qobject_cast<QAction *>(sender());
//        SimulationInterface *i_sim = qobject_cast<SimulationInterface *>(action->parent());


        if (actionGroup) {
            action->setCheckable(true);
            actionGroup->addAction(action);
        }
    }
}

void Window::ChangeSim()
{
    // Initialize a new simulation plugin
    QAction *action = qobject_cast<QAction *>(sender());
    i_sim = qobject_cast<SimulationInterface *>(action->parent());
    sim.p_sim = i_sim;

    if (!i_sim->is_initialized())
    {
        i_sim->InitializeSimulation(sim);
        i_sim->InitializeObjects(right_layout);
        i_sim->InitializeGraphics();
        i_sim->InitializeGUI();
    }
    if (i_sim->is_running())
    {
        m_button1->setText("Stop Simulation 1");
    }
    else
    {
        m_button1->setText("Simulation 1");
    }

}

void Window::About()
{
   QMessageBox::about(this, tr("Generic Estimation Learning and Control Simulator"),
            tr("The initial version is for control of 3DoF car, statistical orbit determination, "
               "and two/restricted three-body orbital mechanics problems."));
}

void Window::HandleButton1()
{
    if (m_button1->text() == "Stop Simulation 1")
    {
        timer->stop();
        i_sim->StopSimulation1();
        m_button1->setText("Simulation 1");
        std::cout << "Stopping simulation 1" << std::endl;
    }
    else
    {
        i_sim->StartSimulation1();
        timer->start(1000);
        m_button1->setText("Stop Simulation 1");
        std::cout << "Starting simulation 1" << std::endl;
    }
}
void Window::HandleButton2()
{
    if (m_button2->text() == "Stop Simulation 2")
    {
        timer->stop();
        i_sim->StopSimulation2();
        m_button2->setText("Simulation 2");
        std::cout << "Stopping simulation 2" << std::endl;
    }
    else
    {
        i_sim->StartSimulation2();
        timer->start(1000);
        m_button2->setText("Stop Simulation 2");
        std::cout << "Starting simulation 2" << std::endl;
    }
}

void Window::TimerTick()
{
    // dt in seconds
    double dt = qobject_cast<QTimer*>(sender())->interval() / 1000.0;
    i_sim->UpdateState(dt);
}
