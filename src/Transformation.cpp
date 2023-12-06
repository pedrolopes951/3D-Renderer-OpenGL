#include "Transformation.h"




Transformation::Transformation() : m_modelMatrixTranslation{ glm::mat4(1.0f) }, m_modelMatrixScaling{ glm::mat4(1.0f) }, m_modelMatrixRotation{ glm::mat4(1.0f) },m_projection{glm::ortho(0.0f, WINDOWWIDTH, 0.0f, WINDOWHEIGHT)}, m_indentyMatrix{glm::mat4(1.0f)}
{
}

Transformation::~Transformation()
{
}

void Transformation::Translate(float x, float y, float z) {
    m_modelMatrixTranslation = glm::translate(m_indentyMatrix, glm::vec3(x, y, z)) ;
}

void  Transformation::Rotate(float angle, float x, float y, float z) {
    // m_rotationangle += 0.5f;
    m_modelMatrixRotation =  glm::rotate(m_indentyMatrix, glm::radians(m_rotationangle), glm::vec3(x, 1.0f, z));
}

void  Transformation::Scale(float x, float y, float z) {
    m_modelMatrixScaling =  glm::scale(m_indentyMatrix, glm::vec3(x, y, z));
}

void Transformation::Ortho(float left, float right, float bottom, float top)
{
    // 3 D
    //m_projection = glm::perspective(glm::radians(45.0f), (float)WINDOWWIDTH / WINDOWHEIGHT, 0.1f, 100.f);

    m_projection = glm::ortho(left, right, bottom, top);

}



const glm::mat4& Transformation::GetModelMatrix() const {
    return m_projection *m_modelMatrixTranslation * m_modelMatrixRotation* m_modelMatrixScaling;
}
