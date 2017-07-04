#include "Textures.hpp"

Textures::Textures()
{

}

bool Textures::loadTexture( const std::string& filename, unsigned int textureStage /*= 0*/ )
{
    m_textures[textureStage] = new QOpenGLTexture(QOpenGLTexture::Target2D);

    if (m_textures[textureStage] != NULL)
    {
        std::cout << "loading texture" << std::endl;
        m_textures[textureStage]->setData(QImage(QString::fromStdString(filename)).mirrored());
        m_textures[textureStage]->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        m_textures[textureStage]->setMagnificationFilter(QOpenGLTexture::Linear);
        m_textures[textureStage]->setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::Repeat);
        m_textures[textureStage]->setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::Repeat);
    }

    return ( m_textures[textureStage] != NULL );
}

void Textures::bindTexture(unsigned int texId)
{
    m_textures[texId]->bind(texId);
}

void Textures::bindAllTextures()
{
    bindTexture(GRASS_TEXTURE);
    bindTexture(ROCK_TEXTURE);
    bindTexture(SNOW_TEXTURE);
    bindTexture(ROAD_TEXTURE);
    bindTexture(CAR_TEXTURE);
    bindTexture(CAR2_TEXTURE);
}

void Textures::cleanup()
{
    for (int i=0; i< 10; i++)
    {
        m_textures[i]->destroy();
    }

}
