/////////////////////////////////////////////////////////////////////////
// Vertex shader for lighting
//
// Copyright 2013 DigiPen Institute of Technology
////////////////////////////////////////////////////////////////////////
#version 430

uniform mat4 ModelMatrix, InvModelMatrix;
uniform mat4 ShadowMatrix;

uniform vec3 lightPos;

layout(location = 0) in vec4 vertex;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec2 vertexTexture;
layout(location = 3) in vec3 vertexTangent;

out vec3 normalVec, lightVec, eyeVec;
out vec2 texCoord;
out vec3 tanVec;

out vec4 shadowCoord;

void LightingVertex(vec3 eyePos)
{
    // Computes world position at a pixel used for
    // light and eye vector calculations
    vec3 worldPos;
    worldPos=(ModelMatrix*vertex).xyz;

    normalVec = vertexNormal*mat3(InvModelMatrix);
    lightVec = lightPos - worldPos;
    eyeVec = eyePos-worldPos;

    tanVec = mat3(ModelMatrix)*vertexTangent;

    texCoord = vertexTexture;

    shadowCoord = ShadowMatrix * ModelMatrix * vertex;
}
