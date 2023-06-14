#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "GLFW/glfw3.h"

namespace trifle
{
    class GameWindow
    {
    private:
        GLFWmonitor *m_monitor;
        GLFWwindow *m_window;

    protected:
    public:
        GameWindow(int width, int height, const char *title);
        virtual ~GameWindow();

        void MakeCurrentContext();
        bool IsCurrentContext();
        GLFWwindow *GetGLFWwindow();

        void Close();
    };
}

#endif // !GAMEWINDOW_H