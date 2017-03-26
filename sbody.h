#ifndef SBODY_H
#define SBODY_H

#include <QVector3D>
#include <QMatrix4x4>
#include "mesh.h"
#include "textures.h"
#include "control.h"
//#include "myopenglwidget.h"

class MyOpenGLWidget;

class SBody
{
    friend class Wing;
public:
    SBody();
    ~SBody();

    void setControlPanel(QVBoxLayout* layout, MyOpenGLWidget* drawingWidget);
    virtual void initializeControls();
    virtual void updateControls();

    // void setMesh(Mesh &mesh);

    void translate(const QVector3D &dt);
    void translate(float dx, float dy, float dz);
    void rotate(const QQuaternion &dr);
    void rotate(float angle, const QVector3D &axis);
    void rotate(float angle, float ax, float ay, float az);
    void scale(float f);
    void scaleToSize(float s);

    // Setters
    void setTexture(Textures *textures, int texture);

    // Transform To (Setters)
    void setPosition(const QVector3D &t);
    void setPosition(float x, float y, float z);
    void setRotation(const QQuaternion &r);
    void setRotation(float angle, const QVector3D &axis);
    void setRotation(float angle, float ax, float ay, float az);

    // Accessors
    inline const QVector3D& getPosition() const { return position; }
    inline const QQuaternion& getRotation() const { return m_rotation; }


    void render();



protected:
    Mesh* m_mesh;
    int m_texture;
    Textures* m_pTextures;
    QVector3D position;
    QQuaternion m_rotation;
    QMatrix4x4 toPosRotMatrix;
    float size;
    int m_modelToWorld;
    Control* sizeControl;
    QVBoxLayout* controlLayout;
    MyOpenGLWidget* drawingWidget;

};

// Transform By (Add/Scale)
inline void SBody::translate(float dx, float dy,float dz) { translate(QVector3D(dx, dy, dz)); }
inline void SBody::rotate(float angle, const QVector3D &axis) { rotate(QQuaternion::fromAxisAndAngle(axis, angle)); }
inline void SBody::rotate(float angle, float ax, float ay,float az) { rotate(QQuaternion::fromAxisAndAngle(ax, ay, az, angle)); }

// Transform To (Setters)
inline void SBody::setPosition(float x, float y, float z) { setPosition(QVector3D(x, y, z)); }
inline void SBody::setRotation(float angle, const QVector3D &axis) { setRotation(QQuaternion::fromAxisAndAngle(axis, angle)); }
inline void SBody::setRotation(float angle, float ax, float ay, float az) { setRotation(QQuaternion::fromAxisAndAngle(ax, ay, az, angle)); }



#endif // SBODY_H
