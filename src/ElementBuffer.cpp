#include "ElementBuffer.h"
#include "Debug.h"


ElementBuffer::ElementBuffer(const std::vector<unsigned int>& indices) : m_indices{indices},m_Count(indices.size())
{
    ASSERT(sizeof(unsigned int) == sizeof(GLuint));

    GLCall(glGenBuffers(1, &m_RendererID));
}

ElementBuffer::~ElementBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

void ElementBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Count * sizeof(unsigned int), m_indices.data(), GL_STATIC_DRAW));
}

void ElementBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
