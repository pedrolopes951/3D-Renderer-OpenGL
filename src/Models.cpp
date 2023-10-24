#include "Models.h"

constexpr int NUMCOUNT1D = 1;
constexpr int NUMCOUNT2D = 2;
constexpr int NUMCOUNT3D = 3;



Triangle::Triangle(const std::vector<Vertex2D>& vertex, const std::vector<unsigned int>& eb, const GLType typeVertices) : m_vb{ vertex }, m_eb{ eb }, m_layout{}, m_va{}, m_shader{ "shaders/Basic.shader" }
{
    switch (typeVertices)
    {
    case GLType::VERTEX3D:
        m_layout.AddVertex3D(NUMCOUNT3D);
        m_va.AddBuffer(m_vb, m_layout, typeVertices);
        break;
    case GLType::VERTEX2D:
        m_layout.AddVertex2D(NUMCOUNT2D);
        m_va.AddBuffer(m_vb, m_layout, typeVertices);
        break;
    case GLType::FLOAT:
        m_layout.AddFloat(NUMCOUNT2D);
        m_va.AddBuffer(m_vb, m_layout, typeVertices);
        break;
    case GLType::UNSIGNED_INT:
        m_layout.AddUnsignedInt(NUMCOUNT2D);
        m_va.AddBuffer(m_vb, m_layout, typeVertices);
        break;
    case GLType::UNSIGNED_BYTE:
        m_layout.AddUnsignedByte(NUMCOUNT2D);
        m_va.AddBuffer(m_vb, m_layout, typeVertices);
        break;
    default:
        std::cout << "Not Valid GLType" << std::endl;
        throw("Not Valid GLType");
        break;
    }

    //m_shader.Bind();
    //// Set a color for now
    //m_shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
}

Triangle::~Triangle()
{
    m_shader.Unbind();
}

void Triangle::Render()
{
    m_shader.Bind();
    // Set a color for now
    m_shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
    m_va.Bind();
    m_eb.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, m_eb.GetCount(), GL_UNSIGNED_INT, nullptr));

}

void Triangle::ApplyTransformation(const Transformation& transformation)
{
    // Pass the model matrix to the shader
    unsigned int transformLoc = GLCall(glGetUniformLocation(m_shader.getID(), "transform"));
    GLCall(glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformation.GetModelMatrix())));
}

Square::Square(const std::vector<Vertex2D>& vertex, const std::vector<unsigned int>& eb, const GLType typeVertices) : m_vb{ vertex }, m_eb{ eb }, m_layout{}, m_va{}, m_shader{ "shaders/Basic.shader" }
{
    switch (typeVertices)
    {
    case GLType::VERTEX3D:
        m_layout.AddVertex3D(NUMCOUNT3D);
        m_va.AddBuffer(m_vb, m_layout, typeVertices);
        break;
    case GLType::VERTEX2D:
        m_layout.AddVertex2D(NUMCOUNT2D);
        m_va.AddBuffer(m_vb, m_layout, typeVertices);
        break;
    case GLType::FLOAT:
        m_layout.AddFloat(NUMCOUNT2D);
        m_va.AddBuffer(m_vb, m_layout, typeVertices);
        break;
    case GLType::UNSIGNED_INT:
        m_layout.AddUnsignedInt(NUMCOUNT2D);
        m_va.AddBuffer(m_vb, m_layout, typeVertices);
        break;
    case GLType::UNSIGNED_BYTE:
        m_layout.AddUnsignedByte(NUMCOUNT2D);
        m_va.AddBuffer(m_vb, m_layout, typeVertices);
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
    m_va.Bind();
    m_eb.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, m_eb.GetCount(), GL_UNSIGNED_INT, nullptr));
}

Circle::Circle(const std::vector<Vertex2D>& vertex, const std::vector<unsigned int>& eb, const GLType typeVertices) : m_vb{ vertex }, m_eb{ eb }, m_layout{}, m_va{}, m_shader{ "shaders/Basic.shader" }
{
    switch (typeVertices)
    {
    case GLType::VERTEX3D:
        m_layout.AddVertex3D(NUMCOUNT3D);
        m_va.AddBuffer(m_vb, m_layout, typeVertices);
        break;
    case GLType::VERTEX2D:
        m_layout.AddVertex2D(NUMCOUNT2D);
        m_va.AddBuffer(m_vb, m_layout, typeVertices);
        break;
    case GLType::FLOAT:
        m_layout.AddFloat(NUMCOUNT2D);
        m_va.AddBuffer(m_vb, m_layout, typeVertices);
        break;
    case GLType::UNSIGNED_INT:
        m_layout.AddUnsignedInt(NUMCOUNT2D);
        m_va.AddBuffer(m_vb, m_layout, typeVertices);
        break;
    case GLType::UNSIGNED_BYTE:
        m_layout.AddUnsignedByte(NUMCOUNT2D);
        m_va.AddBuffer(m_vb, m_layout, typeVertices);
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
    m_va.Bind();
    m_eb.Bind();
    GLCall(glDrawElements(GL_TRIANGLE_FAN,m_eb.GetCount(), GL_UNSIGNED_INT, 0));
}
