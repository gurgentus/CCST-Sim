#include "mesh.h"
#include <stdio.h>
#include <iostream>

Mesh::Mesh()
{
    local_to_world_matrix_.setToIdentity();
}

Mesh::~Mesh()
{

}

void Mesh::SetShaderProgram(QOpenGLShaderProgram* program)
{
    p_program_ = program;
}

void Mesh::SetModels()
{
    model_to_world_ = p_program_->uniformLocation("modelToWorld");
    p_program_->setUniformValue(model_to_world_, QMatrix4x4(local_to_world_matrix_));
}

bool Mesh::SetupMesh(PositionBuffer position_buffer, IndexBuffer index_buffer)
{
    position_buffer_ = position_buffer;
    index_buffer_ = index_buffer;
    return SetupMesh();

}

bool Mesh::SetupMesh()
{
    QOpenGLBuffer m_vertex;
    QOpenGLBuffer m_index(QOpenGLBuffer::IndexBuffer);



    // Create Vertex Array Object
    vao_.create();
    vao_.bind();


    m_vertex.create();
    if ( !m_vertex.bind() )
     {
     qWarning() << "Could not bind vertex buffer to the context";
     return false;
     }
    m_vertex.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vertex.allocate(position_buffer_.data(), position_buffer_.size() * Vertex::stride());
    //m_vertex.allocate(&(m_PositionBuffer[0]), m_PositionBuffer.size() * Vertex::stride());

    //m_vertex[0].allocate(positions.data(), positions.size() * sizeof(vec3));

    p_program_->enableAttributeArray(POSITION_ATTRIBUTE);
    p_program_->setAttributeBuffer(POSITION_ATTRIBUTE, GL_FLOAT, Vertex::positionOffset(), Vertex::PositionTupleSize, Vertex::stride());
    p_program_->enableAttributeArray(COLOR_ATTRIBUTE);
    p_program_->setAttributeBuffer(COLOR_ATTRIBUTE, GL_FLOAT, Vertex::colorOffset(), Vertex::ColorTupleSize, Vertex::stride());
    p_program_->enableAttributeArray(NORMAL_ATTRIBUTE);
    p_program_->setAttributeBuffer(NORMAL_ATTRIBUTE, GL_FLOAT, Vertex::normalOffset(), Vertex::NormalTupleSize, Vertex::stride());
    p_program_->enableAttributeArray(TEXCOORD0_ATTRIBUTE);
    p_program_->setAttributeBuffer(TEXCOORD0_ATTRIBUTE, GL_FLOAT, Vertex::texCoordOffset(), Vertex::TexCoordTupleSize, Vertex::stride());

    m_index.create();

    if ( !m_index.bind() )
     {
     qWarning() << "Could not bind index buffer to the context";
     return false;
     }

    m_index.setUsagePattern(QOpenGLBuffer::StaticDraw);
    //m_index.allocate(m_IndexBuffer.data(), m_IndexBuffer.size()*sizeof(GLuint));
    m_index.allocate(&(index_buffer_[0]), sizeof(GLuint) * index_buffer_.size());

    // Release (unbind) all
    vao_.release();
    m_vertex.release();
    m_index.release();
    std::cout << "Mesh setup finished" << std::endl;
    return true;
}

// original source for the functionality:
// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/
bool Mesh::LoadMesh(const std::string& filename, QVector4D texSignature)
{
    std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
    std::vector< glm::vec3 > temp_vertices;
    std::vector< glm::vec2 > temp_uvs;
    std::vector< glm::vec3 > temp_normals;

    //FILE * file = fopen(path, "r");
    std::cout << filename << std::endl;
    QFile q_file(QString::fromStdString(filename));
    //if( !fs::exists(filename) )
    if( !q_file.exists() )
    {
        std::cerr << "Could not find file: " << q_file.fileName().toStdString() << std::endl;
        return false;
    }
    q_file.open(QFile::ReadOnly);

//    int fd = q_file.handle();
//    qDebug() <<fd;
//    FILE* file = fdopen(fd, "r");

    QTextStream in(&q_file);
    while (!in.atEnd())
    {
         QString q_line = in.readLine();
         QByteArray array = q_line.toLocal8Bit();
         char* line = array.data();

         char lineHeader[128];
         // read the first word of the line
         sscanf(line, "%s", lineHeader);

         // else : parse lineHeader
         if ( strcmp( lineHeader, "v" ) == 0 ){
                glm::vec3 vertex;
                sscanf(line, "%s %f %f %f\n", &lineHeader, &vertex.x, &vertex.y, &vertex.z );
                temp_vertices.push_back(vertex);
         }
         else if ( strcmp( lineHeader, "vt" ) == 0 ){
                glm::vec2 uv;
                sscanf(line, "%s %f %f\n", &lineHeader, &uv.x, &uv.y );
                temp_uvs.push_back(uv);
         }
         else if ( strcmp( lineHeader, "vn" ) == 0 ){
                glm::vec3 normal;
                sscanf(line, "%s %f %f %f\n", &lineHeader, &normal.x, &normal.y, &normal.z );
                temp_normals.push_back(normal);
         }
         else if ( strcmp( lineHeader, "f" ) == 0 ){
                std::string vertex1, vertex2, vertex3;
                unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];

                int matches = sscanf(line, "%s%d/%d/%d %d/%d/%d %d/%d/%d\n", &lineHeader, &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
                if (matches != 10){
                    printf("File can't be read by our simple parser : ( Try exporting with other options\n");
                    return false;
                }
                vertexIndices.push_back(vertexIndex[0]);
                vertexIndices.push_back(vertexIndex[1]);
                vertexIndices.push_back(vertexIndex[2]);
                uvIndices    .push_back(uvIndex[0]);
                uvIndices    .push_back(uvIndex[1]);
                uvIndices    .push_back(uvIndex[2]);
                normalIndices.push_back(normalIndex[0]);
                normalIndices.push_back(normalIndex[1]);
                normalIndices.push_back(normalIndex[2]);
        }
    }
    q_file.close();

    // For each vertex of each triangle
    for( unsigned int i=0; i<vertexIndices.size(); i++ ){
        unsigned int vertexIndex = vertexIndices[i];
        unsigned int uvIndex = uvIndices[i];
        unsigned int normalIndex = normalIndices[i];
        glm::vec3 vertex = temp_vertices[ vertexIndex-1 ];
        glm::vec2 uv = temp_uvs[uvIndex - 1];
        glm::vec3 normal = temp_normals[normalIndex - 1];
        position_buffer_.push_back (Vertex(QVector3D(vertex.x, vertex.y, vertex.z), texSignature,
                                           QVector3D(normal.x, normal.y, normal.z), QVector2D(uv.x,uv.y) ));
        index_buffer_.push_back(i);


    }

    return SetupMesh();
}

void Mesh::Draw()
{
  // render using the shader
  // std::cout << index_buffer_.size() << std::endl;
  vao_.bind();
  glDrawElements(GL_TRIANGLES, index_buffer_.size(), GL_UNSIGNED_INT, 0);
  vao_.release();

}

void Mesh::Cleanup()
{
    vao_.destroy();
}

string Mesh::getMesh_file() const
{
    return mesh_file;
}

void Mesh::setMesh_file(const string &value)
{
    mesh_file = value;
}
