#include "FactoryModels.h"
#include "Models.h"


std::unique_ptr<IModel> TriangleFactory::CreateModel(const Vertex* vertex, const GLType typeVertices, const int countVertices)
{
    return std::make_unique<Triangle>(vertex, typeVertices, countVertices);
}

std::unique_ptr<IModel> SquareFactory::CreateModel(const Vertex* vertex, const GLType typeVertices, const int countVertices)
{
    return std::make_unique<Square>(vertex, typeVertices, countVertices);
}

std::unique_ptr<IModel> CircleFactory::CreateModel(const Vertex* vertex, const GLType typeVertices, const int countVertices)
{
    return std::make_unique<Circle>(vertex, typeVertices, countVertices);
}
