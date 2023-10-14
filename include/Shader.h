#pragma once
#include <string>

class Shader
{
public:

    Shader(const char* vertexShaderPath, const char* fragmentShaderPath);

    // Activate the Shader
    void use();
    // Utility uniform Functions
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;

    ~Shader();

private:
    unsigned int m_id;


};

