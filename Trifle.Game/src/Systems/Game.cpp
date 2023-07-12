#include "Game.h"

#include <glm/glm.hpp>
#include <string>

Game::Game(EntityManager& manager) : System(manager)
{
}

Game::~Game()
{
}

void Game::Init(std::shared_ptr<GLGameWindow> gameWindow)
{
    m_gameWindow = gameWindow;
    float aspectRatio = m_gameWindow->GetScreenWidth() / m_gameWindow->GetScreenHeight();

    m_camera.Register();
    m_camera.Init(aspectRatio, 1.0f, 10.0f);
    m_camera.SetPosition(glm::vec3(5, 5, 0));
    m_camera.SetTarget(glm::vec3(5, 5, 5));

    GetEntityManager().GetSystem<VoxelRenderer>()->SetActiveCamera(m_camera.GetId());

    m_voxelGrid = GetEntityManager().GetSystem<VoxelGridSystem>();
    m_voxelGrid->Init(UIntPoint3{10, 10, 10});
}

void Game::Init()
{
    throw std::runtime_error("Not implemented.");
}

void Game::Update(float dt)
{
    // std::cout << "Game.Update() -> FRAMETIME : " << dt << "ms" << std::endl;

    m_voxelGrid->DrawVoxel({5, 5, 5}, Colour(1, 0, 1, 1));

    if (m_gameWindow->GetKeyState(GLFW_KEY_W) == GLFW_PRESS)
    {
        m_camera.Move(glm::vec3(0, -0.1, 0));
        OutputCameraPosition();
    }

    if (m_gameWindow->GetKeyState(GLFW_KEY_S) == GLFW_PRESS)
    {
        m_camera.Move(glm::vec3(0, 0.1, 0));
        OutputCameraPosition();
    }

    if (m_gameWindow->GetKeyState(GLFW_KEY_A) == GLFW_PRESS)
    {
        m_camera.Move(glm::vec3(-0.1, 0, 0));
        OutputCameraPosition();
    }

    if (m_gameWindow->GetKeyState(GLFW_KEY_D) == GLFW_PRESS)
    {
        m_camera.Move(glm::vec3(0.1, 0, 0));
        OutputCameraPosition();
    }
}

void Game::OutputCameraPosition()
{
    Transform& camTrans = m_camera.GetComponent<Transform>();
    glm::vec3 pos = camTrans.GetPosition();

    std::string msg;
    msg.append("Camera Pos : [");
    msg.append(pos.x);
    msg.append(pos.y);
    msg.append(pos.z);

    std::cout << msg.c_str() << std::endl;
}
