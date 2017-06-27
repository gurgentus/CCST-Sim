#version 330 core

layout(location=0) in vec3 in_position;
layout(location=1) in vec4 color;
layout(location=2) in vec3 in_normal;
layout(location=8) in vec2 in_texcoord;

out vec4 v2f_positionW; // Position in world space.
out vec4 v2f_normalW; // Surface normal in world space.
out vec2 v2f_texcoord;
out vec4 vColor;

// Model, View, Projection matrix.
// uniform mat4 ModelViewProjectionMatrix;
// uniform mat4 ModelMatrix;

uniform mat4 modelToWorld;
uniform mat4 worldToCamera;
uniform mat4 cameraToView;

void main()
{
    gl_Position = cameraToView * worldToCamera * modelToWorld * vec4(in_position, 1);

    v2f_positionW = cameraToView * worldToCamera * modelToWorld * vec4(in_position, 1);//modelToWorld * vec4(in_position, 1);
    v2f_normalW = cameraToView * worldToCamera * modelToWorld * vec4(in_normal, 0); //modelToWorld * vec4(in_normal, 0);
    v2f_texcoord = in_texcoord;
    vColor = color;
}
