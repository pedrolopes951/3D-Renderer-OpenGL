#pragma once
#include <memory>

class IModel;

class IModelFactory
{
public:
    IModelFactory(){};
    virtual ~IModelFactory()= default;
    virtual std::unique_ptr<IModel> CreateModel() = 0;

private:

};

