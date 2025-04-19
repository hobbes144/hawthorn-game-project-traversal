///////////////////////////////////////////////////////////////////////////////
// Vertex shader for GBuffer
//
// Copyright © 2025 DIGIPEN Institute of Technology. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////
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

uniform mat4 ModelMatrix, InvModelMatrix;

out vec3 normalVec, worldPos;
out vec2 texCoord;
out vec3 tanVec;

void main()
{
    // Computes world position at a pixel used for
    // light and eye vector calculations
    worldPos=(ModelMatrix*vertex).xyz;

    // Computes the point’s projection on the screen
    gl_Position = projection*view*ModelMatrix*vertex;

    normalVec = vertexNormal*mat3(InvModelMatrix);

    tanVec = mat3(ModelMatrix)*vertexTangent;

    texCoord = vertexTexture;
}
