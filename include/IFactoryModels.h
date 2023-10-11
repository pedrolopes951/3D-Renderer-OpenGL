#pragma once
#include <memory>
#include "Vertex.h"
#include <vector>
class IModel;

class IModelFactory
{
public:
    IModelFactory(){};
    virtual ~IModelFactory()= default;
    virtual std::unique_ptr<IModel>Create2DModel(const std::vector<Vertex2D>& vertex, const std::vector<unsigned int>& eb, const GLType typeVertices)  = 0;

private:

};

