#ifndef VOXELRENDERSYSTEM_H
#define VOXELRENDERSYSTEM_H

#include "../Core/System.h"
#include "../GLGameWindow.h"
#include "../Components/Components.h"

namespace trifle
{
class VoxelRenderSystem : public System
{
  private:
    const char* DefaultVs = "#version 330 core\n"
                            "layout(location = 0) in vec3 aPos;\n"
                            "layout(location = 1) in vec3 aTint;\n"
                            "layout(location = 3) in vec2 aTextCoord;\n"
                            "out vec2 textCoord;\n"
                            "out vec4 vertexTint;\n"

                            "void main()\n"
                            "{\n"
                            "gl_Position = vec4(aPos, 1.0);\n"
                            "textCoord = vec2(aTextCoord.x, aTextCoord.y);\n"
                            "vertexTint = vec4(aTint, 1.0);\n"
                            "}";

    const char* DefaultFs = "#version 330 core\n"
                            "out vec4 FragColor;\n"
                            "in vec2 textCoord;\n"
                            "in vec4 vertexTint;\n"
                            "uniform sampler2D texture1;\n"
                            "void main()\n"
                            "{\n"
                            "//FragColor = vec4(1.0f,1.0f,1.0f,1.0f);\n"
                            "FragColor = texture(texture1, textCoord);\n"
                            "}";
    Shader m_screenShader;
    Texture2D m_screenTexture;
    Model m_screenQuad;

    Image m_screenImage;

    GLGameWindow* m_gameWindow;

    unsigned int m_vertexArrayObj;

    void DoCommadore64LoadingScreen();

  public:
    VoxelRenderSystem();

    ~VoxelRenderSystem();

    void SetGameWindow(GLGameWindow* gameWindow);

    void Init() override;

    void Update(float dt) override;
};
} // namespace trifle

#endif // !VOXELRENDERSYSTEM_H
