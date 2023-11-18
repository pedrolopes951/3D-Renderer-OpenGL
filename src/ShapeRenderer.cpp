#include "ShapeRenderer.h"






ShapeRenderer::ShapeRenderer(GLFWwindow* window, std::map<ModelShapes, std::shared_ptr<IModel>>& models, const glm::mat4& orthomatrix) : m_window{window}, m_models_available{models}
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

    // Apply transformation and render the selected model
    switch (m_selected_shape)
    {
    case ModelShapes::TRIANGLE:
        m_models_available[ModelShapes::TRIANGLE]->ApplyTransformation(m_transformation_matrices[ModelShapes::TRIANGLE]);
        m_models_available[ModelShapes::TRIANGLE]->Render();
        break;
    case ModelShapes::SQUARE:
        m_models_available[ModelShapes::SQUARE]->ApplyTransformation(m_transformation_matrices[ModelShapes::SQUARE]);
        m_models_available[ModelShapes::SQUARE]->Render();
        break;
    case ModelShapes::CIRCLE:
        m_models_available[ModelShapes::CIRCLE]->ApplyTransformation(m_transformation_matrices[ModelShapes::CIRCLE]);
        m_models_available[ModelShapes::CIRCLE]->Render();
        break;
    default:
        std::cerr << "Not available model for rendering" << std::endl;
        throw("Not available model for rendering");
        break;
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}


void ShapeRenderer::RenderImGuiWindow()
{
    ImGui::Begin("Shape Selection and Operations");

    ImGui::Text("Select a shape to render:");

    const char* shapes[] = { "Triangle", "Square","Circle" };
    ImGui::Combo("Selected Shape", &m_selected_shape, shapes, IM_ARRAYSIZE(shapes));

    // Add which axis to rotate from
    ImGui::SliderFloat("Rotation AngleX", &m_rotationAngle.x, 0.f, 360.f);
    ImGui::SliderFloat("Rotation AngleY", &m_rotationAngle.y, 0.f, 360.f);
    ImGui::SliderFloat("Rotation AngleZ", &m_rotationAngle.z, 0.f, 360.f);


    // Which axis to translate the offset
    ImGui::SliderFloat("Translation OffsetX", (float*)&m_translation.x, 0.0f, 960.0f);
    ImGui::SliderFloat("Translation OffsetY", (float*)&m_translation.y, 0.0f, 540.0f);
    ImGui::SliderFloat("Translation OffsetZ", (float*)&m_translation.z, 0.0f, 0.0f);

    // Which Coordinate to scale it
    ImGui::SliderFloat("Scales X", (float*)&m_scaling.x, 1.0f, 3.0f);
    ImGui::SliderFloat("Scales Y", (float*)&m_scaling.y, 1.0f, 3.0f);
    ImGui::SliderFloat("Scales Z", (float*)&m_scaling.z, 1.0f, 3.0f);

    // Apply alll input to transformation matrices
    for (auto& trans : m_transformation_matrices)
    {
        trans.second.Rotate(m_rotationAngle.x, 1.0, 0.0, 0.0);
        trans.second.Rotate(m_rotationAngle.y, 0.0, 1.0, 0.0);
        trans.second.Rotate(m_rotationAngle.z, 0.0, 0.0, 1.0);

        trans.second.Scale(m_scaling.x, m_scaling.y, m_scaling.z);

        trans.second.Translate(m_translation.x, m_translation.y, m_translation.z);

    }

    ImGui::End();
}

void ShapeRenderer::InitTransformationMatrices(const glm::mat4& orthomatrix)
{
    // Add transformation matrices available
    m_transformation_matrices[ModelShapes::TRIANGLE] = Transformation();
    m_transformation_matrices[ModelShapes::SQUARE] = Transformation();
    m_transformation_matrices[ModelShapes::CIRCLE] = Transformation();

    for (auto& i : m_transformation_matrices)
    {
        i.second.Ortho(orthomatrix);
    }

       
}
