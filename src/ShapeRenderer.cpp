#include "ShapeRenderer.h"






ShapeRenderer::ShapeRenderer(GLFWwindow* window, std::map<std::string, std::unique_ptr<IModel>>& models, const glm::mat4& orthomatrix) : m_window{window}, m_models_available{models}
{
    this->InitTransformationMatrices(orthomatrix);
    const char* glsl_version = "#version 130";
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    ImGui::StyleColorsDark();
}

ShapeRenderer::~ShapeRenderer()
{
}

void ShapeRenderer::Render()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    this->RenderImGuiWindow();

    // Render the models and apply transformations
   /* 
    for (auto& i : m_models_available)
    {
        i->ApplyTransformation();
        i->Render();
    }

    triangleModel->ApplyTransformation(transformationTriangle);
    triangleModel->Render();
    squareModel->ApplyTransformation(transformationSquare);
    squareModel->Render();
    circleModel->ApplyTransformation(transformationCircle);
    circleModel->Render();*/

    

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}


void ShapeRenderer::RenderImGuiWindow()
{
    ImGui::Begin("Shape Selection and Operations");

    ImGui::Text("Select a shape to render:");

    const char* shapes[] = { "Triangle", "Square","Circle" };
    ImGui::Combo("Selected Shape", &m_selected_shape, shapes, IM_ARRAYSIZE(shapes));

    ImGui::SliderFloat("Rotation Angle", &m_rotationAngle.x, 0.f, 360.f);
    // Add which axis to rotate from
    ImGui::SliderFloat2("Translation OffsetX", (float*)&m_translation.x, 0.0f, 960.0f);
    ImGui::SliderFloat2("Translation OffsetY", (float*)&m_translation.y, 0.0f, 540.0f);
    ImGui::SliderFloat2("Translation OffsetZ", (float*)&m_translation.z, 0.0f, 0.0f);

    ImGui::End();
}

void ShapeRenderer::InitTransformationMatrices(const glm::mat4& orthomatrix)
{
    // Add transformation matrices available
    m_transformation_matrices[ShapesAvailable::TRIANGLE] = Transformation();
    m_transformation_matrices[ShapesAvailable::SQUARE] = Transformation();
    m_transformation_matrices[ShapesAvailable::CIRCLE] = Transformation();

    for (auto& i : m_transformation_matrices)
    {
        i.second.Ortho(orthomatrix);
    }

       
}
