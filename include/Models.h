#pragma once
#include "IModels.h"
// Base Model Class Method


class Triangle : public IModel
{
public:
    Triangle();
    ~Triangle();
    void Render() override;
private:

};

class Square : public IModel
{
public:
    Square();
    ~Square();
    void Render() override;


private:

};

class Circle : public IModel
{
public:
    Circle();
    ~Circle();
    void Render() override;

private:

};


