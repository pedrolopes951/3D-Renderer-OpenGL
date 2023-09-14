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
    std::unique_ptr<IModel> CreateModel() override;

private:

};
class SquareFactory : public IModelFactory
{
public:
    SquareFactory() {};
    ~SquareFactory() {};
    std::unique_ptr<IModel> CreateModel() override;

private:

};
class CircleFactory : public IModelFactory
{
public:
    CircleFactory() {};
    ~CircleFactory() {};
    std::unique_ptr<IModel> CreateModel() override;

private:

};
