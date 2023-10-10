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
    unsigned int maxVertexAttribs = 0; // Maximum number of vertex attributes

    //for (unsigned int i = 0; i < elements.size(); i++)
    //{
    //    const VertexBufferElement element = elements[i];
    //    GLCall(glEnableVertexAttribArray(i)); // Enable the vertex attribute at index i
    //    GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized,
    //        layout.GetStride(), INT2VOIDP(offset))); // Specifies how the attribute data is organized in the VBO and how it should be interpreted by shaders.
    //    offset += element.count * VertexBufferElement::GetSizeOfType(element.type);

    //    // Update the maximum number of vertex attributes
    //    maxVertexAttribs = std::max(maxVertexAttribs, i + 1);
    //}

    //// Disable any unused vertex attributes
    //for (unsigned int i = maxVertexAttribs; i < maxVertexAttribs; i++)
    //{
    //    glDisableVertexAttribArray(i);
    //}
   glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);// TODO : This needs to fo inside the for loop for the elements I wan to draw
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
