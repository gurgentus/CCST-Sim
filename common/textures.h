#ifndef TEXTURES_H
#define TEXTURES_H

#include <QtOpenGL>
#include <iostream>


#define EARTH_TEXTURE 0
#define MOON_TEXTURE 1
#define GRASS_TEXTURE 2
#define ROCK_TEXTURE 3
#define SNOW_TEXTURE 4
#define ROAD_TEXTURE 5
#define CAR_TEXTURE 6
#define CAR2_TEXTURE 7

class Textures
{
public:
    Textures();
    bool loadTexture( const std::string& filename, unsigned int textureStage /*= 0*/ );
    void bindTexture(unsigned int texId);
    void bindAllTextures();
    void cleanup();
private:
    QOpenGLTexture* m_textures[10];
};

#endif // TEXTURES_H
