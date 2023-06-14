#include "GameWindow.h"

#include <iostream>
#include "GLFW/glfw3.h"

namespace trifle
{
    GameWindow::GameWindow(int width, int height, const char *title)
    {
        m_monitor = glfwGetPrimaryMonitor();

        const GLFWvidmode *mode = glfwGetVideoMode(m_monitor);

        glfwWindowHint(GLFW_RED_BITS, mode->redBits);
        glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
        glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
        glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
        glfwWindowHint(GLFW_DOUBLEBUFFER, GL_FALSE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_window = glfwCreateWindow(mode->width, mode->height, title, NULL, NULL);
    }

    GameWindow::~GameWindow()
    {
        Close();
    }

    void GameWindow::MakeCurrentContext()
    {
        glfwMakeContextCurrent(m_window);
    }

    bool GameWindow::IsCurrentContext()
    {
        return glfwGetCurrentContext() == m_window;
    }

    GLFWwindow *GameWindow::GetGLFWwindow()
    {
        return m_window;
    }

    void GameWindow::Close()
    {
        if (m_window != nullptr)
        {
            glfwDestroyWindow(m_window);

            m_monitor = nullptr;
            m_window = nullptr;
        }
    }
}