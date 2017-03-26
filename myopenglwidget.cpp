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
#include "myopenglwidget.h"
#include "textureandlightingpch.h"
#include "nums/simulator.h"
#include <window.h>

#include <iostream>

// Create a colored triangle
//static const Vertex sg_vertexes[] = {
//  Vertex( QVector3D( 0.00f,  0.75f, 1.0f), QVector3D(1.0f, 0.0f, 0.0f) ),
//  Vertex( QVector3D(-0.75f, -0.75f, 1.0f), QVector3D(0.0f, 1.0f, 0.0f) ),
//  Vertex( QVector3D( 0.75f, -0.75f, 1.0f), QVector3D(0.0f, 0.0f, 1.0f) )
//};



/*******************************************************************************
 * OpenGL Events
 ******************************************************************************/


MyOpenGLWidget::MyOpenGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    xRot = 0;
    yRot = 0;
    zRot = 0;
    g_fSunRotation = 0.0f;
    m_transform.translate(0.0f, 0.0f, -5.0f);
    m_transform.rotate(g_fSunRotation, 0, -1, 0);
    m_transform.translate(2.5f, 0, 0);

    //glm::mat4 modelMatrix = glm::rotate( glm::radians(g_fSunRotation), glm::vec3(0,-1,0) ) * glm::translate(glm::vec3(90,0,0));

    setFocusPolicy( Qt::StrongFocus );
}

MyOpenGLWidget::~MyOpenGLWidget()
{
}

void MyOpenGLWidget::initializeObjects(QVBoxLayout *layout)
{
    //earth.setPosition(-2.5f, 0, -5);
    //moon.initializeControls(layout);
    //moon.setPosition(0.0f, 0.0f, -5.0f);
    moon.scale(0.3f);
    //earth.initializeControls(layout);
    //fuselage.initializeControls(layout);
    //endCap1.initializeControls(layout);
    //endCap2.initializeControls(layout);

    wing1.setControlPanel(layout, this);
    wing1.initializeControls();

    wing2.setControlPanel(layout, this);
    wing2.initializeControls();

    tail1.setControlPanel(layout, this);
    tail1.initializeControls();

    tail2.setControlPanel(layout, this);
    tail2.initializeControls();

    tail3.setControlPanel(layout, this);
    tail3.initializeControls();

}

QSize MyOpenGLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize MyOpenGLWidget::sizeHint() const
{
    return QSize(800, 800);
}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360)
        angle -= 360 * 16;
}

void MyOpenGLWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
        Q_EMIT xRotationChanged(angle);
        earth.rotate(xRot, 1.0f, 0.0f, 0.0f);
        update();
    }
}

void MyOpenGLWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        Q_EMIT yRotationChanged(angle);
        earth.rotate(yRot, 0.0f, 1.0f, 0.0f);
        update();
    }
}

void MyOpenGLWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        Q_EMIT zRotationChanged(angle);
        earth.rotate(zRot, 0.0f, 0.0f, 1.0f);
        update();
    }
}

// Create a shader program from a set of compiled shader objects.
//GLuint CreateShaderProgram( std::vector<GLuint> shaders )
//{
//    // Create a shader program.
//    GLuint program = glCreateProgram();

//    // Attach the appropriate shader objects.
//    for( GLuint shader: shaders )
//    {
//        glAttachShader( program, shader );
//    }
//    // Link the program
//    glLinkProgram(program);

//    // Check the link status.
//    GLint linkStatus;
//    glGetProgramiv(program, GL_LINK_STATUS, &linkStatus );
//    if ( linkStatus != GL_TRUE )
//    {
//        GLint logLength;
//        glGetProgramiv( program, GL_INFO_LOG_LENGTH, &logLength );
//        GLchar* infoLog = new GLchar[logLength];

//        glGetProgramInfoLog( program, logLength, NULL, infoLog );

//#ifdef _WIN32
//        OutputDebugString(infoLog);
//#else
//        std::cerr << infoLog << std::endl;
//#endif

//        delete infoLog;
//        return 0;
//    }
//    return program;
//}

// Loads a shader and returns the compiled shader object.
// If the shader source file could not be opened or compiling the
// shader fails, then this function returns 0.
//GLuint LoadShader( GLenum shaderType, const std::string& shaderFile )
//{
//    std::ifstream ifs;

//    // Load the shader source file.
//    ifs.open(shaderFile);

//    if ( !ifs )
//    {
//        std::cerr << "Can not open shader file: \"" << shaderFile << "\"" << std::endl;
//        return 0;
//    }

//    std::string source( std::istreambuf_iterator<char>(ifs), (std::istreambuf_iterator<char>()) );
//    ifs.close();

//    // Create a shader object.
//    GLuint shader = glCreateShader( shaderType );

//    // Load the shader source for each shader object.
//    const GLchar* sources[] = { source.c_str() };
//    glShaderSource( shader, 1, sources, NULL );
//    glCompileShader( shader );

//    // Check for errors
//     GLint compileStatus;
//     glGetShaderiv( shader, GL_COMPILE_STATUS, &compileStatus );
//     if ( compileStatus != GL_TRUE )
//     {
//         GLint logLength;
//         glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &logLength );
//         GLchar* infoLog = new GLchar[logLength];
//         glGetShaderInfoLog( shader, logLength, NULL, infoLog );

// #ifdef _WIN32
//         OutputDebugString(infoLog);
// #else
//         std::cerr << infoLog << std::endl;
// #endif
//         delete infoLog;
//         return 0;
//     }

//     return shader;
// }



void MyOpenGLWidget::initializeGL()
{
    //    GLuint textureID = SOIL_load_OGL_texture( file.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS );
    //    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    //    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    //    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    //    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    //    glBindTexture( GL_TEXTURE_2D, 0 );

    //    g_MoonTexture = LoadTexture( "../data/Textures/moon.dds" );


//    assert( QFile::exists(":/shaders/simple.vert") );
//    GLuint vertexShader = LoadShader( GL_VERTEX_SHADER, "/Users/gurgentus/MyOpenGL/shaders/simple.vert" );
//    GLuint fragmentShader = LoadShader( GL_FRAGMENT_SHADER, "/Users/gurgentus/MyOpenGL/shaders/simple.frag" );

//    std::vector<GLuint> shaders;
//    shaders.push_back(vertexShader);
//    shaders.push_back(fragmentShader);

//    GLuint g_SimpleShaderProgram = 0;

//    g_SimpleShaderProgram = CreateShaderProgram( shaders );
//    assert( g_SimpleShaderProgram );

//    // Retrieve the location of the color uniform variable in the simple shader program.
//    GLint g_uniformColor = -1;
//    g_uniformColor = glGetUniformLocation( g_SimpleShaderProgram, "color" );

  Simulator simulator;
  simulator.simulate(results);
  //std::cout << results[0].x();
  it = 0;
  moon.setPosition(results[it]);

  fuselage.setPosition(2,2,2);

  endCap1.setPosition(2,2,2);
  endCap2.setPosition(34,2,2);
  endCap1.rotate(180, 0,1,0);
  wing1.setDimensions(0.3, 2, 0.05, 0.1, 0.3);
  wing1.setPosition(16,3,2);
  wing2.setDimensions(0.3, 2, 0.05, 0.1, 0.3);
  wing2.setPosition(16,1,2);


  tail1.setDimensions(0.1, 2, 0.05, 0.1, 1);
  tail1.setPosition(2,2,3.5);
  tail1.scale(0.5);
  tail2.setDimensions(0.1, 2, 0.05, 0.1, 1);
  tail2.setPosition(2,2,3.5);
  tail2.scale(0.5);

  tail3.setDimensions(0.1, 2, 0.05, 0.1, 1);
  tail3.setPosition(2,2,3);
  tail3.rotate(90, 1,0,0);
  tail3.scale(0.6);

  // Initialize OpenGL Backend
  QOpenGLFunctions::initializeOpenGLFunctions();
  connect(this, SIGNAL(frameSwapped()), this, SLOT(update()));
  connect(context(), SIGNAL(aboutToBeDestroyed()), this, SLOT(teardownGL()), Qt::DirectConnection);
  printVersionInformation();

  // Set global information
  //glEnable(GL_DEPTH_TEST | GL_CULL_FACE);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  //glClearDepth(1.0f);
  // Application-specific initialization
  {
    // Create Shader (Do not release until VAO is created)
    //m_TexturedDiffuseShaderProgram = new QOpenGLShaderProgram();
    m_TexturedDiffuseShaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/texturedDiffuse.vert");
    m_TexturedDiffuseShaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/texturedDiffuse.frag");
    m_TexturedDiffuseShaderProgram->link();
    m_TexturedDiffuseShaderProgram->bind();
    // Cache Uniform Locations
    u_worldToCamera = m_TexturedDiffuseShaderProgram->uniformLocation("worldToCamera");
    u_cameraToView = m_TexturedDiffuseShaderProgram->uniformLocation("cameraToView");

    airplane.setupDefaultMesh();
    //fuselageMesh.setupFuselageMesh(m_TexturedDiffuseShaderProgram);
    //sphereMesh.setupSphereMesh(m_TexturedDiffuseShaderProgram);
//    wing1.setupMesh(m_TexturedDiffuseShaderProgram);
//    wing2.setupMesh(m_TexturedDiffuseShaderProgram);
//    tail1.setupMesh(m_TexturedDiffuseShaderProgram);
//    tail2.setupMesh(m_TexturedDiffuseShaderProgram);
//    tail3.setupMesh(m_TexturedDiffuseShaderProgram);
    //aileronMesh.setupAileronMesh(m_TexturedDiffuseShaderProgram);

//    endCap1.setMesh(capMesh);
//    endCap1.setTexture(MOON_TEXTURE);
//    endCap2.setMesh(capMesh);
//    endCap2.setTexture(MOON_TEXTURE);
//    fuselage.setMesh(fuselageMesh);
//    fuselage.setTexture(EARTH_TEXTURE);
//    earth.setMesh(sphereMesh);
//    earth.setTexture(EARTH_TEXTURE);
//    moon.setMesh(sphereMesh);
//    moon.setTexture(MOON_TEXTURE);

//    wing1.setTexture(EARTH_TEXTURE);
//    wing1.aileron.setTexture(MOON_TEXTURE);
//    wing2.setTexture(EARTH_TEXTURE);
//    wing2.aileron.setTexture(MOON_TEXTURE);

//    wing1.aileronAngleControl->setTfControl(true);
//    wing2.aileronAngleControl->setTfControl(false);

//    tail1.setTexture(EARTH_TEXTURE);
//    tail1.aileron.setTexture(MOON_TEXTURE);
//    tail2.setTexture(EARTH_TEXTURE);
//    tail2.aileron.setTexture(MOON_TEXTURE);
//    tail3.setTexture(EARTH_TEXTURE);
//    tail3.aileron.setTexture(MOON_TEXTURE);


//    m_TexturedDiffuseShaderProgram->release();

//    vertexShader = LoadShader( GL_VERTEX_SHADER, "../data/shaders/texturedDiffuse.vert" );
//    fragmentShader = LoadShader( GL_FRAGMENT_SHADER, "../data/shaders/texturedDiffuse.frag" );
//    shaders.clear();
//    shaders.push_back(vertexShader);
//    shaders.push_back(fragmentShader);
//    g_TexturedDiffuseShaderProgram = CreateShaderProgram( shaders );
//    assert( g_TexturedDiffuseShaderProgram );

//       g_uniformMVP = glGetUniformLocation( g_TexturedDiffuseShaderProgram, "ModelViewProjectionMatrix" );
//       g_uniformModelMatrix = glGetUniformLocation( g_TexturedDiffuseShaderProgram, "ModelMatrix" );
//       g_uniformEyePosW = glGetUniformLocation( g_TexturedDiffuseShaderProgram, "EyePosW" );

  }
}

void MyOpenGLWidget::resizeGL(int width, int height)
{
    // Currently we are not handling width/height changes.
    (void)width;
    (void)height;
    m_projection.setToIdentity();
    m_projection.perspective(45.0f, width / float(height), 1.0f, 1000.0f);
}

void MyOpenGLWidget::paintGL()
{
  //  std::cout << "draw" << std::endl;
  // Clear
  glClear(GL_COLOR_BUFFER_BIT);
  glClear(GL_DEPTH_BUFFER_BIT);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  //glDisable(GL_LIGHTING);

  m_TexturedDiffuseShaderProgram->bind();
  m_TexturedDiffuseShaderProgram->setUniformValue(u_worldToCamera, m_camera.toMatrix());
  m_TexturedDiffuseShaderProgram->setUniformValue(u_cameraToView, m_projection);

  earth.render();
  //moon.render();
  fuselage.render();
  endCap1.render();
  endCap2.render();

  wing1.render();
  wing1.aileron.render();
  wing2.render();
  wing2.aileron.render();

  tail1.render();
  tail1.aileron.render();
  tail2.render();
  tail2.aileron.render();
  tail3.render();
  tail3.aileron.render();

  m_TexturedDiffuseShaderProgram->release();
}

void MyOpenGLWidget::update()
{
    // Update input
    Input::update();

    if (Input::keyPressed(Qt::Key_T))
    {
      moon.setPosition(results[it]);
      if (it < 19900) it = it+50;
    }

    // Camera Transformation
    if (Input::buttonPressed(Qt::RightButton))
    {

      static const float transSpeed = 0.5f;
      static const float rotSpeed   = 0.5f;

      // Handle rotations
      m_camera.rotate(-rotSpeed * Input::mouseDelta().x(), Camera3D::LocalUp);
      m_camera.rotate(-rotSpeed * Input::mouseDelta().y(), m_camera.right());

      // Handle translations
      QVector3D translation;
      if (Input::keyPressed(Qt::Key_W))
      {
        translation += m_camera.forward();
      }
      if (Input::keyPressed(Qt::Key_S))
      {
        translation -= m_camera.forward();
      }
      if (Input::keyPressed(Qt::Key_A))
      {
        translation -= m_camera.right();
      }
      if (Input::keyPressed(Qt::Key_D))
      {
        translation += m_camera.right();
      }
      if (Input::keyPressed(Qt::Key_Q))
      {
        translation -= m_camera.up();
      }
      if (Input::keyPressed(Qt::Key_E))
      {
        translation += m_camera.up();
      }
      m_camera.translate(transSpeed * translation);

    }
  // Schedule a redraw
   //std::cout << "TTEST" << std::endl;
   this->makeCurrent();
   this->paintGL();
  QOpenGLWidget::update();
}
void MyOpenGLWidget::mainUpdate()
{
}

void MyOpenGLWidget::teardownGL()
{
  // Actually destroy our OpenGL information
  //m_object.destroy();
  //m_vertex.destroy();
  airplane.cleanup();
//  fuselageMesh.cleanup();
//  capMesh.cleanup();

  delete m_program;
  delete m_TexturedDiffuseShaderProgram;
}

void MyOpenGLWidget::keyPressEvent(QKeyEvent *event)
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

void MyOpenGLWidget::keyReleaseEvent(QKeyEvent *event)
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

void MyOpenGLWidget::mousePressEvent(QMouseEvent *event)
{
  Input::registerMousePress(event->button());
  lastPos = event->pos();
}

void MyOpenGLWidget::mouseReleaseEvent(QMouseEvent *event)
{
  Input::registerMouseRelease(event->button());
}

//void MyOpenGLWidget::mousePressEvent(QMouseEvent *event)
//{
//    lastPos = event->pos();
//}

void MyOpenGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(xRot + 0.5 * dy);
        setYRotation(yRot + 0.5 * dx);
    } else if (event->buttons() & Qt::RightButton) {
        setXRotation(xRot + 0.5 * dy);
        setZRotation(zRot + 0.5 * dx);
    }

    lastPos = event->pos();

    // Update instance information
    //earth_transform.rotate(1.0f, QVector3D(0.4f, 0.3f, 0.3f));
}


/*******************************************************************************
 * Private Helpers
 ******************************************************************************/

void MyOpenGLWidget::printVersionInformation()
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
