#ifndef TERRAIN_H
#define TERRAIN_H

//#define GLEW_STATIC
//#include <gl/glew.h>

#include <vector>
#include <string>
#include <iostream>
#include <ctime>

//#include <boost/filesystem.hpp>
//#include <boost/filesystem/fstream.hpp>
//namespace fs = boost::filesystem;

#define GLM_SWIZZLE_XYZW

#include "Common/Vertex.hpp"
#include "Objects/Mesh.hpp"
#include "Common/Textures.hpp"
#include "Objects/SimObject.hpp"
#include "Objects/Road.hpp"
#include <QtOpenGL>


#define POSITION_ATTRIBUTE 0
#define COLOR_ATTRIBUTE 1
#define NORMAL_ATTRIBUTE 2
#define DIFFUSE_ATTRIBUTE 3
#define SPECULAR_ATTRIBUTE 4
#define TEXCOORD0_ATTRIBUTE 8
#define TEXCOORD1_ATTRIBUTE 9
#define TEXCOORD2_ATTRIBUTE 10

#define BUFFER_OFFSET(offset) ((void*)(offset))
#define MEMBER_OFFSET(s,m) ((char*)NULL + (offsetof(s,m)))

using namespace std;

class Terrain : public Mesh, public SimObject
{
public:
    Terrain( float heightScale = 500.0f, float blockScale = 2.0f );
    virtual ~Terrain();
    bool SetupDefaultMesh(QVector4D texSignature = QVector4D( 0.0f, 1.0f, 0.0f, 1.0f ));

    void setRoad(Road* road);
    Road* m_pRoad;
private:

    // The dimensions of the heightmap texture
    glm::uvec2 m_HeightmapDimensions;

    // The height-map value will be multiplied by this value
    // before it is assigned to the vertex's Y-coordinate
    float   m_fHeightScale;
    // The vertex's X and Z coordinates will be multiplied by this
    // for each step when building the terrain
    float   m_fBlockScale;

    bool LoadHeightmap( const std::string& filename, unsigned char bitsPerPixel, unsigned int width, unsigned int height );

};

#endif // TERRAIN_H
