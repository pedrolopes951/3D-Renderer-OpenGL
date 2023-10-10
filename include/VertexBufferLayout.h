#pragma once
#include <vector>
#include <GL/glew.h>
#include <Debug.h>

// This struct defines the properties of a single vertex attribute.
struct VertexBufferElement
{
    unsigned int type; // Data type, GL_FLOT, GL:UNSIGNED
    unsigned int count; //  How many Components make up the attributes (1 for scalar, 2 for 2d vectors , 3 for 3d vector ...)
    unsigned char normalized; // SHould or not be normalized the data 

    static unsigned int GetSizeOfType(unsigned int type)
    {
        switch (type)
        {

        case GL_FLOAT: return sizeof(GLfloat);
        case GL_UNSIGNED_INT: return sizeof(GLuint);
        case GL_UNSIGNED_BYTE: return sizeof(GLbyte);
        }
        ASSERT(false);
        return 0;
    }


};

// defining the layout of vertex data within a VBO
class VertexBufferLayout
{
private:
    unsigned int m_Stride; //offset between consecutive vertices in the VBO.
    std::vector<VertexBufferElement> m_Elements; //  VertexBufferElement instances, which collectively describe how the vertex data is organized.

public:
    VertexBufferLayout() :
        m_Stride(0) { }

    void AddFloat(unsigned int count) { Push(GL_FLOAT, count, GL_FALSE); }
    void AddUnsignedInt(unsigned int count) { Push(GL_UNSIGNED_INT, count, GL_FALSE); }
    void AddUnsignedByte(unsigned int count) { Push(GL_UNSIGNED_BYTE, count, GL_TRUE); }

    const std::vector<VertexBufferElement> GetElements() const { return m_Elements; };
    unsigned int GetStride() const { return m_Stride; };

private:
    void Push(unsigned int type, unsigned int count, unsigned char normalized)
    {
        struct VertexBufferElement vbe = { type, count, normalized };
        m_Elements.push_back(vbe);
        m_Stride += count * VertexBufferElement::GetSizeOfType(type);
    }
};
