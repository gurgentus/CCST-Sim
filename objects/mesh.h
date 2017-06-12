#ifndef MESH_H
#define MESH_H

#include <common/vertex.h>
#include <QtOpenGL>
#include <QOpenGLVertexArrayObject>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
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

//#define BUFFER_OFFSET(offset) ((void*)(offset))
//#define MEMBER_OFFSET(s,m) ((char*)NULL + (offsetof(s,m)))

using namespace std;

class Mesh {
    public:
        Mesh();
        ~Mesh();

        // vertex and index data containers
        typedef std::vector<Vertex>  PositionBuffer;
        typedef std::vector<GLuint>     IndexBuffer;
        // constant data
        constexpr static const float pi = 3.1415926535897932384626433832795f;
        constexpr static const float _2pi = 2.0f * pi;

        // setup car mesh based on vertex data or obj file
        virtual bool SetupDefaultMesh(QVector4D tex_signature) = 0;
        bool SetupMesh();
        bool SetupMesh(PositionBuffer position_buffer, IndexBuffer index_buffer);
        bool LoadMesh(const string &filename, QVector4D texSignature);


        void SetShaderProgram(QOpenGLShaderProgram *program);
        void SetModels();
        QMatrix4x4 local_to_world_matrix_;
        /*  Render data  */
        void Draw();
        void Cleanup();

        string getMesh_file() const;
        void setMesh_file(const string &value);

protected:
        string mesh_file = "";
        QOpenGLShaderProgram* p_program_;
        QOpenGLVertexArrayObject vao_;
        int model_to_world_;
        glm::mat4x4 m_LocalToWorldMatrix;
        glm::mat4x4 m_InverseLocalToWorldMatrix;

        PositionBuffer  position_buffer_;
        IndexBuffer     index_buffer_;
};

#endif // MESH_H
