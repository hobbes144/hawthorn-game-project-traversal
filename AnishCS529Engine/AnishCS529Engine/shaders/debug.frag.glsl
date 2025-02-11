#version 430 core
out vec4 FragColor;

in vec2 texcoord;
in vec3 final_color;

void main() {
  FragColor = vec4(final_color, 0.0f);
}
