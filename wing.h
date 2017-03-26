#ifndef WING_H
#define WING_H

#include "part.h"
#include "sbody.h"

class Wing : public Part
{
public:
    Wing();

    Part mainPart;
    Part aileron;
    Control* aileronAngleControl;

    typedef std::vector<Vertex>  PositionBuffer;
//    typedef std::vector<glm::vec4>  ColorBuffer;
//    typedef std::vector<glm::vec3>  NormalBuffer;
//    typedef std::vector<glm::vec2>  TexCoordBuffer;
    typedef std::vector<GLuint>     IndexBuffer;


    float l = 0;
    float b = 0;
    float ao = 0;
    float aw = 0;
    float al = 0;
    void setDimensions(float l, float b, float ao, float aw, float al);
    void initializeControls();
    void updateControls();
};

#endif // WING_H
