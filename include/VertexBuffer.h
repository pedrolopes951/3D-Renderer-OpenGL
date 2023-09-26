#pragma once
#include <Vertex.h>
#include <Debug.h>
#include <vector>

class VertexBuffer
{
private:
    unsigned int m_RendererID; // Unique identifier to keep track of objects 

    const std::vector<Vertex>& m_data;
    unsigned int m_size;
public:
    VertexBuffer(const std::vector<Vertex>& data);
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;
};

