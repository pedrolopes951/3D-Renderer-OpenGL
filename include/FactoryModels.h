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
    std::unique_ptr<IModel> CreateModel(const Vertex& vertex,const unsigned int size ,const GLType typeVertices, const int countVertices) override;

private:

};
class SquareFactory : public IModelFactory
{
public:
    SquareFactory() {};
    ~SquareFactory() {};
    std::unique_ptr<IModel> CreateModel(const Vertex& vertex,  const unsigned int size, const GLType typeVertices, const int countVertices) override;

private:

};
class CircleFactory : public IModelFactory
{
public:
    CircleFactory() {};
    ~CircleFactory() {};
    std::unique_ptr<IModel> CreateModel(const Vertex& vertex,  const unsigned int size , const GLType typeVertices, const int countVertices) override;

private:

};
