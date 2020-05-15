// Request GLSL 3.3
#version 330

// The input must match name and type of the output in the vertex shader
in vec2 fragTextCoord;

// The output color to the color buffer
out vec4 outColor;

// Texture sampling
uniform sampler2D uTexture;

void main() {
    // Set the color to blue
    outColor = texture(uTexture, fragTextCoord);
}