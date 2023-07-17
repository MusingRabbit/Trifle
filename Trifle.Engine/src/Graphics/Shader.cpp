#include "Shader.h"

#include <GL/glew.h>
#include <iostream>
#include <stdexcept>

namespace tfl
{
unsigned int Shader::CreateShaderProgram(const char* program, GLenum type)
{
    int success;

    unsigned int result = glCreateShader(type);
    glShaderSource(result, 1, &program, NULL);
    glCompileShader(result);
    glGetShaderiv(result, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(result, 512, NULL, infoLog);
        std::cout << "ERROR! Shader compilation failure : " << infoLog << std::endl;
    }

    return result;
}

Shader::Shader()
{
}

Shader::Shader(const Shader& rhs)
{
    m_program = rhs.m_program;
}

Shader::~Shader()
{
}

void Shader::Initialise(const char* vertexProgram, const char* fragmentProgram)
{
    unsigned int vertex = CreateShaderProgram(vertexProgram, GL_VERTEX_SHADER);
    unsigned int fragment = CreateShaderProgram(fragmentProgram, GL_FRAGMENT_SHADER);

    m_program = glCreateProgram();
    glAttachShader(m_program, vertex);
    glAttachShader(m_program, fragment);
    glLinkProgram(m_program);

    int linkSuccess;
    glGetProgramiv(m_program, GL_LINK_STATUS, &linkSuccess);

    if (!linkSuccess)
    {
        char infoLog[512];
        glGetShaderInfoLog(m_program, 512, NULL, infoLog);
        std::cout << "ERROR! Shader Linking failed." << infoLog << std::endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::Use()
{
    glUseProgram(m_program);
}

void Shader::SetBool(const char* name, bool value)
{
    SetInt(name, (int)value);
}

void Shader::SetInt(const char* name, int value)
{
    glUniform1i(glGetUniformLocation(m_program, name), value);
}

void Shader::SetFloat(const char* name, float value)
{
    glUniform1f(glGetUniformLocation(m_program, name), value);
}
bool Shader::IsInitialised()
{
    return m_program != -1;
}
} // namespace tfl
