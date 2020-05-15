// Request GLSL 3.3
#version 330

// This should correspond to the data stored
// for each vertex in the vertex buffer.
// For now, just a position.
in vec3 inPosition;

// Uniform variables do not change between shader invocations
uniform mat4 uWorldTransform;
uniform mat4 uViewProj;

void main() {
    // The vertex shader needs to output a 4D
    // coordinate.
    // For now set the 4th coordinate to 1.0
    vec4 position = vec4(inPosition, 1.0);
    gl_Position = position * uWorldTransform * uViewProj;
}