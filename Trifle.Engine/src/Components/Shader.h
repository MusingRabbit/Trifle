#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

namespace trifle
{
class Shader
{
  private:
    unsigned int m_program;

    unsigned int CreateShaderProgram(const char* program, GLenum type);

  public:
    Shader();
    ~Shader();

    void InitialiseFromFile(const char* vertextPath, const char* fragmentPath);
    void Initialise(const char* vertexProgram, const char* fragmentProgram);
    void Use();

    void SetBool(const char* name, bool value);
    void SetInt(const char* name, int value);
    void SetFloat(const char* name, float value);
};
} // namespace trifle

#endif // !SHADER_H