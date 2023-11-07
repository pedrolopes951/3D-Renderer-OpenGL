#include "ShapeRenderer.h"



ShapeRenderer::ShapeRenderer(GLFWwindow* window, std::vector<IModel> models) : m_window{window}, m_models_available{models}
{
    this->InitTransformationMatrices();
}

ShapeRenderer::~ShapeRenderer()
{
}

void ShapeRenderer::InitTransformationMatrices()
{
    // Add transformation matrices available
    m_transformation_matrices[ShapesAvailable::TRIANGLE] = Transformation();
    m_transformation_matrices[ShapesAvailable::SQUARE] = Transformation();
    m_transformation_matrices[ShapesAvailable::CIRCLE] = Transformation();

}
