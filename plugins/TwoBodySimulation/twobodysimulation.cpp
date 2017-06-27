#include "twobodysimulation.h"
#include <QtCharts>
#include "nums/BoundaryValueProblem.hpp"
#include "Eigen/Dense"
#include <QStringList>

using namespace QtCharts;

QStringList TwoBodySimulation::Simulations() const
{
    return QStringList() << tr("Satellite Tracking") << tr("Satellite Tracking 2");
}

void TwoBodySimulation::InitializeSimulation()
{
    double spatial_scale = 400;

    sat_.setP_simulator(&simulator);
    sat_.setSpatial_scale(spatial_scale);
    sat_.setR(100);
    sat_.setMesh_file(":/Data/Objects/cube.obj");

    earth_.setP_simulator(&er_simulator);
    earth_.setSpatial_scale(spatial_scale);
    earth_.setR(6378);

    sat_.SetPositionFunction(static_cast<QVector3D (AbstractOdeSolver::*)()>(&TwoBodySolver::position));
    earth_.SetRotationFunction(static_cast<double (AbstractOdeSolver::*)()>(&EarthRotationSolver::rotation));

    AddPlanet(sat_);
    AddPlanet(earth_);

    sat_simulator.InitialConditions();
}

void TwoBodySimulation::InitializeGUI()
{
    sat_.InitializeOutputs();

    speedControl_ = new Control(control_layout_, this, this, 1, 100000, 1, 10, "Simulation Speed: ", "");
    t_output_ = new Output(output_layout_, 0, 1, "Time:", "seconds");
    u_output_ = new Output(output_layout_, 0, 1, "Uncertainty:", "km");
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
    if (currentSim == 1)
    {
        current_time_ = current_time_ + 10*dt;
        std::cout << "Current time: " << current_time_ << std::endl;
        std::cout << "Time step: " << 10*dt << std::endl;
        // simulate ground truth data
        sat_simulator.UpdateState(10*dt);
        std::cout << "GROUND INTEGRATING FORWARD: " << 10*dt << "s";
        std::normal_distribution<double> distribution(0.0,0.01);
        double noise = distribution(generator);
        const double omega_E = 2*M_PI/86164;
        Eigen::MatrixXd rotate = Eigen::MatrixXd(3,3);
        Eigen::VectorXd pos = Eigen::VectorXd(3);
        rotate << cos(omega_E*current_time_), sin(omega_E*current_time_), 0,
                -sin(omega_E*current_time_), cos(omega_E*current_time_), 0,
                0, 0, 1;

        // read measurements at this timestamp
        MeasurementPackage meas_package;
        meas_package.sensor_type_ = MeasurementPackage::STATION1;
        meas_package.raw_measurements_ = VectorXd(2);
        pos << -5127.51, -3794.16, 0;
        pos = rotate*pos;

        QVector3D rel = sat_simulator.position() - QVector3D(pos(0), pos(1), pos(2));
        double rho = rel.length();
        double rhodot = QVector3D::dotProduct(rel,
            QVector3D(sat_simulator.velocity().x()+pos(1)*omega_E,sat_simulator.velocity().y()-pos(0)*omega_E, sat_simulator.velocity().z()) )/rho;

        std::cout << "Ground data: " << sat_simulator.position().x() << " " << sat_simulator.position().y() << " " << sat_simulator.position().z()
                  << sat_simulator.velocity().x() << " " << sat_simulator.velocity().y() << " " << sat_simulator.velocity().z() << std::endl;
        std::cout << "Ground range: " << sat_simulator.position().length() << " " << rhodot << std::endl;
        std::cout << "Ground station cords: " << pos(0) << " " << pos(1) << " " << pos(2) << std::endl;
        meas_package.raw_measurements_ << rho + noise, rhodot + noise;
        meas_package.timestamp_ = current_time_;
        measurement_pack_list.push_back(meas_package);

        noise = distribution(generator);
        meas_package.sensor_type_ = MeasurementPackage::STATION2;
        meas_package.raw_measurements_ = VectorXd(2);
        pos << 3860.91, 3238.490, 3898.094;
        pos = rotate*pos;
        rel = sat_simulator.position() - QVector3D(pos(0), pos(1), pos(2));
        rho = rel.length();
        rhodot = QVector3D::dotProduct(rel,
            QVector3D(sat_simulator.velocity().x()+pos(1)*omega_E,sat_simulator.velocity().y()-pos(0)*omega_E, sat_simulator.velocity().z()) )/rho;
        meas_package.timestamp_ = current_time_;

        meas_package.raw_measurements_ << rho + noise, rhodot + noise;
        measurement_pack_list.push_back(meas_package);

        noise = distribution(generator);
        meas_package.sensor_type_ = MeasurementPackage::STATION3;
        meas_package.raw_measurements_ = VectorXd(2);
        pos << 549.505, -1380.872, 6182.197;
        pos = rotate*pos;
        rel = sat_simulator.position() - QVector3D(pos(0), pos(1), pos(2));
        rho = rel.length();
        rhodot = QVector3D::dotProduct(rel,
            QVector3D(sat_simulator.velocity().x()+pos(1)*omega_E,sat_simulator.velocity().y()-pos(0)*omega_E, sat_simulator.velocity().z()) )/rho;
        meas_package.timestamp_ = current_time_;
        meas_package.raw_measurements_ << rho + noise, rhodot + noise;
        measurement_pack_list.push_back(meas_package);

        if (measurement_pack_list.size() != 0) {

          // Call the fusion, which contains the decision logic for using
          // KF, EKF, UKF, dependent on the measurement type
          filter.ProcessMeasurement(measurement_pack_list);
          planets[0]->setPosition(QVector3D(filter.ekf_.x_(0),filter.ekf_.x_(1),filter.ekf_.x_(2)));
          double spatial_scale = planets[1]->getSpatial_scale();
          double eig = filter.ekf_.P_.operatorNorm();
          std::cout << eig << std::endl;

          planets[0]->setTranslation(filter.ekf_.x_(0)/spatial_scale, filter.ekf_.x_(2)/spatial_scale, filter.ekf_.x_(1)/spatial_scale);
          planets[0]->local_to_world_matrix_ = planets[0]->toMatrix();
          planets[0]->UpdateOutputs();
          std::cout << "Estimated data: " << filter.ekf_.x_(0) << " " << filter.ekf_.x_(1) << " " << filter.ekf_.x_(2)
                    << " " << filter.ekf_.x_(3) << " " << filter.ekf_.x_(4) << " " << filter.ekf_.x_(5) << std::endl;
          std::cout << "Estimated range: " << filter.ekf_.x_.segment(0,3).norm() << std::endl;
          sat_simulator.omt.orbit_desc(filter.ekf_.x_.segment(0,3), filter.ekf_.x_.segment(3,3), filter.ekf_.x_(6));

          //Eigen::VectorXd st2;
          //sat_simulator.getState(st2);
          //sat_simulator.omt.orbit_desc(sat_simulator.position(), sat_simulator.velocity(), st2(6));
          if (t_output_ != nullptr)
          {
              t_output_->setValue(current_time_); //setValue(simulator.omt.e);
          }

          if (u_output_ != nullptr)
          {
              u_output_->setValue(eig); //setValue(simulator.omt.e);
          }
          if (e_output_ != nullptr)
          {
              e_output_->setValue(sat_simulator.omt.e);
          }
          if (h_output_ != nullptr)
          {
              h_output_->setValue(sat_simulator.omt.h);
          }
          if (Omega_output_ != nullptr)
          {
              Omega_output_->setValue(sat_simulator.omt.Omega);
          }
          if (omega_output_ != nullptr)
          {
              omega_output_->setValue(sat_simulator.omt.omega);
          }
          if (i_output_ != nullptr)
          {
              i_output_->setValue(sat_simulator.omt.i);
          }

          Eigen::MatrixXd rotate_back(3,3);
          rotate_back << cos(-omega_E*current_time_), sin(-omega_E*current_time_), 0,
                  -sin(-omega_E*current_time_), cos(-omega_E*current_time_), 0,
                  0, 0, 1;

          Eigen::Vector3d Rx(3);
          Rx = rotate_back*filter.ekf_.x_.segment(0,3);
          // longitude and latitude
          double longitude,latitude;
          std::tie(longitude,latitude) =  Omt::right_ascension_and_declination(Rx);
          if (longitude_output_ != nullptr)
          {
              longitude_output_->setValue(longitude);
          }
          if (latitude_output_ != nullptr)
          {
              latitude_output_->setValue(latitude);
          }
        }
    }
}


Eigen::VectorXd rhs(double t, const Eigen::VectorXd& y)
{
    Eigen::VectorXd v = Eigen::VectorXd(2);
    v << y(1), 34*sin(t)+4*y(0)-3*y(1);
    return v;
}
Eigen::MatrixXd rhs_grad(double t, const Eigen::VectorXd& y)
{
    Eigen::MatrixXd v = Eigen::MatrixXd(2,2);
    v << 0,1,
         4,-3;
    return v;
}
Eigen::VectorXd bc(const Eigen::VectorXd& y1, const Eigen::VectorXd& y2)
{
    Eigen::VectorXd v = Eigen::VectorXd(2);
    v << y1(1)+5, y2(0)-4;
    return v;
}
Eigen::MatrixXd bc_grad1(const Eigen::VectorXd& y1, const Eigen::VectorXd& y2)
{
    Eigen::MatrixXd v = Eigen::MatrixXd(2,2);
    v << 0,1,
         0,0;
    return v;
}
Eigen::MatrixXd bc_grad2(const Eigen::VectorXd& y1, const Eigen::VectorXd& y2)
{
    Eigen::MatrixXd v = Eigen::MatrixXd(2,2);
    v << 0,0,
         1,0;
    return v;
}

void TwoBodySimulation::PlotSimulation()
{
    //std::cout << r_rel << " " << v_rel <<  "" << a_rel << std::endl;
    //omt.orbit_desc(QVector3D(-6045, -3490, 2500), QVector3D(-3.457, 6.618, 2.533), 398600);
    //omt.orbit_desc(80000, 1.4, 30*M_PI/180, 40*M_PI/180, 60*M_PI/180, 30*M_PI/180, 398600);
    Eigen::Vector3d res;
    //omt.change_coords(res, Eigen::Vector3d(6285.0,3628.6,0));
    //std::cout << res << std::endl;

//    double longit, lat;
//    simulator.omt.sat_long_lat(longit, lat, 230*M_PI/180, 45*60);
//    std::cout << longit*180/M_PI << " " << lat*180/M_PI << std::endl;

    DifferentialSystem ds(rhs, rhs_grad, bc, bc_grad1, bc_grad2, 0.0, M_PI);
    BoundaryValueProblem bvp(&ds, 101, 2);
    bvp.Solve();
    //bvp.WriteSolutionFile();

    std::cout << bvp.sol_vec() << std::endl;;


    QLineSeries *series = new QLineSeries();

    // Run the full simulation to generate plots
    for (int i=0; i < bvp.sol_vec().size()/2; i++)
    {
        series->append(bvp.Step(i), bvp.sol_vec()(2*i));
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

void TwoBodySimulation::check_files(ifstream& in_file, string& in_name) {
  if (!in_file.is_open()) {
    std::cerr << "Cannot open input file: " << in_name << std::endl;
    exit(EXIT_FAILURE);
  }
}
