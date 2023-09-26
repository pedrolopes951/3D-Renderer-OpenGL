#pragma once
#include "IFactoryModels.h"
#include <iostream>

class TriangleFactory : public IModelFactory
{
public:
    TriangleFactory()
    {
        std::cout << "Triangle Created" <<  std::endl;
    };
    ~TriangleFactory(){};
    std::unique_ptr<IModel> CreateModel(const std::vector<Vertex>& vertex, const std::vector<unsigned int>& eb, const GLType typeVertices)  override;

private:

};
class SquareFactory : public IModelFactory
{
public:
    SquareFactory() {};
    ~SquareFactory() {};
    std::unique_ptr<IModel> CreateModel(const std::vector<Vertex>& vertex, const std::vector<unsigned int>& eb, const GLType typeVertices)  override;

private:

};
class CircleFactory : public IModelFactory
{
public:
    CircleFactory() {};
    ~CircleFactory() {};
    std::unique_ptr<IModel> CreateModel(const std::vector<Vertex>& vertex, const std::vector<unsigned int>& eb, const GLType typeVertices)  override;

private:

};
