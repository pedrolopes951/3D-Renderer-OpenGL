#pragma once
#include <Vertex.h>
#include <Debug.h>
#include <vector>


template<typename T>
class VertexBuffer
{
private:
    unsigned int m_RendererID; // Unique identifier to keep track of objects 

    const std::vector<T>& m_data;
    unsigned int m_size;
public:
    VertexBuffer(const std::vector<T>& data): m_data{ data }, m_size(data.size() * sizeof(T))
    {
        GLCall(glGenBuffers(1, &m_RendererID)); // Generate a VBO identifier and store it in m_RendererID

    };
    ~VertexBuffer()
    {
        GLCall(glDeleteBuffers(1, &m_RendererID)); // Delete VBO identified by m_RendererID
    }

    void Bind() const
    {
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID)); // This activated the buffer, this tell the current OpenGlContex that this buffer is ready operated on
        GLCall(glBufferData(GL_ARRAY_BUFFER, m_size, m_data.data(), GL_STATIC_DRAW));
    }
    void Unbind() const
    {
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0)); // Unbind it, deactivating the current VBO feeir in for other operations
    }

};

