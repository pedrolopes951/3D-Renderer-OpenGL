#include "Shader.h"

#include "GL/glew.h"
#include "Debug.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath) : m_sources(ParseShaders(vertexShaderPath, fragmentShaderPath)), m_id{0}
{

}

void Shader::use()
{
    GLCall(glUseProgram(m_id));
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

ShaderProgramSource Shader::ParseShaders(const std::string& vertexshaderpath, const std::string& fragmenshaderpath)
{
    // Parse from txt files the shader code
     // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        vShaderFile.open(vertexshaderpath);
        fShaderFile.open(fragmenshaderpath);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
    }

    return ShaderProgramSource{ std::string(vertexCode.c_str()),std::string(fragmentCode.c_str()) };
}


void Shader::CreateShader(const ShaderProgramSource& sources)
{
    // 2. compile shaders
    unsigned int vertex, fragment;
    const char* vShaderCode = sources.VertexSource.c_str();
    const char* fShaderCode = sources.FragmentSource.c_str();
    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    GLCall(glShaderSource(vertex, 1, &vShaderCode, NULL));
    GLCall(glCompileShader(vertex));
    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    GLCall(glShaderSource(fragment, 1, &fShaderCode, NULL));
    GLCall(glCompileShader(fragment));
    // shader Program
    m_id = glCreateProgram();
    GLCall(glAttachShader(m_id, vertex));
    GLCall(glAttachShader(m_id, fragment));
    GLCall(glLinkProgram(m_id));
    // delete the shaders as they're linked into our program now and no longer necessary
    GLCall(glDeleteShader(vertex));
    GLCall(glDeleteShader(fragment));
}

unsigned int Shader::GetUniformLocation(const std::string& name)
{
    return 0;
}

