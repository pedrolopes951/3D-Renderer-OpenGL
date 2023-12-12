#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

// Vertex Array Objects (VAOs)
template<typename T>
class VertexArray
{
public:
    VertexArray()
    {
        GLCall(glGenVertexArrays(1, &m_RendererID));

    }
    ~VertexArray()
    {
        GLCall(glDeleteVertexArrays(1, &m_RendererID));
    }


    void AddBuffer(const VertexBuffer<T>& vb, const VertexBufferLayout& layout, GLType type)
    {
        const std::vector<VertexBufferElement> elements = layout.GetElements();
        unsigned int offset = 0;

        for (unsigned int i = 0; i < elements.size(); i++)
        {
            const VertexBufferElement element = elements[i];
            GLCall(glVertexAttribPointer(i, element.count, VertexBufferElement::ConvertGLType(element.type), element.normalized,
                layout.GetStride(), INT2VOIDP(offset))); // Specifies how the attribute data is organized in the VBO and how it should be interpreted by shaders.
            offset += element.count * VertexBufferElement::GetSizeOfType(element.type);

            GLCall(glEnableVertexAttribArray(i)); // Enable the vertex attribute at index i
            // Update the maximum number of vertex attributes
        }

    }
    void Bind() const
    {
        GLCall(glBindVertexArray(m_RendererID));
    }
    void Unbind() const
    {
        GLCall(glBindVertexArray(0));
    }

private:
    unsigned int m_RendererID;
};

