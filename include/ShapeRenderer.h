#pragma once
#include <IModels.h>
// Include GLEW
#include <GL/glew.h>
// Include GLFW
#include <GLFW/glfw3.h>
#include <vector>
#include <map>
#include <Transformation.h>
// GUI
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "Constants.h"



enum class ShapesAvailable
{
    TRIANGLE,
    SQUARE,
    CIRCLE
};
class ShapeRenderer
{
public:
    ShapeRenderer(GLFWwindow* window, std::vector<std::unique_ptr<IModel>>& models,const glm::mat4& orthomatrix);
    ~ShapeRenderer();
    void Render();


private:

    void RenderShape();
    void RenderImGuiWindow();

    void InitTransformationMatrices(const glm::mat4& orthomatrix);

    int m_selected_shape = 0;
    glm::vec4 m_rotationAngle = { 0.f ,0.f,0.f,0.f };
    glm::vec3 m_translation{0.f,0.f,0.f};

    
    GLFWwindow* m_window;
    std::vector<std::unique_ptr<IModel>>& m_models_available;
    std::map<ShapesAvailable,Transformation> m_transformation_matrices;

};
