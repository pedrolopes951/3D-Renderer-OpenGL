#include "ShapeRenderer.h"






ShapeRenderer::ShapeRenderer(GLFWwindow* window, std::vector<std::unique_ptr<IModel>>& models, const glm::mat4& orthomatrix) : m_window{window}, m_models_available{models}
{
    this->InitTransformationMatrices();
}

ShapeRenderer::~ShapeRenderer()
{
}

void ShapeRenderer::Render()
{
    // Render the models and apply transformations
 /*   for (auto& i : m_models_available)
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
}

void ShapeRenderer::RenderShape()
{

}

void ShapeRenderer::RenderImGuiWindow()
{
    ImGui::Begin("Shape Selection and Operations");

    ImGui::Text("Select a shape to render:");

    const char* shapes[] = { "Triangle", "Square","Circle" };
    ImGui::Combo("Selected Shape", &m_selected_shape, shapes, IM_ARRAYSIZE(shapes));

    ImGui::SliderFloat("Rotation Angle", &m_rotationAngle, 0.f, 360.f);

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
