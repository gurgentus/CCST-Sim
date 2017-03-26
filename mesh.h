#ifndef MESH_H
#define MESH_H

#include "vertex.h"
#include <QtOpenGL>
#include <QOpenGLVertexArrayObject>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
//#include <glm/gtc/swizzle.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/std_based_type.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/compatibility.hpp>
#include <glm/gtx/matrix_operation.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>


#define POSITION_ATTRIBUTE 0
#define COLOR_ATTRIBUTE 1
#define NORMAL_ATTRIBUTE 2
#define DIFFUSE_ATTRIBUTE 3
#define SPECULAR_ATTRIBUTE 4
#define TEXCOORD0_ATTRIBUTE 8
#define TEXCOORD1_ATTRIBUTE 9
#define TEXCOORD2_ATTRIBUTE 10

#define BUFFER_OFFSET(offset) ((void*)(offset))
#define MEMBER_OFFSET(s,m) ((char*)NULL + (offsetof(s,m)))

using namespace std;

class Mesh {
    public:
        Mesh();
        ~Mesh();
        /*  Mesh Data  */
        //vector<Vertex> m_VertexBuffer;
        //vector<QOpenGLTexture*> m_textures;
        QOpenGLShaderProgram* m_program;
        QOpenGLVertexArrayObject VAO;

        typedef std::vector<Vertex>  PositionBuffer;
//        typedef std::vector<glm::vec4>  ColorBuffer;
//        typedef std::vector<glm::vec3>  NormalBuffer;
//        typedef std::vector<glm::vec2>  TexCoordBuffer;
        typedef std::vector<GLuint>     IndexBuffer;

        /*  Functions  */
        void setShaderProgram(QOpenGLShaderProgram *texturedDiffuseShaderProgram);
        bool setupMesh();
        bool setupMesh(PositionBuffer positionBuffer, IndexBuffer indexBuffer);
        virtual bool setupDefaultMesh() = 0;

        /*  Render data  */
        void draw();
        void cleanup();
    protected:
        constexpr static const float pi = 3.1415926535897932384626433832795f;
        constexpr static const float _2pi = 2.0f * pi;

        PositionBuffer  m_PositionBuffer;
//        ColorBuffer     m_ColorBuffer;
//        NormalBuffer    m_NormalBuffer;
//        TexCoordBuffer  m_Tex0Buffer;
        IndexBuffer     m_IndexBuffer;
};

#endif // MESH_H
