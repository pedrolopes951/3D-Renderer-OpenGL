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

}

Triangle::~Triangle()
{
    m_shader.Unbind();
}

void Triangle::Render()
{
    m_shader.Bind();
    m_shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
    m_va.Bind();
    m_eb.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, m_eb.GetCount(), GL_UNSIGNED_INT, nullptr));

}

void Triangle::ApplyTransformation(const Transformation& transformation)
{
    // Pass the model matrix to the shader
    unsigned int transformLoc = GLCall(glGetUniformLocation(m_shader.getID(), "transformation"));
    GLCall(glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformation.GetModelMatrix2D())));
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
    m_shader.Bind();
    m_shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

}


Square::~Square()
{
    m_shader.Unbind();

}

void Square::Render()
{

    m_shader.Bind();
    m_shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
    m_va.Bind();
    m_eb.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, m_eb.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Square::ApplyTransformation(const Transformation& transformation)
{
    // Pass the model matrix to the shader
    unsigned int transformLoc = GLCall(glGetUniformLocation(m_shader.getID(), "transformation"));
    GLCall(glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformation.GetModelMatrix2D())));
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
    m_shader.Unbind();
}

void Circle::Render()
{
    m_shader.Bind();
    m_shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
    m_va.Bind();
    m_eb.Bind();
    GLCall(glDrawElements(GL_TRIANGLE_FAN, m_eb.GetCount(), GL_UNSIGNED_INT, 0));
}

void Circle::ApplyTransformation(const Transformation& transformation)
{
    // Pass the model matrix to the shader
    unsigned int transformLoc = GLCall(glGetUniformLocation(m_shader.getID(), "transformation"));
    GLCall(glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformation.GetModelMatrix2D())));
}


Piramid::Piramid(const std::vector<Vertex3D>& vertex, const std::vector<unsigned int>& eb, const GLType typeVertices) : m_vb{ vertex }, m_eb{ eb }, m_layout{}, m_va{}, m_shader{ "shaders/Basic.shader" }
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
    m_shader.Bind();
    m_shader.SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
    m_va.Bind();
    m_eb.Bind();
}

Piramid::~Piramid()
{
    m_shader.Unbind();

}

void Piramid::Render()
{

    m_va.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, m_eb.GetCount(), GL_UNSIGNED_INT, 0));
}

void Piramid::ApplyTransformation(const Transformation& transformation)
{


    // create transformations
    glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
    model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, 0.0f));
    projection = glm::perspective(glm::radians(45.0f), (float)WINDOWHEIGHT / (float)WINDOWWIDTH, 0.1f, 100.0f);

    glm::mat4 transformation_matrix = projection * view * model;

    glUniformMatrix4fv(glGetUniformLocation(m_shader.getID(), "transformation"), 1, GL_FALSE, &transformation_matrix[0][0]);

    m_va.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, m_eb.GetCount(), GL_UNSIGNED_INT, 0));

    //// Pass the model matrix to the shader
    //unsigned int transformLoc = GLCall(glGetUniformLocation(m_shader.getID(), "transformation"));
    //GLCall(glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformation.GetModelMatrix3D())));
}
