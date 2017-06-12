#include "restricted3bodysimulation.h"

#include <iostream>
#include <cmath>

#include <QtCharts>

using namespace QtCharts;

void Restricted3BodySimulation::InitializeSimulation()
{
    double spatial_scale = 10000;

    sat_.setP_simulator(&simulator);
    sat_.setSpatial_scale(spatial_scale);
    sat_.setR(1000);
    sat_.setMesh_file(":/Data/Objects/nasa.obj");

    earth_.setP_simulator(&simulator);
    earth_.setSpatial_scale(spatial_scale);
    earth_.setR(5378);

    moon_.setP_simulator(&simulator);
    moon_.setSpatial_scale(spatial_scale);
    moon_.setR(6378*0.3);

    sat_.SetPositionFunction(static_cast<QVector3D (AbstractOdeSolver::*)()>(&Restricted3BodySolver::position));
    earth_.SetPositionFunction(static_cast<QVector3D (AbstractOdeSolver::*)()>(&Restricted3BodySolver::body1pos));
    moon_.SetPositionFunction(static_cast<QVector3D (AbstractOdeSolver::*)()>(&Restricted3BodySolver::body2pos));

    AddPlanet(moon_);
    AddPlanet(earth_);
    AddPlanet(sat_);
}

void Restricted3BodySimulation::InitializeGUI()
{
    sat_.InitializeOutputs();
    sat_.InitializeControls();
    PlotSimulation();

    camera_.translate(0,0,2);
}

void Restricted3BodySimulation::PlotSimulation()
{
    QLineSeries *series = new QLineSeries();

    // Run the full simulation to generate plots
    for (int i=0; i<2800; i++)
    {
        series->append(simulator.position().x()/100000,simulator.position().y()/100000);
        planets[2]->p_simulator()->UpdateState(100);
    }

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);

    // Plot and axes captions

    chart->setTitle("Spacecraft Trajectory");

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
