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
    std::unique_ptr<IModel> Create2DModel(const std::vector<Vertex2D>& vertex, const std::vector<unsigned int>& eb, const GLType typeVertices)  override;
                                                          
private:                                                  
                                                          
};                                                        
class SquareFactory : public IModelFactory                
{                                                         
public:                                                   
    SquareFactory() {                                     
        std::cout << "Square Created" << std::endl;       
    };                                                    
    ~SquareFactory() {};                                  
    std::unique_ptr<IModel> Create2DModel(const std::vector<Vertex2D>& vertex, const std::vector<unsigned int>& eb, const GLType typeVertices)  override;
                                                          
private:                                                  
                                                          
};                                                        
class CircleFactory : public IModelFactory                
{                                                         
public:                                                   
    CircleFactory() {                                     
        std::cout << "Circle Created" << std::endl;       
    };                                                    
    ~CircleFactory() {};                                  
    std::unique_ptr<IModel> Create2DModel(const std::vector<Vertex2D>& vertex, const std::vector<unsigned int>& eb, const GLType typeVertices)  override;

private:

};
class PiramidFactory : public IModelFactory
{
public:
    PiramidFactory() {
        std::cout << "Circle Created" << std::endl;
    };
    ~PiramidFactory() {};
    std::unique_ptr<IModel> Create3DModel(const std::vector<Vertex3D>& vertex, const std::vector<unsigned int>& eb, const GLType typeVertices)  override;

private:

};
class CubeFactory : public IModelFactory
{
public:
    CubeFactory() {
        std::cout << "Cube Created" << std::endl;
    };
    ~CubeFactory() {};
    std::unique_ptr<IModel> Create3DModel(const std::vector<Vertex3D>& vertex, const std::vector<unsigned int>& eb, const GLType typeVertices)  override;

private:

};
class SphereFactory : public IModelFactory
{
public:
    SphereFactory() {
        std::cout << "Cube Created" << std::endl;
    };
    ~SphereFactory() {};
    std::unique_ptr<IModel> Create3DModel(const std::vector<Vertex3D>& vertex, const std::vector<unsigned int>& eb, const GLType typeVertices)  override;

private:

};
