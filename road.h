#ifndef ROAD_H
#define ROAD_H

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

class Road : public Mesh, public SBody
{
public:
    Road();
    //virtual ~Terrain();

    //void Terminate();
    bool setupDefaultMesh();
    void setModels();
    double distanceToRoad(double x, double z);

private:

    glm::mat4x4 m_LocalToWorldMatrix;
    glm::mat4x4 m_InverseLocalToWorldMatrix;

//    // The dimensions of the heightmap texture
//    glm::uvec2 m_HeightmapDimensions;

//    // The height-map value will be multiplied by this value
//    // before it is assigned to the vertex's Y-coordinate
//    float   m_fHeightScale;
//    // The vertex's X and Z coordinates will be multiplied by this
//    // for each step when building the terrain
//    float   m_fBlockScale;

//    bool LoadHeightmap( const std::string& filename, unsigned char bitsPerPixel, unsigned int width, unsigned int height );

};

#endif // ROAD_H
