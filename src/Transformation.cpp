#include "Transformation.h"




Transformation::Transformation() : m_projection{ glm::ortho(0.0f, WINDOWWIDTH, 0.0f, WINDOWHEIGHT) }, m_indentyMatrix{glm::mat4(1.0f)}
{
}

Transformation::~Transformation()
{
}

void Transformation::Translate(float x, float y, float z) {
    m_modelMatrix = glm::translate(m_indentyMatrix, glm::vec3(x, y, z));
}

void  Transformation::Rotate(float angle, float x, float y, float z) {
    m_modelMatrix = glm::rotate(m_indentyMatrix, glm::radians(angle), glm::vec3(x, y, z));
}

void  Transformation::Scale(float x, float y, float z) {
    m_modelMatrix = glm::scale(m_indentyMatrix, glm::vec3(x, y, z));
}

void Transformation::Ortho(float left, float right, float bottom, float top)
{
    m_projection = glm::ortho(left, right, bottom, top);

}



const glm::mat4& Transformation::GetModelMatrix() const {
    return m_projection*m_modelMatrix;
}
