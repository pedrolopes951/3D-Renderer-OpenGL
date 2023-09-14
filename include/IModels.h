#pragma once
// Base Model Class Method

class IModel
{
public:
    IModel(){}
    virtual ~IModel() = default;
    // Render for all implementation of this models to render
    virtual void Render() = 0;
private:
};