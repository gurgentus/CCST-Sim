#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QScrollArea>
#include <QOpenGLFunctions>
#include <QOpenGLTexture>
#include <QMatrix4x4>
#include "camera3d.h"
#include "transform3d.h"
#include "objects/mesh.h"
#include "objects/sbody.h"
#include "objects/wing.h"
#include "objects/part.h"
#include "objects/airplane.h"

class QOpenGLShaderProgram;
//class SBody;
//class Wing;
//class Mesh;

class MyOpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    friend class Control;
    Q_OBJECT
public:
    explicit MyOpenGLWidget(QWidget *parent = 0);
    ~MyOpenGLWidget();
    // OpenGL Events
    public:
      void initializeObjects(QVBoxLayout *layout);
      void initializeGL();
      void resizeGL(int width, int height);
      void paintGL();
      void mainUpdate();

    protected:
      QSize minimumSizeHint() const;
      QSize sizeHint() const;

      void keyPressEvent(QKeyEvent *event);
      void keyReleaseEvent(QKeyEvent *event);
      void mousePressEvent(QMouseEvent *event);
      void mouseReleaseEvent(QMouseEvent *event);
      void mouseMoveEvent(QMouseEvent *event);

    protected Q_SLOTS:
      void update();
      void teardownGL();

    public Q_SLOTS:
        // slots for xyz-rotation slider
        void setXRotation(int angle);
        void setYRotation(int angle);
        void setZRotation(int angle);

    Q_SIGNALS:
        // signaling rotation from mouse movement
        void xRotationChanged(int angle);
        void yRotationChanged(int angle);
        void zRotationChanged(int angle);

    private:
      // OpenGL State Information
      QOpenGLShaderProgram* m_program;
      QOpenGLShaderProgram* m_TexturedDiffuseShaderProgram;
//      Mesh sphereMesh;
//      Mesh fuselageMesh;
//      Mesh capMesh;
      Airplane airplane;
      Part endCap1;
      Part endCap2;
      Part fuselage;
      Wing wing1;
      Wing wing2;
      Wing tail1;
      Wing tail2;
      Wing tail3;

      Part earth;
      Part moon;
      //SControl moonRadius;

      // Shader Information
      int u_worldToCamera;
      int u_cameraToView;

      QMatrix4x4 m_projection;
      Camera3D m_camera;
      Transform3D m_transform;

      float g_fSunRotation;
      // Private Helpers
      void printVersionInformation();

      int xRot;
      int yRot;
      int zRot;

      QPoint lastPos;
      vector<QVector3D> results;
      int it;

};

#endif // MYOPENGLWIDGET_H
