#version 330 core
out vec4 FragColor;

in vec2 texcoord;
in vec3 final_color;

uniform bool useTexture;
uniform bool isTransparent;
uniform sampler2D mainTexture;

void main() {
    if (useTexture)
        FragColor = texture(mainTexture, texcoord);
    else {
        if(isTransparent)
            FragColor = vec4(final_color, 0.0f);
        else
            FragColor = vec4(final_color, 1.0f);
    }
        
}