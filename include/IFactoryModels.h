#pragma once
#include <memory>
#include "Vertex.h"

class IModel;

class IModelFactory
{
public:
    IModelFactory(){};
    virtual ~IModelFactory()= default;
    virtual std::unique_ptr<IModel> CreateModel(const Vertex* vertex, const GLType typeVertices, const int countVertices) = 0;

private:

};

