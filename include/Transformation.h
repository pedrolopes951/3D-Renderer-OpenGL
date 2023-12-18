#pragma once
#include <glm/glm.hpp>
// glm::translate, glm::rotate, glm::scale
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>


#include <glm/gtx/string_cast.hpp>
#include "Constants.h"
#include <unordered_map>


class Transformation
{
public:
    Transformation();
    Transformation(const Transformation& other) { m_modelMatrixTranslation = other.m_modelMatrixTranslation; m_modelMatrixScaling = other.m_modelMatrixScaling; m_modelMatrixRotation = other.m_modelMatrixRotation; m_indentyMatrix = other.m_indentyMatrix; m_projectionOrtho = other.m_projectionOrtho; m_projectionPerspective = other.m_projectionPerspective; m_view = other.m_view; };
    ~Transformation();

    void Translate(float x, float y, float z);

    void Rotate(float angle, float x, float y, float z, AxisRotation axis);

    void Scale(float x, float y, float z);

    // This will multiply to place the model between the boundaries of the orthographic matrix so in a algebric perpective is just putting this in a normalized field
    void Ortho(float left, float right, float bottom, float top, float near = -1.0f, float far = 1.0f);

    void Perspective(float fov, float aspectRatio, float near = 0.1f, float far = 100.0f);

    void View(float x, float y, float z);

    void setColor(const glm::vec4& color) { m_color = color; };
    void SetCameraViewMatrix(const glm::mat4& view_matrix) { m_view = view_matrix; };

    const glm::vec4& getColor() const { return m_color; };

    const glm::mat4& GetModelMatrix2D() const; 
    const glm::mat4& GetModelMatrix3D() const;


private:
    glm::vec4 m_color;
    glm::mat4 m_modelMatrixTranslation;
    glm::mat4 m_modelMatrixScaling;
    glm::mat4 m_modelMatrixRotation;
    mutable glm::mat4 m_result{1.0f};
    glm::mat4 m_indentyMatrix;
    glm::mat4 m_projectionOrtho;
    glm::mat4 m_view;
    glm::mat4 m_projectionPerspective;
    static std::unordered_map<AxisRotation, float> m_lastAngles;



};


