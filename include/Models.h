#pragma once
#include "IModels.h"
#include "Vertex.h"
// Base Model Class Method


class Triangle : public IModel
{
public:
    Triangle(const Vertex& vertex, const unsigned int size, const GLType typeVertices, const int countVertices);
    ~Triangle();
    void Render() override;
private:
    VertexArray m_va;
    VertexBuffer m_vb;
    VertexBufferLayout m_layout;
    int m_countvertices;

};

class Square : public IModel
{
public:
    Square(const Vertex& vertex, const unsigned int size, const GLType typeVertices, const int countVertices);
    ~Square();
    void Render() override;


private:
    VertexArray m_va;
    VertexBuffer m_vb;
    VertexBufferLayout m_layout;
    int m_countvertices;


};

class Circle : public IModel
{
public:
    Circle(const Vertex& vertex, const unsigned int size, const GLType typeVertices, const int countVertices);
    ~Circle();
    void Render() override;

private:
    VertexArray m_va;
    VertexBuffer m_vb;
    VertexBufferLayout m_layout;

};


