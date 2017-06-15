#include "twobodysimulation.h"
#include <QtCharts>

using namespace QtCharts;

void TwoBodySimulation::InitializeSimulation()
{
    double spatial_scale = 400;

    moon_.setP_simulator(&simulator);
    moon_.setSpatial_scale(spatial_scale);
    moon_.setR(100);
    moon_.setMesh_file(":/Data/Objects/cube.obj");

    earth_.setP_simulator(&er_simulator);
    earth_.setSpatial_scale(spatial_scale);
    earth_.setR(6378);

    moon_.SetPositionFunction(static_cast<QVector3D (AbstractOdeSolver::*)()>(&TwoBodySolver::position));
    earth_.SetRotationFunction(static_cast<double (AbstractOdeSolver::*)()>(&EarthRotationSolver::rotation));

    AddPlanet(moon_);
    AddPlanet(earth_);
}

void TwoBodySimulation::InitializeGUI()
{
    moon_.InitializeOutputs();

    speedControl_ = new Control(control_layout_, this, this, 1, 100000, 1, 10, "Simulation Speed: ", "");

    e_output_ = new Output(output_layout_, 0, 1, "Eccentricity:", "");
    h_output_ = new Output(output_layout_, 0, 1, "Specific Angular Momentum:", "km^2/s");
    i_output_ = new Output(output_layout_, 0, 180/M_PI, "Inclination:", "deg");
    Omega_output_ = new Output(output_layout_, 0, 180/M_PI, "Right Ascension of the Ascending Node:", "deg");
    omega_output_ = new Output(output_layout_, 0, 180/M_PI, "Argument of Perigee:", "deg");

    longitude_output_ = new Output(output_layout_, 0, 180/M_PI, "Longitude:", "deg");
    latitude_output_ = new Output(output_layout_, 0, 180/M_PI, "Latitude:", "deg");


    camera_.translate(0,0,80);

    PlotSimulation();
}

void TwoBodySimulation::UpdateState(double dt)
{
    double longit, lat, E, tm, theta;
    tm = sim_speed_*simulator.time();
    simulator.omt.e_anom_kepler(E, simulator.omt.e, tm*M_PI/simulator.omt.period);
    theta =2*atan(sqrt((1+simulator.omt.e)/(1-simulator.omt.e))*tan(E/2));

    simulator.omt.sat_long_lat(longit, lat, theta, tm);
    if (longitude_output_ != nullptr)
    {
        longitude_output_->setValue(longit);
    }
    if (latitude_output_ != nullptr)
    {
        latitude_output_->setValue(lat);
    }
    OrbitalSimulation::UpdateState(dt);
}
void TwoBodySimulation::PlotSimulation()
{
    std::cout << r_rel << " " << v_rel <<  "" << a_rel << std::endl;
    //omt.orbit_desc(QVector3D(-6045, -3490, 2500), QVector3D(-3.457, 6.618, 2.533), 398600);
    //omt.orbit_desc(80000, 1.4, 30*M_PI/180, 40*M_PI/180, 60*M_PI/180, 30*M_PI/180, 398600);
    Eigen::Vector3f res;
    //omt.change_coords(res, Eigen::Vector3f(6285.0,3628.6,0));
    //std::cout << res << std::endl;

//    double longit, lat;
//    simulator.omt.sat_long_lat(longit, lat, 230*M_PI/180, 45*60);
//    std::cout << longit*180/M_PI << " " << lat*180/M_PI << std::endl;
    if (e_output_ != nullptr)
    {
        e_output_->setValue(simulator.omt.e);
    }
    if (h_output_ != nullptr)
    {
        h_output_->setValue(simulator.omt.h);
    }
    if (Omega_output_ != nullptr)
    {
        Omega_output_->setValue(simulator.omt.Omega);
    }
    if (omega_output_ != nullptr)
    {
        omega_output_->setValue(simulator.omt.omega);
    }
    if (i_output_ != nullptr)
    {
        i_output_->setValue(simulator.omt.i);
    }

    QLineSeries *series = new QLineSeries();

    // Run the full simulation to generate plots
    for (int i=0; i < simulator.omt.period/100; i++)
    {
        series->append(simulator.position().x()/1000,simulator.position().z()/1000);
        planets[0]->p_simulator()->UpdateState(100);
    }

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);

    // Plot and axes captions

    chart->setTitle("Trajectory Projection");

    QValueAxis *axisX = new QValueAxis;
    axisX->setTitleText("x [km] 10^5");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis;
    axisY->setTitleText("y [km] 10^5");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // Add plot

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    output_layout_->addWidget(chartView);
}

void TwoBodySimulation::UpdateControls()
{
    if (speedControl_ != nullptr)
    {
            setSim_speed((double)speedControl_->value());
    }
}
