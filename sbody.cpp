#include "sbody.h"
#include <iostream>

SBody::SBody()
{
    size = 1;
    m_mesh = nullptr;
    sizeControl = nullptr;
    controlLayout = nullptr;
    drawingWidget = nullptr;
}


SBody::~SBody()
{
    //delete m_mesh;
}

void SBody::initializeControls()
{
    sizeControl = new Control(controlLayout, drawingWidget);
    sizeControl->setValue(1);
}

//void SBody::setMesh(Mesh& mesh)
//{
//    m_mesh = &mesh;
//    m_modelToWorld = m_mesh->m_program->uniformLocation("modelToWorld");
//}

void SBody::setTexture(Textures* textures, int texture)
{
    m_texture = texture;
    m_pTextures = textures;
}


void SBody::setControlPanel(QVBoxLayout* layout, MyOpenGLWidget *drawingWidget)
{
   controlLayout = layout;
   this->drawingWidget = drawingWidget;
}

void SBody::updateControls()
{

    if (sizeControl != nullptr)// && (sizeControl->m_value != sizeControl->old_value))
    {

        //toPosRotMatrix.setToIdentity();
        //scaleToSize((float)sizeControl->m_value);
        //sizeControl->old_value = sizeControl->m_value;
    }
}

void SBody::render()
{
    //updateControls();

    m_pTextures->bindTexture(2);
    m_pTextures->bindTexture(3);
    m_pTextures->bindTexture(4);
    m_pTextures->bindTexture(5);
//    m_mesh->m_program->setUniformValue(m_modelToWorld, toPosRotMatrix);
//    m_mesh->draw();

//    for (std::vector<SBody>::iterator it = parts.begin(); it != parts.end(); ++it) {
//        it->render();
//    }

}

void SBody::setPosition(const QVector3D &pos)
{
    toPosRotMatrix.translate(pos-position);
    position = pos;
}

// Transform By (Add/Scale)
void SBody::translate(const QVector3D &dt)
{
  position += dt;
  toPosRotMatrix.translate(dt);
}

void SBody::rotate(const QQuaternion &dr)
{
  m_rotation = dr;// * m_rotation;
  //toPosRotMatrix.setToIdentity();
  //std::cout << "draw" << std::endl;
  toPosRotMatrix.rotate(m_rotation);
}

void SBody::scale(float f)
{
    toPosRotMatrix.scale(f);
}

void SBody::scaleToSize(float s)
{
    if ( ( (s/size) > 0.01) && ((s/size) < 20) )
    {
        toPosRotMatrix.scale(s/size);
        size = s;
    }
}

// Transform To (Setters)
void SBody::setRotation(const QQuaternion &r)
{
  m_rotation = r;
  toPosRotMatrix.rotate(m_rotation);
}

