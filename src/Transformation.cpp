#include "Transformation.h"
#include <unordered_map>

Transformation::Transformation() : m_modelMatrixTranslation{ glm::mat4(1.0f) }, m_modelMatrixScaling{ glm::mat4(1.0f) }, m_modelMatrixRotation{ glm::mat4(1.0f) }, m_view{glm::mat4(1.f)}, m_projectionOrtho{glm::ortho(0.0f, WINDOWWIDTH, 0.0f, WINDOWHEIGHT)}, m_projectionPerspective{ glm::perspective(glm::radians(FOV), (float)WINDOWHEIGHT / (float)WINDOWWIDTH, 0.1f, 100.0f) }, m_indentyMatrix{glm::mat4(1.0f)}, m_color{ 1.0f, 1.0f, 1.0f, 1.0f } 
{
}

Transformation::~Transformation()
{
}

void Transformation::Translate(float x, float y, float z) {
    m_modelMatrixTranslation = glm::translate(m_indentyMatrix, glm::vec3(x, y, z)) ;
}

void  Transformation::Rotate(float angle, float x, float y, float z, AxisRotation axis)
{
    static std::unordered_map<AxisRotation, float> lastAngles;

    if (lastAngles[axis] != angle) {
        glm::mat4 rotationMatrix = glm::mat4(1.0f);

        if (axis == AxisRotation::X) {
            rotationMatrix = glm::rotate(rotationMatrix, angle, glm::vec3(1.0f, 0.0f, 0.0f));
        }
        else if (axis == AxisRotation::Y) {
            rotationMatrix = glm::rotate(rotationMatrix, angle, glm::vec3(0.0f, 1.0f, 0.0f));
        }
        else if (axis == AxisRotation::Z) {
            rotationMatrix = glm::rotate(rotationMatrix, angle, glm::vec3(0.0f, 0.0f, 1.0f));
        }

        m_modelMatrixRotation *= rotationMatrix;
        lastAngles[axis] = angle;
    }
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

    m_result = m_projectionOrtho * m_modelMatrixTranslation * m_modelMatrixRotation * m_modelMatrixScaling;
    return m_result;
}

const glm::mat4& Transformation::GetModelMatrix3D() const {
   //glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
   //glm::mat4 view = glm::mat4(1.0f);
   //glm::mat4 projection = glm::mat4(1.0f);
   //model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
   //view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
   //projection = glm::perspective(glm::radians(45.0f), (float)WINDOWHEIGHT / (float)WINDOWWIDTH, 0.1f, 100.0f);
   //return projection * view * model;
   //m_projectionPerspective = glm::perspective(glm::radians(45.0f), (float)WINDOWHEIGHT / (float)WINDOWWIDTH, 0.1f, 100.0f);
    m_result = m_projectionPerspective * m_view * m_modelMatrixRotation;
   return m_result;
}
