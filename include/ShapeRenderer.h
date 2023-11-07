#pragma once
#include <IModels.h>
// Include GLEW
#include <GL/glew.h>
// Include GLFW
#include <GLFW/glfw3.h>
#include <vector>
#include <map>
#include <Transformation.h>

enum class ShapesAvailable
{
    TRIANGLE,
    SQUARE,
    CIRCLE
};
class ShapeRenderer
{
public:
    ShapeRenderer(GLFWwindow* window, std::vector<IModel> models);
    ~ShapeRenderer();

private:

    void InitTransformationMatrices();

    GLFWwindow* m_window;
    std::vector<IModel> m_models_available;
    std::map<ShapesAvailable,Transformation> m_transformation_matrices;

};
