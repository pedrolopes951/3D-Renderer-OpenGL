#pragma once
#include <Vertex.h>
#include <Debug.h>

class VertexBuffer
{
private:
    unsigned int m_RendererID; // Unique identifier to keep track of objects 

    const Vertex& m_data;
    unsigned int m_size;
public:
    VertexBuffer(const Vertex& data, unsigned int size);
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;
};

