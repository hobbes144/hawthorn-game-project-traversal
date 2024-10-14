#version 330 core
layout (location = 0) in vec3 vPos;
uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
uniform vec3 Color;

out vec3 final_color;

void main() {
    final_color = Color;
    gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(vPos, 1.0);
}