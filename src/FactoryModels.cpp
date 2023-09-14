#include "FactoryModels.h"
#include "Models.h"


std::unique_ptr<IModel> TriangleFactory::CreateModel()
{
    return std::make_unique<Triangle>();
}

std::unique_ptr<IModel> SquareFactory::CreateModel()
{
    return std::make_unique<Square>();
}

std::unique_ptr<IModel> CircleFactory::CreateModel()
{
    return std::make_unique<Circle>();
}
