#include "Models.h"


Triangle::Triangle(const Vertex* vertex, const GLType typeVertices, const int countVertices) : m_vb{vertex,countVertices * sizeof(vertex)}, m_layout{}, m_va{}, m_countvertices{countVertices}
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

Triangle::~Triangle()
{
}

void Triangle::Render()
{
    m_va.Bind();
    GLCall(glDrawArrays(GL_TRIANGLES,0, m_countvertices));
    GLCall(glDrawElements(GL_TRIANGLES, m_countvertices, GL_UNSIGNED_INT, nullptr));

}

Square::Square(const Vertex* vertex, const GLType typeVertices, const int countVertices) : m_vb{ vertex,sizeof(vertex) }, m_layout{}, m_va{}, m_countvertices{ countVertices }
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

Circle::Circle(const Vertex* vertex, const GLType typeVertices, const int countVertices) : m_vb{ vertex,sizeof(vertex) }, m_layout{}, m_va{}
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
