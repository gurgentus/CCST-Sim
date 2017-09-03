#ifndef MAINVIEWWIDGET_H
#define MAINVIEWWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>

#include "Common/Camera3D.hpp"
#include "Common/Textures.hpp"

class QOpenGLShaderProgram;

/* Main 3D view widget.  Inherits from Qt OpenGL classes and implements
 * the rquired graphics methods.
 */
class MainViewWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit MainViewWidget(QWidget *parent = 0);

    public:
      // Main objects used in interfacing with the graphics.
      // The shader program is used to modify the shader program
      // that is run on the graphics card.  The textures object
      // is used to load and change textures.
      // TODO: make private?
      QOpenGLShaderProgram* p_program_;
      Textures* p_textures_;
      Camera3D camera_;

      // Sets the program and texture pointers
      void InitializeObjects(QOpenGLShaderProgram* shader, Textures* textures);

      // inherited QOpenGLWidget methods
      void initializeGL();
      void resizeGL(int width, int height);
      void paintGL();

    protected:
      // OpenGL State Information
      int world_to_camera_;
      int camera_to_view_;
      // Camera projection matrix
      QMatrix4x4 projection_;

      // Mouse last position
      QPoint lastPos;

//      std::vector<QVector3D> results;
//      int it;

      // Implement inherited windowing methods
      QSize minimumSizeHint() const;
      QSize sizeHint() const;

      // Implement handle events inherited from QWidget class
      // for custom functionality
      void keyPressEvent(QKeyEvent *event);
      void keyReleaseEvent(QKeyEvent *event);
      void mousePressEvent(QMouseEvent *event);
      void mouseReleaseEvent(QMouseEvent *event);
      void mouseMoveEvent(QMouseEvent *event);

      // print openGL info
      void printVersionInformation();

    protected Q_SLOTS:
      virtual void update();
      void teardownGL();

};

#endif // MAINVIEWWIDGET_H
