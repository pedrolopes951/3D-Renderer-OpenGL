#pragma once
#include <glm/glm.hpp>
// glm::translate, glm::rotate, glm::scale
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>


#include <glm/gtx/string_cast.hpp>
#include "Constants.h"

class Transformation
{
public:
    Transformation();
    Transformation(const Transformation& other) { m_modelMatrixTranslation = other.m_modelMatrixTranslation; m_modelMatrixScaling = other.m_modelMatrixScaling; m_modelMatrixRotation = other.m_modelMatrixRotation; m_indentyMatrix = other.m_indentyMatrix; m_projection = other.m_projection; };
    ~Transformation();

    void Translate(float x, float y, float z);

    void Rotate(float angle, float x, float y, float z);

    void Scale(float x, float y, float z);

    // This will multiply to place the model between the boundaries of the orthographic matrix so in a algebric perpective is just putting this in a normalized field
    void Ortho(float left, float right, float bottom, float top);


    const glm::mat4& GetModelMatrix()const; 


private:
    glm::mat4 m_modelMatrixTranslation;
    glm::mat4 m_modelMatrixScaling;
    glm::mat4 m_modelMatrixRotation;
    glm::mat4 m_indentyMatrix;
    glm::mat4 m_projection;

    float m_rotationangle{ 0.f };

};


