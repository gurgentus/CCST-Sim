#include <QDebug>
#include <QString>
#include <QtOpenGL>
#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include "vertex.h"
#include "input.h"
#include "mainviewwidget.h"
#include "nums/simulator.h"
#include <window.h>

#include <iostream>

MainViewWidget::MainViewWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    setFocusPolicy( Qt::StrongFocus );
}

MainViewWidget::~MainViewWidget()
{
}

void MainViewWidget::InitializeObjects(QVBoxLayout *layout, QVBoxLayout *output_layout, QOpenGLShaderProgram* shader,
                                       Textures* textures, Terrain* terrain, Road *road, AdaptiveCar* car, Car* leadCar)
{
    p_program_ = shader;
    p_textures_ = textures;
    p_terrain_ = terrain;
    p_road_ = road;
    p_lead_car_ = leadCar;
    p_car_ = car;

    p_car_->SetControlOutputPanel(layout, output_layout, this);
    p_car_->InitializeControls();
    p_car_->InitializeOutputs();

    p_lead_car_->SetControlOutputPanel(layout, output_layout, this);
    p_lead_car_->InitializeControls();



}


QSize MainViewWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize MainViewWidget::sizeHint() const
{
    return QSize(800, 800);
}

void MainViewWidget::initializeGL()
{

    // Initialize OpenGL Backend
    QOpenGLFunctions::initializeOpenGLFunctions();
    connect(this, SIGNAL(frameSwapped()), this, SLOT(update()));
    connect(context(), SIGNAL(aboutToBeDestroyed()), this, SLOT(teardownGL()), Qt::DirectConnection);
    printVersionInformation();


    p_program_->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/texturedDiffuse.vert");
    p_program_->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/texturedDiffuse.frag");
    p_program_->link();
    p_program_->bind();

    // Cache Uniform Locations
    world_to_camera_ = p_program_->uniformLocation("worldToCamera");
    camera_to_view_ = p_program_->uniformLocation("cameraToView");
    p_program_->setUniformValue(world_to_camera_, QMatrix4x4());
    p_program_->setUniformValue(camera_to_view_, QMatrix4x4());
//    if ( !m_pTextures->loadTexture( ":/Textures/earth.dds", EARTH_TEXTURE ) )
//    {
//        std::cerr << "Failed to load terrain texture for earth!" << std::endl;
//    }
//    if ( !m_pTextures->loadTexture( ":/Textures/moon.dds", MOON_TEXTURE ) )
//    {
//        std::cerr << "Failed to load terrain texture for moon!" << std::endl;
//    }

    if ( !p_textures_->loadTexture( ":/Data/Textures/grass.jpg", GRASS_TEXTURE ) )
    {
        std::cerr << "Failed to load terrain texture for grass!" << std::endl;
    }
    if ( !p_textures_->loadTexture( ":/Data/Textures/rock.png", ROCK_TEXTURE ) )
    {
        std::cerr << "Failed to load terrain texture for rock!" << std::endl;
    }
    if ( !p_textures_->loadTexture( ":/Data/Textures/snow.jpg", SNOW_TEXTURE ) )
    {
        std::cerr << "Failed to load terrain texture for snow!" << std::endl;
    }
    if ( !p_textures_->loadTexture( ":/Data/Textures/road.jpg", ROAD_TEXTURE ) )
    {
        std::cerr << "Failed to load terrain texture for road!" << std::endl;
    }
    if ( !p_textures_->loadTexture( ":/Data/Textures/car1.jpeg", CAR_TEXTURE ) )
    {
        std::cerr << "Failed to load terrain texture for road!" << std::endl;
    }
    if ( !p_textures_->loadTexture( ":/Data/Textures/car2.jpeg", CAR2_TEXTURE ) )
    {
        std::cerr << "Failed to load terrain texture for road!" << std::endl;
    }

    if (p_road_ != NULL)
    {
        if ( !p_road_->SetupDefaultMesh() )
        {
            std::cerr << "Failed to load the road!" << std::endl;
        }
    }
    else
    {
        std::cerr << "Road object doesn't exist!" << std::endl;
    }
    if (p_car_ != NULL)
    {
        if ( !p_car_->LoadMesh(":/Data/Objects/coop.obj", QVector4D( 0.0f, 1.0f, 0.0f, 1.0f )) )
        {
            std::cerr << "Failed to load the car!" << std::endl;
        }
    }
    else
    {
        std::cerr << "Car object doesn't exist!" << std::endl;
    }
    if (p_lead_car_ != NULL)
    {
        if ( !p_lead_car_->LoadMesh(":/Data/Objects/coop.obj", QVector4D( 0.0f, 1.0f, 1.0f, 1.0f )) )
        {
            std::cerr << "Failed to load the lead car!" << std::endl;
        }
    }
    else
    {
        std::cerr << "Car object doesn't exist!" << std::endl;
    }
    if (p_terrain_ != NULL)
    {
        if ( !p_terrain_->SetupDefaultMesh() )
        {
            std::cerr << "Failed to load heightmap for terrain!" << std::endl;
        }
    }
    else
    {
        std::cerr << "Terrain object doesn't exist!" << std::endl;
    }


  // Set global information
  //glEnable(GL_DEPTH_TEST | GL_CULL_FACE);
  glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

  p_terrain_->SetModels();
  p_road_->SetModels();
  p_car_->SetModels();
  p_lead_car_->SetModels();
  p_program_->release();
}

void MainViewWidget::resizeGL(int width, int height)
{
    // Currently we are not handling width/height changes.
    (void)width;
    (void)height;
    projection_.setToIdentity();
    projection_.perspective(45.0f, width / float(height), 1.0f, 1000.0f);
}

void MainViewWidget::paintGL()
{
  // std::cout << "draw" << std::endl;
  // Clear
  glClear(GL_COLOR_BUFFER_BIT);
  glClear(GL_DEPTH_BUFFER_BIT);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  p_program_->bind();
  p_program_->setUniformValue(world_to_camera_, camera_.toMatrix());
  p_program_->setUniformValue(camera_to_view_, projection_);
  p_program_->setUniformValue("stage1", GRASS_TEXTURE);
  p_program_->setUniformValue("stage2", ROCK_TEXTURE);
  p_program_->setUniformValue("stage3", ROAD_TEXTURE);
  p_program_->setUniformValue("car", CAR_TEXTURE);
  p_program_->setUniformValue("car2", CAR2_TEXTURE);

  p_program_->setUniformValue(p_program_->uniformLocation("modelToWorld"), QMatrix4x4());

  p_textures_->bindAllTextures();

  p_road_->SetModels();
  p_road_->Draw();


  p_car_->SetModels();
  p_car_->Draw();


  p_lead_car_->SetModels();
  p_lead_car_->Draw();


  p_terrain_->SetModels();
  p_terrain_->Draw();


  p_program_->release();


}

void MainViewWidget::update()
{
    // Update input
    Input::update();

    // Camera Transformation
    if (Input::keyPressed(Qt::Key_A))
    {
      //translation -= m_camera.right();
      //std::cout << "A key pressed" << std::endl;
      p_car_->SteerLeft();
    }
    if (Input::keyPressed(Qt::Key_D))
    {
      //translation += m_camera.right();
      //std::cout << "A key pressed" << std::endl;
      p_car_->SteerRight();
    }
    if (Input::buttonPressed(Qt::RightButton))
    {
      static const float transSpeed = 0.5f;
      static const float rotSpeed   = 0.5f;

      // Handle rotations
      camera_.rotate(-rotSpeed * Input::mouseDelta().x(), Camera3D::LocalUp);
      camera_.rotate(-rotSpeed * Input::mouseDelta().y(), camera_.right());

      // Handle translations
      QVector3D translation;
      if (Input::keyPressed(Qt::Key_W))
      {
        translation += camera_.forward();
      }
      if (Input::keyPressed(Qt::Key_S))
      {
        translation -= camera_.forward();
      }
      if (Input::keyPressed(Qt::Key_A))
      {
        translation -= camera_.right();
      }
      if (Input::keyPressed(Qt::Key_D))
      {
        translation += camera_.right();
      }
      if (Input::keyPressed(Qt::Key_Q))
      {
        translation -= camera_.up();
      }
      if (Input::keyPressed(Qt::Key_E))
      {
        translation += camera_.up();
      }
      camera_.translate(transSpeed * translation);

    }
  // Schedule a redraw
   //std::cout << "TTEST" << std::endl;
   this->makeCurrent();
   this->paintGL();
   QOpenGLWidget::update();
}

void MainViewWidget::teardownGL()
{
  // Actually destroy our OpenGL information
  delete p_program_;
}

void MainViewWidget::keyPressEvent(QKeyEvent *event)
{
  if (event->isAutoRepeat())
  {
    event->ignore();
  }
  else
  {
    Input::registerKeyPress(event->key());
  }
}

void MainViewWidget::keyReleaseEvent(QKeyEvent *event)
{
  if (event->isAutoRepeat())
  {
    event->ignore();
  }
  else
  {
    Input::registerKeyRelease(event->key());
  }
}

void MainViewWidget::mousePressEvent(QMouseEvent *event)
{
  Input::registerMousePress(event->button());
  lastPos = event->pos();
}

void MainViewWidget::mouseReleaseEvent(QMouseEvent *event)
{
  Input::registerMouseRelease(event->button());
}

void MainViewWidget::mouseMoveEvent(QMouseEvent *event)
{
   update();
//    int dx = event->x() - lastPos.x();
//    int dy = event->y() - lastPos.y();

//    if (event->buttons() & Qt::LeftButton) {
//        setXRotation(xRot + 0.5 * dy);
//        setYRotation(yRot + 0.5 * dx);
//    } else if (event->buttons() & Qt::RightButton) {
//        setXRotation(xRot + 0.5 * dy);
//        setZRotation(zRot + 0.5 * dx);
//    }

//    lastPos = event->pos();

    // Update instance information
    //earth_transform.rotate(1.0f, QVector3D(0.4f, 0.3f, 0.3f));
}


/*******************************************************************************
 * Private Helpers
 ******************************************************************************/

void MainViewWidget::printVersionInformation()
{
  QString glType;
  QString glVersion;
  QString glProfile;

  // Get Version Information
  glType = (context()->isOpenGLES()) ? "OpenGL ES" : "OpenGL";
  glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));

  // Get Profile Information
#define CASE(c) case QSurfaceFormat::c: glProfile = #c; break
  switch (format().profile())
  {
    CASE(NoProfile);
    CASE(CoreProfile);
    CASE(CompatibilityProfile);
  }
#undef CASE

  // qPrintable() will print our QString w/o quotes around it.
  qDebug() << qPrintable(glType) << qPrintable(glVersion) << "(" << qPrintable(glProfile) << ")";
}
