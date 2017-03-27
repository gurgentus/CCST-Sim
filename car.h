#ifndef CAR_H
#define CAR_H

#include "vertex.h"
#include "mesh.h"
#include "textures.h"
#include "sbody.h"

#define EARTH_TEXTURE 0
#define MOON_TEXTURE 1
#define GRASS_TEXTURE 2
#define ROCK_TEXTURE 3
#define SNOW_TEXTURE 4
#define ROAD_TEXTURE 5


class Car : public Mesh, public SBody
{
public:
    Car();
    bool setupDefaultMesh();
    void setModels();
    //double distanceToRoad(double x, double z);

private:

    glm::mat4x4 m_LocalToWorldMatrix;
    glm::mat4x4 m_InverseLocalToWorldMatrix;

};

#endif // ROAD_H
