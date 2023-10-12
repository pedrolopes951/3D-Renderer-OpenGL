#pragma once
#include "IModels.h"
#include "ElementBuffer.h"
#include "Vertex.h"

// Base Model Class Method


class Triangle : public IModel
{
public:
    Triangle(const std::vector<Vertex2D>& vertex, const std::vector<unsigned int>& eb, const GLType typeVertices);
    ~Triangle();
    void Render() override; // When using glDrawElements we're going to draw using indices provided in the element buffer object currently bound
private:
    VertexArray<Vertex2D> m_va;
    VertexBuffer<Vertex2D> m_vb;
    VertexBufferLayout m_layout;
    ElementBuffer m_eb;

    unsigned int m_countvertices;

};

class Square : public IModel
{
public:
    Square(const std::vector<Vertex2D>& vertex, const std::vector<unsigned int>& eb, const GLType typeVertices);
    ~Square();
    void Render() override;


private:
    VertexArray<Vertex2D> m_va;
    VertexBuffer<Vertex2D> m_vb;
    VertexBufferLayout m_layout;
    ElementBuffer m_eb;
    unsigned int m_countvertices;


};

class Circle : public IModel
{
public:
    Circle(const std::vector<Vertex2D>& vertex, const std::vector<unsigned int>& eb ,const GLType typeVertices) ;
    ~Circle();
    void Render() override;

private:
    VertexArray<Vertex2D> m_va;
    VertexBuffer<Vertex2D> m_vb;
    VertexBufferLayout m_layout;
    ElementBuffer m_eb;

    unsigned int m_countvertices;


};


