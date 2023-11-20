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
    Transformation(const Transformation& other) { m_modelMatrix = other.m_modelMatrix; m_indentyMatrix = other.m_indentyMatrix; m_projection = other.m_projection; };
    ~Transformation();
    void Translate(float x, float y, float z);

    void Rotate(float angle, float x, float y, float z);

    void Scale(float x, float y, float z);

    // This will multiply to place the model between the boundaries of the orthographic matrix so in a algebric perpective is just putting this in a normalized field
    void Ortho(float left, float right, float bottom, float top);

    void Ortho(const glm::mat4& orthmatrix);

    const glm::mat4& GetModelMatrix()const; 


private:
    glm::mat4 m_modelMatrix;
    glm::mat4 m_indentyMatrix;
    glm::mat4 m_projection;

};


