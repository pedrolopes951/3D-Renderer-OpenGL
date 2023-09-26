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
    virtual std::unique_ptr<IModel>CreateModel(const std::vector<Vertex>& vertex, const std::vector<unsigned int>& eb, const GLType typeVertices)  = 0;

private:

};

