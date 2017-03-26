#ifndef TEXTURES_H
#define TEXTURES_H

#include <QtOpenGL>

#include <iostream>

class Textures
{
public:
    Textures();
    bool loadTexture( const std::string& filename, unsigned int textureStage /*= 0*/ );
    void bindTexture(unsigned int texId);
    void cleanup();
private:
    QOpenGLTexture* m_textures[10];
};

#endif // TEXTURES_H
