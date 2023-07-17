#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <GLFW/glfw3.h>
#include "Core/EventHandler.h"

namespace tfl
{
class GameWindow
{
  private:
    GLFWwindow* m_window;
    unsigned int m_width, m_height;

    void WindowFocusCallback(GLFWwindow* window, int focused);

  protected:
  public:
    EventHandler OnWindowResized;
    
    GameWindow(unsigned int width, unsigned int height, const char* title);
    virtual ~GameWindow();

    unsigned int GetWidth();
    unsigned int GetHeight();
    void SetSize(unsigned int width, unsigned int height);

    void SetActive(bool active);

    bool IsActive();

    bool HasFocus();

    //void MakeCurrentContext();
    //bool IsCurrentContext();

    void RequestFocus();

    void Update();

    void Close();
    
    bool IsOpen();
};
} // namespace tfl

#endif // !GAMEWINDOW_H