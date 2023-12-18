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




class ShapeRenderer
{
public:
    ShapeRenderer(GLFWwindow* window, std::map<ModelShapes, std::shared_ptr<IModel>>& models);
    ~ShapeRenderer();
    void Render();


private:

    enum Render
    {
        TWOD,
        THREED
    };
    void Render3D();
    void Render2D();

    void RenderImGuiWindow();

    void InitTransformationMatrices();


    int m_selected_shape = 0;
    int m_render_option = 0;
    glm::vec3 m_rotationAngle = { 0.f ,0.f,0.f};
    glm::vec3 m_translation{0.f,0.f,0.f};
    glm::vec3 m_scaling{ 1.f,1.f,0.f };
    glm::vec4 m_color{ 1.0f };

    
    GLFWwindow* m_window;
    std::map<ModelShapes, std::shared_ptr<IModel>>& m_models_available;
    std::map<ModelShapes,Transformation> m_transformation_matrices;

};
