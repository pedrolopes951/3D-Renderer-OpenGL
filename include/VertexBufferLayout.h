#pragma once
#include <vector>
#include <GL/glew.h>
#include <Debug.h>
#include "Vertex.h"

// This struct defines the properties of a single vertex attribute.
struct VertexBufferElement
{
    GLType type; // Data type, GL_FLOT, GL:UNSIGNED
    unsigned int count; //  How many Components make up the attributes (1 for scalar, 2 for 2d vectors , 3 for 3d vector ...)
    unsigned char normalized; // SHould or not be normalized the data 

    static unsigned int GetSizeOfType(GLType type)
    {
        switch (type)
        {
        case GLType::VERTEX3D: return 3 * sizeof(GLfloat);
        case GLType::VERTEX2D: return 2 * sizeof(GLfloat);
        case GLType::FLOAT : return sizeof(GLfloat);
        case GLType::UNSIGNED_INT: return sizeof(GLuint);
        case GLType::UNSIGNED_BYTE: return sizeof(GLbyte);
        }
        ASSERT(false);
        return 0;
    }

    static GLenum ConvertGLType(GLType type)
    {
        switch (type)
        {
        case GLType::VERTEX3D:
            return GL_FLOAT;
        case GLType::VERTEX2D:
            return GL_FLOAT;
        case GLType::FLOAT:
            return GL_FLOAT;
        case GLType::UNSIGNED_INT:
            return GL_UNSIGNED_INT;
        case GLType::UNSIGNED_BYTE:
            return GL_UNSIGNED_BYTE;
        default:
            ASSERT(false); // Handle an unsupported GLType or assert if necessary.
            return 0;
        }
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
    void AddVertex3D(unsigned int count) { Push(GLType::VERTEX3D, count, GL_FALSE); }
    void AddVertex2D(unsigned int count) { Push(GLType::VERTEX2D, count, GL_FALSE); }
    void AddFloat(unsigned int count) { Push(GLType::FLOAT, count, GL_FALSE); }
    void AddUnsignedInt(unsigned int count) { Push(GLType::UNSIGNED_INT, count, GL_FALSE); }
    void AddUnsignedByte(unsigned int count) { Push(GLType::UNSIGNED_BYTE, count, GL_TRUE); }

    const std::vector<VertexBufferElement> GetElements() const { return m_Elements; };
    unsigned int GetStride() const { return m_Stride; };

private:
    void Push(GLType type, unsigned int count, unsigned char normalized)
    {
        struct VertexBufferElement vbe = { type, count, normalized };
        m_Elements.push_back(vbe);
        m_Stride += VertexBufferElement::GetSizeOfType(type);
    }
};
