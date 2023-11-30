#include "FactoryModels.h"
#include "Models.h"


std::unique_ptr<IModel> TriangleFactory::Create2DModel(const std::vector<Vertex2D>& vertex, const std::vector<unsigned int>& eb, const GLType typeVertices)
{
    return std::make_unique<Triangle>(vertex,eb ,typeVertices);

}
std::unique_ptr<IModel> SquareFactory::Create2DModel(const std::vector<Vertex2D>& vertex, const std::vector<unsigned int>& eb, const GLType typeVertices)
{
    return std::make_unique<Square>(vertex,eb,typeVertices);
}

std::unique_ptr<IModel> CircleFactory::Create2DModel(const std::vector<Vertex2D>& vertex, const std::vector<unsigned int>& eb, const GLType typeVertices)
{
    return std::make_unique<Circle>(vertex,eb,typeVertices);
}

std::unique_ptr<IModel> PiramidFactory::Create3DModel(const std::vector<Vertex3D>& vertex, const std::vector<unsigned int>& eb, const GLType typeVertices)
{
    return std::make_unique<Piramid>(vertex,eb,typeVertices);
}
