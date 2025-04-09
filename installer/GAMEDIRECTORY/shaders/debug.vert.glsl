#version 430 core

layout(location = 0) in vec4 vPos;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

out vec3 final_color;

void main() {
    final_color = vec3(0.0, 1.0, 0.0);
    gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vPos;
}
