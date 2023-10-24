#include "Transformation.h"




Transformation::Transformation() : m_modelMatrix{ glm::mat4(1.0f) }
{
}

Transformation::~Transformation()
{
}

void Transformation::Translate(float x, float y, float z) {
    m_modelMatrix = glm::translate(m_modelMatrix, glm::vec3(x, y, z));
}

void  Transformation::Rotate(float angle, float x, float y, float z) {
    m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(angle), glm::vec3(x, y, z));
}

void  Transformation::Scale(float x, float y, float z) {
    m_modelMatrix = glm::scale(m_modelMatrix, glm::vec3(x, y, z));
}

const glm::mat4& Transformation::GetModelMatrix() const {
    return m_modelMatrix;
}
