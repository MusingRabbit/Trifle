#include "Game.h"

#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include <iostream>
#include <GLGameWindow.h>
#include <Systems/Systems.h>
#include <chrono>

/// @brief Constructor
Game::Game()
{
}

/// @brief Destructor
Game::~Game()
{
}

/// @brief Starts main program loop
/// @return Error code. 0 indicates no Error
int Game::Run()
{
    std::cout << "Game.Run()" << std::endl;

    int initResult = glfwInit();

    if (initResult == GL_FALSE)
    {
        std::cout << "GLFW initialisation failed" << std::endl;
        return -1;
    }

    std::cout << "GLFW initialisation complete" << std::endl;
    std::cout << "Creating game window" << std::endl;

    m_gameWindow = std::make_unique<GLGameWindow>(800, 600, "Trifle");
    m_gameWindow->MakeCurrentContext();

    std::cout << "Initialising ECS" << std::endl;
    m_enttySvc = std::make_unique<EntityService>();
    m_enttySvc->Init();

    std::cout << "Registering Components" << std::endl;

    std::cout << "Registering Systems" << std::endl;

    std::shared_ptr<VoxelRenderSystem> vRender = m_enttySvc->RegisterSystem<VoxelRenderSystem>();
    vRender->SetGameWindow(m_gameWindow.get());
    vRender->Init();

    std::cout << "Starting main loop" << std::endl;

    auto currTime = std::chrono::high_resolution_clock::now();

    while (!m_gameWindow->WindowShouldClose())
    {
        if (m_gameWindow->GetKeyState(GLFW_KEY_ESCAPE) == GLFW_PRESS)
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

        const auto prevTime = currTime;
        currTime = std::chrono::high_resolution_clock::now();
        const auto deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(currTime - prevTime).count();

        vRender->Update(deltaTime);
    }

    return 0;
}