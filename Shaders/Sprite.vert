// Request GLSL 3.3
#version 330

// This should correspond to the data stored
// for each vertex in the vertex buffer.
// location refers to which index it is in the glVertexAttribPointer call
layout(location=0) in vec3 inPosition;
layout(location=1) in vec3 inNormal;
layout(location=2) in vec2 inTexCoord;

// Uniform variables do not change between shader invocations
uniform mat4 uWorldTransform;
uniform mat4 uViewProj;

// The fragment shader needs to know about the text coordinates to determine the color.
// This is a declaration of a global out variable for the fragment shader.
out vec2 fragTextCoord;

void main() {
    // The vertex shader needs to output a 4D
    // coordinate.
    // For now set the 4th coordinate to 1.0
    vec4 position = vec4(inPosition, 1.0);
    gl_Position = position * uWorldTransform * uViewProj;
    // Pass along the texture coordinates to the fragment shader.
    fragTextCoord = inTexCoord;
}