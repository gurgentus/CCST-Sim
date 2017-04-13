#include "adaptivecar.h"

AdaptiveCar::AdaptiveCar()
{
    distance_to_obstacle_ = 0;
}

void AdaptiveCar::Sense(const Car& lead_car)
{
    distance_to_obstacle_ = ((cos(xi_)*(lead_car.x() - x_) +
                           sin(xi_)*(lead_car.y() - y_))/fabs((cos(xi_)*(lead_car.x() - x_) +
                           sin(xi_)*(lead_car.y() - y_))))*sqrt((lead_car.x() - x_)*(lead_car.x() - x_) +
                           (lead_car.y() - y_)*(lead_car.y() - y_));

}

void AdaptiveCar::InitializeControls()
{
}

void AdaptiveCar::InitializeOutputs()
{
    speed_output = new Output(output_layout_, 0, "Speed: ", "m/s");
    steering_output_ = new Output(output_layout_, 0, "Steering Angle: ", "rad");
    gap_ = new Output(output_layout_, 0, "Gap: ", "m");

}

// this controls the main car with simple proportional controller
void AdaptiveCar::UpdateState1(double dt)
{
    double mass = 1000;
    double drag = 1;
    double desired_gap = 1;

    double k_p = 100;
    // control
    T_ = k_p*(distance_to_obstacle_ - desired_gap);


    // simulate
    xi_ = xi_ + (v_*tan(dw_)/4.0)*dt;
    x_ = x_ + v_*cos(xi_)*dt;
    y_ = y_ + v_*sin(xi_)*dt;
    v_ = v_ + dt*(T_*cos(dw_)*cos(dw_)-drag*v_)/mass;

    // cap if velocity is too large
    if (v_ > 2)
    {
        v_ = 2;
    }

    std::cout << "steering angle (dw): " << dw_ << ", car orientation (xi): " << xi_ << ", current gap: " << distance_to_obstacle_ << "m, current velocity: " << v_ << "m/s" << std::endl;


    ResetOrientation();
    rotate((xi_-1.5*pi)*180/pi, 0,1,0);
    setTranslation(QVector3D(x_, 0.51, -y_));
    local_to_world_matrix_ = toMatrix();
    UpdateOutputs();

}



//void AdaptiveCar::UpdateControls()
//{
//    if (steering_output_ != nullptr)
//    {
//        dw_ =(double)steering_output_->m_value;
//    }
//}

void AdaptiveCar::UpdateOutputs()
{
    if (speed_output != nullptr)// && (sizeControl->m_value != sizeControl->old_value))
    {
        speed_output->setText(QString::number(v_));
        gap_->setText(QString::number(distance_to_obstacle_));
        steering_output_->setText(QString::number(dw_));
        //toPosRotMatrix.setToIdentity();
        //scaleToSize((float)sizeControl->m_value);
        //sizeControl->old_value = sizeControl->m_value;
    }
}

// this controls the main car with the fancy student controller
void AdaptiveCar::UpdateState2(double dt)
{
    // control
    double mass = 1000;
    double drag = 1;
    double desired_gap = 0.5;
    double k_p = (-3*mass)/(cos(dw_)*sin(xi_));
    double k_i = -mass/(cos(dw_)*sin(xi_));
    double k_d = (drag-3*mass)/(cos(dw_)*sin(xi_));

    double m_prev_error = current_error_;
    current_error_ = distance_to_obstacle_ - desired_gap;

    total_error_ = total_error_ + current_error_*dt;
    double T_ = k_p*current_error_;
    T_ += k_d*(current_error_-m_prev_error)/dt;
    T_ += k_i*total_error_;


    // simulate
    xi_ = xi_ + (v_*tan(dw_)/4.0)*dt;
    x_ = x_ + v_*cos(xi_)*dt;
    y_ = y_ + v_*sin(xi_)*dt;
    v_ = v_ + dt*(T_*cos(dw_)*cos(dw_)-drag*v_)/mass;
    std::cout << "steering angle (dw): " << dw_ << ", car orientation (xi): " << xi_ << ", current gap: " << distance_to_obstacle_ << "m, current velocity: " << v_ << "m/s" << std::endl;

    ResetOrientation();
    rotate((xi_-1.5*pi)*180/pi, 0,1,0);
    setTranslation(QVector3D(x_, 0.51, -y_));
    local_to_world_matrix_ = toMatrix();
    UpdateOutputs();
}
