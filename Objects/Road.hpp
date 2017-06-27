#ifndef ROAD_H
#define ROAD_H

#include "Common/Vertex.hpp"
#include "Common/Textures.hpp"
#include "Objects/Mesh.hpp"
#include "Objects/SimObject.hpp"

// Road object in the 2D car simulation
class Road : public Mesh, public SimObject
{
public:
    Road();
    // setup the mesh
    bool SetupDefaultMesh(QVector4D texSignature = QVector4D( 0.0f, 1.0f, 0.0f, 1.0f ));
    // returns distance from the point (x,0,z) to the road
    double distanceToRoad(double x, double z);
};

#endif // ROAD_H
