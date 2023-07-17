#ifndef SHADERUTIL_H
#define SHADERUTIL_H

namespace tfl
{
class ShaderUtil
{
  public:
    static constexpr const char* DefaultVs = "#version 330 core\n"
                                             "layout(location = 0) in vec3 aPos;\n"
                                             "layout(location = 1) in vec3 aTint;\n"
                                             "out vec4 vertexTint;\n"

                                             "void main()\n"
                                             "{\n"
                                             "gl_Position = vec4(aPos, 1.0);\n"
                                             "vertexTint = vec4(aTint, 1.0);\n"
                                             "}";

    static constexpr const char* DefaultFs = "#version 330 core\n"
                                             "in vec4 vertexTint;\n"
                                             "out vec4 FragColor;\n"
                                             "void main()\n"
                                             "{\n"
                                             "FragColor = vertexTint;\n"
                                             "}";

    static constexpr const char* BasicTextureVs = "#version 330 core\n"
                                                  "layout(location = 0) in vec3 aPos;\n"
                                                  "layout(location = 3) in vec2 aTextCoord;\n"
                                                  "out vec2 textCoord;\n"

                                                  "void main()\n"
                                                  "{\n"
                                                  "gl_Position = vec4(aPos, 1.0);\n"
                                                  "textCoord = vec2(aTextCoord.x, aTextCoord.y);\n"
                                                  "}";

    static constexpr const char* BasicTextureFs = "#version 330 core\n"
                                                  "in vec2 textCoord;\n"
                                                  "uniform sampler2D texture1;\n"
                                                  "out vec4 FragColor;\n"
                                                  "void main()\n"
                                                  "{\n"
                                                  "FragColor = texture(texture1, textCoord);\n"
                                                  "}";
};
} // namespace tfl

#endif // !SHADERUTIL_H
