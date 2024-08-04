#include "GameWindow.h"
#include "Input/Keyboard.h"

namespace tfl
{
GameWindow::GameWindow(unsigned int width, unsigned int height, const char* title)
{
    m_width = width;
    m_height = height;

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();

    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
    glfwWindowHint(GLFW_DOUBLEBUFFER, GL_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(m_width, m_height, title, NULL, NULL);

    glfwSetKeyCallback(m_window, Keyboard::KeyCallback);
    //glfwSetWindowFocusCallback(m_window, (GLFWwindowclosefun*)&WindowFocusCallback);
}

GameWindow::~GameWindow()
{
    Close();
}

void GameWindow::SetSize(unsigned int width, unsigned int height)
{
    m_width = width;
    m_height = height;
    glfwSetWindowSize(m_window, width, height);
}

unsigned int GameWindow::GetWidth()
{
    return m_width;
}

unsigned int GameWindow::GetHeight()
{
    return m_height;
}

void GameWindow::SetActive()
{
    glfwMakeContextCurrent(m_window);
}

bool GameWindow::IsActive()
{
    return glfwGetCurrentContext() == m_window;
}

bool GameWindow::HasFocus()
{
    return true; // TODO : Implement
}

void GameWindow::RequestFocus()
{
    glfwFocusWindow(m_window);
}

void GameWindow::Update()
{
    glfwPollEvents();
}

void GameWindow::Close()
{
    if (m_window != nullptr)
    {
        glfwDestroyWindow(m_window);

        m_window = nullptr;
    }
}

void GameWindow::WindowFocusCallback(GLFWwindow* window, int focused)
{
    if (focused)
    {
        // The window gained input focus
    }
    else
    {
        // The window lost input focus
    }
}

bool GameWindow::IsOpen()
{
    return glfwWindowShouldClose(m_window) == 0;
}

} // namespace tfl