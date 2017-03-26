#include "textures.h"

Textures::Textures()
{

}

bool Textures::loadTexture( const std::string& filename, unsigned int textureStage /*= 0*/ )
{
    // assert( textureStage < m_uiNumTextures );
    //DeleteTexture( m_GLTextures[textureStage] );

    //m_GLTextures[textureStage] = SOIL_load_OGL_texture( filename.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS );
    m_textures[textureStage] = new QOpenGLTexture(QOpenGLTexture::Target2D);
//    if ( m_GLTextures[textureStage] != 0 )
//    {
//        glBindTexture( GL_TEXTURE_2D, m_GLTextures[textureStage] );
//        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
//        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
//        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
//        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
//        glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
//        glBindTexture( GL_TEXTURE_2D, 0 );
//    }

    if (m_textures[textureStage] != NULL)
    {
        std::cout << "loading texture" << std::endl;
        m_textures[textureStage]->setData(QImage(QString::fromStdString(filename)).mirrored());
        m_textures[textureStage]->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        m_textures[textureStage]->setMagnificationFilter(QOpenGLTexture::Linear);
        m_textures[textureStage]->setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::Repeat);
        m_textures[textureStage]->setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::Repeat);

        //m_textures[textureStage] = texture;
        //m_textures.push_back(texture);
    }

    return ( m_textures[textureStage] != NULL );
}

void Textures::bindTexture(unsigned int texId)
{
    m_textures[texId]->bind(texId);
}

void Textures::cleanup()
{
    for (int i=0; i< 10; i++)
    {
        m_textures[i]->destroy();
    }
//    for (std::vector<QOpenGLTexture*>::iterator it = m_textures.begin(); it != m_textures.end(); ++it) {
//        (*it)->destroy();
//    }
}

//void Mesh::loadDefaultTextures()
//{
//    QOpenGLTexture *m_EarthTexture = new QOpenGLTexture(QOpenGLTexture::Target2D);
//    m_EarthTexture->setData(QImage(":/Textures/earth.dds").mirrored());
//    m_EarthTexture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
//    m_EarthTexture->setMagnificationFilter(QOpenGLTexture::Linear);
//    m_EarthTexture->setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::Repeat);
//    m_EarthTexture->setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::Repeat);

//    QOpenGLTexture *m_MoonTexture = new QOpenGLTexture(QOpenGLTexture::Target2D);
//    m_MoonTexture->setData(QImage(":/Textures/moon.dds").mirrored());
//    m_MoonTexture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
//    m_MoonTexture->setMagnificationFilter(QOpenGLTexture::Linear);
//    m_MoonTexture->setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::Repeat);
//    m_MoonTexture->setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::Repeat);

//    vector<QOpenGLTexture*> textures;
//    textures.push_back(m_EarthTexture);
//    textures.push_back(m_MoonTexture);

//    m_textures = textures;
//}
