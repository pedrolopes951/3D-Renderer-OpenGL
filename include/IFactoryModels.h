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
    virtual std::unique_ptr<IModel>Create2DModel(const std::vector<Vertex2D>& vertex, const std::vector<unsigned int>& eb, const GLType typeVertices) { return std::unique_ptr<IModel>(); };
    virtual std::unique_ptr<IModel>Create3DModel(const std::vector<Vertex3D>& vertex, const std::vector<unsigned int>& eb, const GLType typeVertices) { return std::unique_ptr<IModel>(); };

private:

};

