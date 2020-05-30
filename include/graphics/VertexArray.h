//
// Created by tony on 4/26/20.
//

#ifndef CHAPTER2_VERTEXARRAY_H
#define CHAPTER2_VERTEXARRAY_H


class VertexArray {
public:
    VertexArray(const float* verts, unsigned int numVerts,
            const unsigned int* indices, unsigned int numIndices);
    ~VertexArray();

    //Activate the array so that we may draw it.
    void setActive();

    unsigned int getNumVerts() { return mNumVerts; }
    unsigned int getNumIndices() { return mNumIndices; }

private:
    //How many vertices in the buffer
    unsigned int mNumVerts;
    //How many indices in the buffer
    unsigned int mNumIndices;
    // OpenGL id of the vertex buffer
    unsigned int mVertexBuffer;
    // OpenGL id of the index buffer
    unsigned int mIndexBuffer;
    // OpenGL id of the vertex array object
    unsigned int mVertexArray;
};


#endif //CHAPTER2_VERTEXARRAY_H
