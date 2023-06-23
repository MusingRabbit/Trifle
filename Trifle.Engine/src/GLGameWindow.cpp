#include "GLGameWindow.h"

#include "GLFW/glfw3.h"
#include <iostream>

namespace trifle
{
GLGameWindow::GLGameWindow(unsigned int width, unsigned int height, const char* title)
{
    m_monitor = glfwGetPrimaryMonitor();

    const GLFWvidmode* mode = glfwGetVideoMode(m_monitor);

    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
    glfwWindowHint(GLFW_DOUBLEBUFFER, GL_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_width = width;
    m_height = height;

    m_window = glfwCreateWindow(m_width, m_height, title, NULL, NULL);
}

GLGameWindow::~GLGameWindow()
{
    Close();
}

unsigned int GLGameWindow::GetScreenWidth()
{
    return m_width;
}

unsigned int GLGameWindow::GetScreenHeight()
{
    return m_height;
}

void GLGameWindow::MakeCurrentContext()
{
    glfwMakeContextCurrent(m_window);
}

bool GLGameWindow::IsCurrentContext()
{
    return glfwGetCurrentContext() == m_window;
}

void GLGameWindow::Close()
{
    if (m_window != nullptr)
    {
        glfwDestroyWindow(m_window);

        m_monitor = nullptr;
        m_window = nullptr;
    }
}

bool GLGameWindow::WindowShouldClose()
{
    return glfwWindowShouldClose(m_window) > 0;
}

void GLGameWindow::SwapBuffers()
{
    return glfwSwapBuffers(m_window);
}

int GLGameWindow::GetKeyState(int key)
{
    return glfwGetKey(this->m_window, key);
}

} // namespace trifle