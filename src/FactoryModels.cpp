#include "FactoryModels.h"
#include "Models.h"


std::unique_ptr<IModel> TriangleFactory::CreateModel(const std::vector<Vertex>& vertex, const std::vector<unsigned int>& eb, const GLType typeVertices)
{
    return std::make_unique<Triangle>(vertex,eb ,typeVertices);

}
std::unique_ptr<IModel> SquareFactory::CreateModel(const std::vector<Vertex>& vertex, const std::vector<unsigned int>& eb, const GLType typeVertices)
{
    return std::make_unique<Square>(vertex,eb,typeVertices);
}

std::unique_ptr<IModel> CircleFactory::CreateModel(const std::vector<Vertex>& vertex, const std::vector<unsigned int>& eb, const GLType typeVertices)
{
    return std::make_unique<Circle>(vertex,eb,typeVertices);
}
