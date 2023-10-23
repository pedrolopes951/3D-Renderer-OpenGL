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
    void Translate(float x, float y, float z) {
        m_modelMatrix = glm::translate(m_modelMatrix, glm::vec3(x, y, z));
    }

    void Rotate(float angle, float x, float y, float z) {
        m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(angle), glm::vec3(x, y, z));
    }

    void Scale(float x, float y, float z) {
        m_modelMatrix = glm::scale(m_modelMatrix, glm::vec3(x, y, z));
    }

    const glm::mat4& GetModelMatrix() const {
        return m_modelMatrix;
    }


private:
    glm::mat4 m_modelMatrix;

};


