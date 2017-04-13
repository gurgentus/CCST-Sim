#ifndef ROAD_H
#define ROAD_H

#include "vertex.h"
#include "mesh.h"
#include "textures.h"
#include "sbody.h"

class Road : public Mesh, public SBody
{
public:
    Road();
    bool SetupDefaultMesh();
    double distanceToRoad(double x, double z);
};

#endif // ROAD_H
