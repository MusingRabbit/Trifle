#include "Program.h"

#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include <iostream>
#include "GameWindow.h"
#include "Graphics/Renderer.h"

/// @brief Constructor
Program::Program()
{
    m_renderer = new Renderer();
}

/// @brief Destructor
Program::~Program()
{
    delete m_renderer;
    delete m_gameWindow;    
}

/// @brief Starts main program loop
/// @return Error code. 0 indicates no Error
int Program::Run()
{
    std::cout << "Program.Run()" << std::endl;

    int initResult = glfwInit();

    if (initResult == GL_FALSE)
    {
        std::cout << "GLFW initialisation failed" << std::endl;
        return -1;
    }

    std::cout << "GLFW initialisation complete" << std::endl;
    std::cout << "Creating game window" << std::endl;
    
    m_gameWindow = new GameWindow(800, 600, "Trifle");
    m_gameWindow->MakeCurrentContext();
    GLFWwindow* window = m_gameWindow->GetGLFWwindow();

    std::cout << "Starting main loop" << std::endl;

    while (!glfwWindowShouldClose(window))
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            std::cout << "GLFW_KEY_ESCAPE Pressed. Ending program." << std::endl;
            return 0;
        }

        GLenum errorResult = glGetError();

        if (errorResult != GL_NO_ERROR)
        {
            std::cout << "OpenGL Error : " << errorResult << ". Ending program." << std::endl;
            return errorResult;
        }

        glfwPollEvents();

        m_renderer->Clear(glm::vec3(0, 0.5f, 0));
        
        glfwSwapBuffers(window);
        glFlush();
    }

    return 0;
}