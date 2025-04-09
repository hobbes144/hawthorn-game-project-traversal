/////////////////////////////////////////////////////////////////////////
// Main Vertex shader
//
// Copyright 2013 DigiPen Institute of Technology
////////////////////////////////////////////////////////////////////////
#version 440

in vec4 vertex;
in vec3 vertexNormal;
in vec2 vertexTexture;
in vec3 vertexTangent;

layout (binding = 0) uniform camera
{
    mat4 projection;
    mat4 view;
    mat4 inverseView;
    float exposure;
};

struct DirectionalLight {
  vec3 direction;
  float intensity;
  vec3 color;
  float padding0;
};

struct AmbientLight {
  vec3 color;
  float intensity;
};

layout (binding = 1) uniform lights
{
  DirectionalLight sunLight;
  AmbientLight ambientLight;
};

uniform mat4 ModelMatrix, InvModelMatrix;

out vec3 normalVec, lightVec, eyeVec;
out vec2 texCoord;
out vec3 tanVec;

void main()
{
    // Computes world position at a pixel used for
    // light and eye vector calculations
    vec3 worldPos;
    worldPos=(ModelMatrix*vertex).xyz;

    // Computes the point’s projection on the screen
    gl_Position = projection*view*ModelMatrix*vertex;
    vec3 eyePos = (inverseView*vec4(0,0,0,1)).xyz;

    normalVec = vertexNormal*mat3(InvModelMatrix);
    lightVec = sunLight.direction;
    eyeVec = eyePos-worldPos;

    tanVec = mat3(ModelMatrix)*vertexTangent;

    texCoord = vertexTexture;
}
