#ifndef GLGAMESCREEN_H
#define GLGAMESCREEN_H

#include "GLInclude.h"

namespace trifle
{
class GLGameWindow
{
  private:
    GLFWmonitor* m_monitor;
    GLFWwindow* m_window;

    unsigned int m_width, m_height;

  protected:
  public:
    GLGameWindow(unsigned int width, unsigned int height, const char* title);
    virtual ~GLGameWindow();

    unsigned int GetScreenWidth();
    unsigned int GetScreenHeight();

    void MakeCurrentContext();
    bool IsCurrentContext();

    void Close();

    bool WindowShouldClose();

    void SwapBuffers();

    int GetKeyState(int key);
};
} // namespace trifle

#endif // !GAMEWINDOW_H