//
// Created by tony on 4/26/20.
//

#include <GL/glew.h>
#include "graphics/VertexArray.h"

VertexArray::VertexArray(const float *verts, unsigned int numVerts, const unsigned int *indices,
                         unsigned int numIndices) : mNumVerts(numVerts), mNumIndices(numIndices) {
    // Establish the vertex array from OpenGL
    glGenVertexArrays(1, &mVertexArray);
    glBindVertexArray(mVertexArray);

    //One vertex array object is bound, we can create our vertex buffer
    glGenBuffers(1, &mVertexBuffer);
    // GL_ARRAY_BUFFER signals that we want to use this as a vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
    // Now that the buffer is bound, send the data
    glBufferData(
            GL_ARRAY_BUFFER, // The active buffer to write to
            numVerts * 8 * sizeof(float), // Number of bytes we are copying
            verts,  // Source to copy data from
            GL_STATIC_DRAW // How will this data be used.
            );

    // create the index buffer
    glGenBuffers(1, &mIndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
    // Copy the indices into the buffer
    glBufferData(
            GL_ELEMENT_ARRAY_BUFFER,
            numIndices * sizeof(unsigned int),
            indices,
            GL_STATIC_DRAW
            );

    //specify vertex layout
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
            0,  // Attribute index (0 for first one)
            3,  // Number of components (3 in our case)
            GL_FLOAT, // Type of components
            GL_FALSE, // (only used for integral types)
            sizeof(float) * 8, // Stride (usually size of each vertex)
            0 // Offset from start of vertex to this attribute
            );
    //Vertex attribute for the texture
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8,
                          reinterpret_cast<void*>(sizeof(float) * 3));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8,
                          reinterpret_cast<void*>(sizeof(float ) * 6));

}

VertexArray::~VertexArray() {
    glDeleteBuffers(1, &mVertexBuffer);
    glDeleteBuffers(1, &mIndexBuffer);
    glDeleteVertexArrays(1, &mVertexArray);
}

void VertexArray::setActive() {
    //Specify the current vertex we are using
    glBindVertexArray(mVertexArray);
}