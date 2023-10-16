#include "Shader.h"

#include "GL/glew.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath) : m_sources{vertexShaderPath , fragmentShaderPath }, m_id{0}
{

}

void Shader::use()
{
}

void Shader::setBool(const std::string& name, bool value) const
{
}

void Shader::setInt(const std::string& name, int value) const
{
}

void Shader::setFloat2D(const std::string& name, float v0, float v1, float value0, float value1) const
{
}

void Shader::setFloat3D(const std::string& name, float v0, float v1, float v2, float value0, float value1, float value2) const
{
}

Shader::~Shader()
{
}

unsigned int  Shader::CompileShader(unsigned int type, const std::string& source)
{
    return false;
}

unsigned int Shader::CreateShader(const std::string& vertexSahder, const std::string& fragmentshader)
{

    return 0;
}

unsigned int Shader::GetUniformLocation(const std::string& name)
{
    return 0;
}
