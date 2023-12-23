#pragma once
#include "IModels.h"
#include "ElementBuffer.h"
#include "Vertex.h"
#include "Transformation.h"
#include "Shader.h"

// Base Model Class Method


class Triangle : public IModel
{
public:
    Triangle(const std::vector<Vertex2D>& vertex, const std::vector<unsigned int>& eb, const GLType typeVertices);
    ~Triangle();
    void Render() override; // When using glDrawElements we're going to draw using indices provided in the element buffer object currently bound
    void ApplyTransformation(const Transformation& transformation)override;
private:
    VertexArray<Vertex2D> m_va;
    VertexBuffer<Vertex2D> m_vb;
    VertexBufferLayout m_layout;
    ElementBuffer m_eb;
    Shader m_shader;
    Transformation m_transformation;
};

class Square : public IModel
{
public:
    Square(const std::vector<Vertex2D>& vertex, const std::vector<unsigned int>& eb, const GLType typeVertices);
    ~Square();
    void Render() override;
    void ApplyTransformation(const Transformation& transformation)override;


private:
    VertexArray<Vertex2D> m_va;
    VertexBuffer<Vertex2D> m_vb;
    VertexBufferLayout m_layout;
    ElementBuffer m_eb;
    Shader m_shader;
    Transformation m_transformation;
    


};

class Circle : public IModel
{
public:
    Circle(const std::vector<Vertex2D>& vertex, const std::vector<unsigned int>& eb ,const GLType typeVertices) ;
    ~Circle();
    void Render() override;
    void ApplyTransformation(const Transformation& transformation)override;

private:
    VertexArray<Vertex2D> m_va;
    VertexBuffer<Vertex2D> m_vb;
    VertexBufferLayout m_layout;
    ElementBuffer m_eb;
    Shader m_shader;
    Transformation m_transformation;


};

class Piramid : public IModel
{
public:
    Piramid(const std::vector<Vertex3D>& vertex, const std::vector<unsigned int>& eb, const GLType typeVertices);
    ~Piramid();
    void Render() override;
    void ApplyTransformation(const Transformation& transformation)override;

private:
    VertexArray<Vertex3D> m_va;
    VertexBuffer<Vertex3D> m_vb;
    VertexBufferLayout m_layout;
    ElementBuffer m_eb;
    Shader m_shader;
    Transformation m_transformation;


};

class Cube : public IModel
{
public:
    Cube(const std::vector<Vertex3D>& vertex, const std::vector<unsigned int>& eb, const GLType typeVertices);
    ~Cube();
    void Render() override;
    void ApplyTransformation(const Transformation& transformation)override;

private:
    VertexArray<Vertex3D> m_va;
    VertexBuffer<Vertex3D> m_vb;
    VertexBufferLayout m_layout;
    ElementBuffer m_eb;
    Shader m_shader;
    Transformation m_transformation;


};

class Sphere : public IModel
{
public:
    Sphere(const std::vector<Vertex3D>& vertex, const std::vector<unsigned int>& eb, const GLType typeVertices);
    ~Sphere();
    void Render() override;
    void ApplyTransformation(const Transformation& transformation)override;

private:
    VertexArray<Vertex3D> m_va;
    VertexBuffer<Vertex3D> m_vb;
    VertexBufferLayout m_layout;
    ElementBuffer m_eb;
    Shader m_shader;
    Transformation m_transformation;


};

