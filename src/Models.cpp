#include "Models.h"


Triangle::Triangle(const std::vector<Vertex>& vertex, const std::vector<unsigned int>& eb, const GLType typeVertices) : m_vb{vertex}, m_eb{eb}, m_layout{}, m_va{}, m_countvertices{ vertex.size()}
{
    switch (typeVertices)
    {
    case GLType::VERTEX3D:
        m_layout.AddVertex3D(m_countvertices);
        break;
    case GLType::VERTEX2D:
        m_layout.AddVertex2D(m_countvertices);
        break;
    case GLType::FLOAT:
        m_layout.AddFloat(m_countvertices);
        break;
    case GLType::UNSIGNED_INT:
        m_layout.AddUnsignedInt(m_countvertices);
        break;
    case GLType::UNSIGNED_BYTE:
        m_layout.AddUnsignedByte(m_countvertices);
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
    m_eb.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, m_eb.GetCount(), GL_UNSIGNED_INT, nullptr));

}

Square::Square(const std::vector<Vertex>& vertex, const std::vector<unsigned int>& eb, const GLType typeVertices) : m_vb{ vertex }, m_eb{ eb },m_layout{}, m_va{}, m_countvertices{ m_eb.GetCount()}
{
    switch (typeVertices)
    {
    case GLType::FLOAT:
        m_layout.AddFloat(m_countvertices);
        break;
    case GLType::UNSIGNED_INT:
        m_layout.AddUnsignedInt(m_countvertices);
        break;
    case GLType::UNSIGNED_BYTE:
        m_layout.AddUnsignedByte(m_countvertices);
        break;
    default:
        std::cout << "Not Valid GLType" << std::endl;
        throw("Not Valid GLType");
        break;
    }
    m_va.AddBuffer(m_vb, m_layout);

}


Square::~Square()
{
}

void Square::Render()
{
    m_va.Bind();
    m_eb.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, m_eb.GetCount(), GL_UNSIGNED_INT, nullptr));
}

Circle::Circle(const std::vector<Vertex>& vertex, const std::vector<unsigned int>& eb, const GLType typeVertices) : m_vb{ vertex },  m_eb{ eb }, m_layout{}, m_va{}, m_countvertices{ m_eb.GetCount() }
{
    switch (typeVertices)
    {
    case GLType::FLOAT:
        m_layout.AddFloat(m_countvertices);
        break;
    case GLType::UNSIGNED_INT:
        m_layout.AddUnsignedInt(m_countvertices);
        break;
    case GLType::UNSIGNED_BYTE:
        m_layout.AddUnsignedByte(m_countvertices);
        break;
    default:
        std::cout << "Not Valid GLType" << std::endl;
        throw("Not Valid GLType");
        break;
    }
    m_va.AddBuffer(m_vb, m_layout);

}


Circle::~Circle()
{
}

void Circle::Render()
{
    m_va.Bind();
    m_eb.Bind();
    GLCall(glDrawElements(GL_TRIANGLE_FAN, m_countvertices + 1, GL_UNSIGNED_INT, 0));
}
