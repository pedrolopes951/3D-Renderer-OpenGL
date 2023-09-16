#include "VertexBuffer.h"


VertexBuffer::VertexBuffer(const Vertex* data, unsigned int size)
{
    GLCall(glGenBuffers(1, &m_RendererID)); // Generate a VBO identifier and store it in m_RendererID
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID)); // Bind the VBO 
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW)); // Allocate memory on the gpuand copy data to the VBO GL_STATIC_DRAW hint that the actual vertex data gets loaded into the vbo

}

VertexBuffer::~VertexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RendererID)); // Delete VBO identified by m_RendererID
}

void VertexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID)); // This activated the buffer, this tell the current OpenGlContex that this buffer is ready operated on
}

void VertexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0)); // Unbind it, deactivating the current VBO feeir in for other operations 
}
