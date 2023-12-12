#include "Transformation.h"




Transformation::Transformation() : m_modelMatrixTranslation{ glm::mat4(1.0f) }, m_modelMatrixScaling{ glm::mat4(1.0f) }, m_modelMatrixRotation{ glm::mat4(1.0f) }, m_view{glm::mat4(1.f)}, m_projectionOrtho{glm::ortho(0.0f, WINDOWWIDTH, 0.0f, WINDOWHEIGHT)}, m_projectionPerspective{glm::perspective(glm::radians(45.0f), WINDOWWIDTH/WINDOWHEIGHT,0.1f,100.f)}, m_indentyMatrix{glm::mat4(1.0f)}
{
}

Transformation::~Transformation()
{
}

void Transformation::Translate(float x, float y, float z) {
    m_modelMatrixTranslation = glm::translate(m_indentyMatrix, glm::vec3(x, y, z)) ;
}

void  Transformation::Rotate(float angle, float x, float y, float z) {

    m_modelMatrixRotation =  glm::rotate(m_indentyMatrix, glm::radians(angle), glm::vec3(x, y, z));
}

void  Transformation::Scale(float x, float y, float z) {
    m_modelMatrixScaling =  glm::scale(m_indentyMatrix, glm::vec3(x, y, z));
}

void Transformation::Ortho(float left, float right, float bottom, float top, float near , float far)
{
    m_projectionOrtho = glm::ortho(left, right, bottom, top,near,far);

}

void Transformation::Perspective(float fov, float aspectRatio, float near, float far)
{
    m_projectionPerspective = glm::perspective(fov, aspectRatio, near, far);
}

void Transformation::View(float x, float y, float z)
{
    m_view = glm::translate(m_indentyMatrix, glm::vec3(x, y, z));
}

const glm::mat4& Transformation::GetModelMatrix2D() const {
    return m_projectionOrtho *m_modelMatrixTranslation * m_modelMatrixRotation* m_modelMatrixScaling;
}

const glm::mat4& Transformation::GetModelMatrix3D() const {
    return m_projectionPerspective * m_view * m_modelMatrixTranslation * m_modelMatrixRotation * m_modelMatrixScaling;
}
