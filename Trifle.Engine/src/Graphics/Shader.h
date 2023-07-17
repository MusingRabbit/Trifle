#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

namespace tfl
{
class Shader
{
  private:
    unsigned int m_program = -1;

    unsigned int CreateShaderProgram(const char* program, GLenum type);

  public:
    Shader();
    Shader(const Shader& rhs);
    ~Shader();

    void Initialise(const char* vertexProgram, const char* fragmentProgram);
    void Use();

    void SetBool(const char* name, bool value);
    void SetInt(const char* name, int value);
    void SetFloat(const char* name, float value);

    bool IsInitialised();
};
} // namespace tfl

#endif // !SHADER_H