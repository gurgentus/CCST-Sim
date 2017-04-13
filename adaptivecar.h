#ifndef ADAPTIVECAR_H
#define ADAPTIVECAR_H

#include "car.h"
#include "output.h"

class AdaptiveCar : public Car
{
public:
    AdaptiveCar();
    void Sense(const AdaptiveCar::Car &lead_car);
    void UpdateState1(double dt);
    void UpdateState2(double dt);
    void InitializeControls();
    void InitializeOutputs();
    //void UpdateControls();
    void UpdateOutputs();
private:
    Output* speed_output;
    Output* steering_output_;
    Output* gap_;
    double distance_to_obstacle_;
    double current_error_;
};

#endif // ADAPTIVECAR_H
