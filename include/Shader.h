#pragma once
#include <string>

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;

};

class Shader
{
public:

    Shader(const char* vertexShaderPath, const char* fragmentShaderPath);

    // Activate the Shader
    void use();
    // Utility uniform Functions
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat2D(const std::string& name,float v0,float v1, float value0, float value1) const;
    void setFloat3D(const std::string& name, float v0, float v1,float v2, float value0, float value1, float value2) const;
    
    ~Shader();

private:

    static ShaderProgramSource ParseShaders(const std::string& vertexshaderpath, const std::string& fragmenshaderpath);
    void CreateShader(const ShaderProgramSource& sources);
    unsigned int GetUniformLocation(const std::string& name);

    unsigned int m_id;

    ShaderProgramSource m_sources;


};

