#include "Models.h"


Triangle::Triangle(const Vertex& vertex, const unsigned int size, const GLType typeVertices, const int countVertices) : m_vb{vertex,size}, m_layout{}, m_va{}, m_countvertices{countVertices}
{
    switch (typeVertices)
    {
    case GLType::FLOAT:
        m_layout.AddFloat(countVertices);
        break;
    case GLType::UNSIGNED_INT:
        m_layout.AddUnsignedInt(countVertices);
        break;
    case GLType::UNSIGNED_BYTE:
        m_layout.AddUnsignedByte(countVertices);
        break;
    default:
        std::cout << "Not Valid GLType" << std::endl;
        throw("Not Valid GLType");
        break;
    }
    m_va.AddBuffer(m_vb, m_layout);
  
}

Triangle::~Triangle()
{
}

void Triangle::Render()
{
    m_va.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, m_countvertices, GL_UNSIGNED_INT, nullptr));

}

Square::Square(const Vertex& vertex, const unsigned int size, const GLType typeVertices, const int countVertices) : m_vb{ vertex,sizeof(vertex) }, m_layout{}, m_va{}, m_countvertices{ countVertices }
{
    switch (typeVertices)
    {
    case GLType::FLOAT:
        m_layout.AddFloat(countVertices);
        break;
    case GLType::UNSIGNED_INT:
        m_layout.AddUnsignedInt(countVertices);
        break;
    case GLType::UNSIGNED_BYTE:
        m_layout.AddUnsignedByte(countVertices);
        break;
    default:
        std::cout << "Not Valid GLType" << std::endl;
        throw("Not Valid GLType");
        break;
    }
}


Square::~Square()
{
}

void Square::Render()
{
}

Circle::Circle(const Vertex& vertex, const unsigned int size, const GLType typeVertices, const int countVertices) : m_vb{ vertex,sizeof(vertex) }, m_layout{}, m_va{}
{
    switch (typeVertices)
    {
    case GLType::FLOAT:
        m_layout.AddFloat(countVertices);
        break;
    case GLType::UNSIGNED_INT:
        m_layout.AddUnsignedInt(countVertices);
        break;
    case GLType::UNSIGNED_BYTE:
        m_layout.AddUnsignedByte(countVertices);
        break;
    default:
        std::cout << "Not Valid GLType" << std::endl;
        throw("Not Valid GLType");
        break;
    }
}


Circle::~Circle()
{
}

void Circle::Render()
{
}
