#version 330 core
out vec4 FragColor;

in vec3 final_color;

void main() {
    FragColor = vec4(final_color, 1.0f);
}