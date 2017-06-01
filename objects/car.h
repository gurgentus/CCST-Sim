#ifndef CAR_H
#define CAR_H

#include <common/vertex.h>
#include <objects/mesh.h>
#include <common/textures.h>
#include <objects/sbody.h>


class Car : public Mesh, public SBody
{
public:
    Car();
    // setup car mesh for 2D car simulation
    bool SetupDefaultMesh(QVector4D texSignature = QVector4D( 0.0f, 1.0f, 0.0f, 1.0f ));
    // initialize state and control values
    void InitializeState();
    void InitializeControls();
    // update state based on gui control
    void UpdateControls();

    // apply control and simulate the dynamics for two simulations
    void UpdateState(double dt, double radius);



    // update state to steer left/right
    void SteerLeft();
    void SteerRight();

    // state set/get functions
    double x() const;
    void setX(double x);

    double y() const;
    void setY(double y);

    double xi() const;
    void setXi(double xi);

    double dw() const;
    void setDw(double dw);

protected:
    void ResetOrientation();

    Control* speedControl;

    // control variables
    double T_;
    double dw_;

    // state variables
    double v_;
    double xi_;
    double xi_old_;
    double x_;
    double y_;

    // helper variables
    double angle_;
    double total_error_;

private:
    void UpdateSpeed(double speed);
};

#endif // ROAD_H
