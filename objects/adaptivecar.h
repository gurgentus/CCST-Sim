#ifndef ADAPTIVECAR_H
#define ADAPTIVECAR_H

#include "car.h"
#include "output.h"

// car with adaptive cruise control
class AdaptiveCar : public Car
{
public:
    AdaptiveCar();
    void InitializeControls();
    void InitializeOutputs();

    // sets the distance_to_obstacle_ to the distance to the lead car
    void Sense(const AdaptiveCar::Car &lead_car);

    // apply control and simulate the dynamics for two simulations
    void UpdateState1(double dt);
    void UpdateState2(double dt);

    // update outputs based on the state values
    void UpdateOutputs();

private:
    // define outputs to be displayed
    Output* speed_output_;
    Output* steering_output_;
    Output* gap_;

    // define control parameters
    double distance_to_obstacle_;
    double current_error_;
};

#endif // ADAPTIVECAR_H
