#ifndef MAINVIEWWIDGET_H
#define MAINVIEWWIDGET_H

#include <QOpenGLWidget>
#include <QScrollArea>
#include <QOpenGLFunctions>
#include <QOpenGLTexture>
#include <QMatrix4x4>
#include "camera3d.h"
#include "transform3d.h"
#include "terrain.h"
#include "road.h"
#include "car.h"
#include "textures.h"

class QOpenGLShaderProgram;

class MainViewWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit MainViewWidget(QWidget *parent = 0);
    ~MainViewWidget();
    // OpenGL Events
    public:
      void initializeObjects(QVBoxLayout *layout, QOpenGLShaderProgram* shader, Textures *textures, Terrain* terrain, Road* road, Car *car);
      void initializeGL();
      void resizeGL(int width, int height);
      void paintGL();
      void mainUpdate();
      Camera3D m_camera;

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

//    public Q_SLOTS:
//        // slots for xyz-rotation slider
//        void setXRotation(int angle);
//        void setYRotation(int angle);
//        void setZRotation(int angle);

    Q_SIGNALS:
        // signaling rotation from mouse movement
        void xRotationChanged(int angle);
        void yRotationChanged(int angle);
        void zRotationChanged(int angle);

    private:
      // Shader Information
      QOpenGLShaderProgram* m_TexturedDiffuseShaderProgram;
      // Textures used in this widget
      Textures* m_pTextures;
      // Mesh Information
      Terrain* m_pTerrain;
      Road* m_pRoad;
      Car* m_pCar;

      // OpenGL State Information
      int u_worldToCamera;
      int u_cameraToView;


      QMatrix4x4 m_projection;
      Transform3D m_transform;

      // Private Helpers
      void printVersionInformation();

      QPoint lastPos;
      vector<QVector3D> results;
      int it;

};

#endif // MAINVIEWWIDGET_H
