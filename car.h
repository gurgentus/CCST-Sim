#ifndef CAR_H
#define CAR_H

#include "vertex.h"
#include "mesh.h"
#include "textures.h"
#include "sbody.h"


class Car : public Mesh, public SBody
{
public:
    Car();
    void InitializeState();
    void ResetOrientation();
    bool SetupDefaultMesh();
    void UpdateSpeed(double speed);
    void UpdateState(double dt, double radius);
    void InitializeControls();
    void UpdateControls();

    void SteerLeft();
    void SteerRight();

    double x() const;
    void setX(double x);

    double y() const;
    void setY(double y);

    double xi() const;
    void setXi(double xi);

    double dw() const;
    void setDw(double dw);

protected:
    Control* speedControl;
    double T_;
    double dw_;
    double v_;
    double xi_;
    double xi_old_;
    double x_;
    double y_;
    double angle_;
    double total_error_;
};

#endif // ROAD_H
