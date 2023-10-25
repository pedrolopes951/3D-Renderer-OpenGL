#pragma once
#include <glm/glm.hpp>
// glm::translate, glm::rotate, glm::scale
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include <glm/gtx/string_cast.hpp>

class Transformation
{
public:
    Transformation();
    ~Transformation();
    void Translate(float x, float y, float z);

    void Rotate(float angle, float x, float y, float z);

    void Scale(float x, float y, float z);

    void Ortho(float left, float right, float bottom, float top);

    const glm::mat4& GetModelMatrix()const; 


private:
    glm::mat4 m_modelMatrix;

};


