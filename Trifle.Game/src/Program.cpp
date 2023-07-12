#include "Program.h"

#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include <iostream>
#include <chrono>

#include "Systems/Game.h"

/// @brief Constructor
Program::Program()
{
}

/// @brief Destructor
Program::~Program()
{
}

void Program::Init()
{
    std::cout << "Program.Init()" << std::endl;

    int initResult = glfwInit();

    if (initResult == GL_FALSE)
    {
        std::cout << "GLFW initialisation failed" << std::endl;
        return;
    }

    std::cout << "GLFW initialisation complete" << std::endl;
    std::cout << "Creating game window" << std::endl;

    m_gameWindow = std::make_shared<GLGameWindow>(800, 600, "Trifle");
    m_gameWindow->MakeCurrentContext();

    std::cout << "Initialising ECS" << std::endl;
    m_entityManager = std::make_shared<EntityManager>();
    m_entityManager->Init();

    Entity::Init(m_entityManager);

    RegisterComponents();
    RegisterSystems();

    InitSystems();
}

/// @brief Starts main program loop
/// @return Error code. 0 indicates no Error
int Program::Run()
{
    std::cout << "Program.Run()" << std::endl;
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

        GameUpdateSystems(deltaTime);

        // std::cout << "Frametime : " << deltaTime << "ms" << std::endl;
    }

    return 0;
}

void Program::RegisterComponents()
{
    m_entityManager->RegisterComponent<Collider>();
    m_entityManager->RegisterComponent<Model3D>();
    m_entityManager->RegisterComponent<Movement>();
    m_entityManager->RegisterComponent<Target>();
    m_entityManager->RegisterComponent<Projection>();
    m_entityManager->RegisterComponent<Transform>();
}

void Program::RegisterSystems()
{
    m_entityManager->RegisterSystem<Renderer>();
    m_entityManager->RegisterSystem<VoxelRenderer>();
    m_entityManager->RegisterSystem<VoxelGridSystem>();
    m_entityManager->RegisterSystem<Game>();
}

void Program::InitSystems()
{
    m_entityManager->GetSystem<Renderer>()->Init();

    std::shared_ptr<VoxelRenderer> vRenderer = m_entityManager->GetSystem<VoxelRenderer>();
    vRenderer->SetImageSize(m_gameWindow->GetScreenWidth(), m_gameWindow->GetScreenHeight());

    m_entityManager->GetSystem<VoxelRenderer>()->Init();
    m_entityManager->GetSystem<Game>()->Init(m_gameWindow);
}

void Program::GameUpdateSystems(float dt)
{
    m_entityManager->GetSystem<VoxelGridSystem>()->Update(dt);
    m_entityManager->GetSystem<VoxelRenderer>()->Update(dt);
    m_entityManager->GetSystem<Renderer>()->Update(dt);

    m_entityManager->GetSystem<Game>()->Update(dt);
}