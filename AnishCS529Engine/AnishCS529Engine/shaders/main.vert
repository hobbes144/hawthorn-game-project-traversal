/////////////////////////////////////////////////////////////////////////
// Main Vertex shader
//
// Copyright 2013 DigiPen Institute of Technology
////////////////////////////////////////////////////////////////////////
#version 330

uniform mat4 WorldView, WorldInverse, WorldProj, ModelTr, NormalTr;
in vec4 vertex;
in vec3 vertexNormal;

void LightingVertex(vec3 eye); // Signature of the separated procedure
void main()
{
    // Computes world position at a pixel used for
    // light and eye vector calculations
    vec3 worldPos;
    worldPos=(ModelTr*vertex).xyz;

    // Computes the point’s projection on the screen
    gl_Position = WorldProj*WorldView*ModelTr*vertex;
    vec3 eyePos = (WorldInverse*vec4(0,0,0,1)).xyz;

    LightingVertex(eyePos);
}
