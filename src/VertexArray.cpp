#include "VertexArray.h"
#include "Debug.h"

VertexArray::VertexArray()
{
    GLCall(glGenVertexArrays(1, &m_RendererID));
}

VertexArray::~VertexArray()
{
    GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
    Bind(); // Performs operation in this VAO
    vb.Bind(); // Makes this VBO active for attribute data
    const std::vector<VertexBufferElement> elements = layout.GetElements();
    unsigned int offset = 0;
    for (unsigned int i = 0; i < elements.size(); i++) 
    {
        const VertexBufferElement element = elements[i];
        GLCall(glEnableVertexAttribArray(i)); // Enable the vertex attribute at index i
        GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized,
            layout.GetStride(), INT2VOIDP(offset))); // pecifies how the attribute data is organized in the VBO and how it should be interpreted by shaders.
        offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
    }
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void VertexArray::Bind() const
{
    GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::Unbind() const
{
    GLCall(glBindVertexArray(0));
};
