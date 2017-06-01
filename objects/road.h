#ifndef ROAD_H
#define ROAD_H

#include <common/vertex.h>
#include <objects/mesh.h>
#include <common/textures.h>
#include <objects/sbody.h>

// Road object in the 2D car simulation
class Road : public Mesh, public SBody
{
public:
    Road();
    // setup the mesh
    bool SetupDefaultMesh(QVector4D texSignature = QVector4D( 0.0f, 1.0f, 0.0f, 1.0f ));
    // returns distance from the point (x,0,z) to the road
    double distanceToRoad(double x, double z);
};

#endif // ROAD_H
