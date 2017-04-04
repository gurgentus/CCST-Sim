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
    void orient();
    bool setupDefaultMesh();
    void setModels();
    //double distanceToRoad(double x, double z);
    void updateState(double dt, double velocity);
    void updateState2(double dt, double gap);
    double T;
    double dw;

    double v;
    double xi;
    double xi_old;
    double x;
    double y;
    double angle;

};

#endif // ROAD_H
