#include "FactoryModels.h"
#include "Models.h"


std::unique_ptr<IModel> TriangleFactory::CreateModel(const Vertex& vertex, const unsigned int size, const GLType typeVertices, const int countVertices)
{
    return std::make_unique<Triangle>(vertex, size,typeVertices, countVertices);
}

std::unique_ptr<IModel> SquareFactory::CreateModel(const Vertex& vertex, const unsigned int size, const GLType typeVertices, const int countVertices)
{
    return std::make_unique<Square>(vertex, size,typeVertices, countVertices);
}

std::unique_ptr<IModel> CircleFactory::CreateModel(const Vertex& vertex, const unsigned int size, const GLType typeVertices, const int countVertices)
{
    return std::make_unique<Circle>(vertex, size,typeVertices, countVertices);
}
