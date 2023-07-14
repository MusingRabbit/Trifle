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
    float aspectRatio = (float)m_gameWindow->GetScreenWidth() / (float)m_gameWindow->GetScreenHeight();

    m_camera.Register();
    m_camera.Init(aspectRatio, 1.0f, 30);
    m_camera.SetPosition(glm::vec3(15, 15, 0));
    m_camera.SetTarget(glm::vec3(15, 15, 8));

    m_camera.GetComponent<Movement>().speed = 1.0f;

    GetEntityManager().GetSystem<VoxelRenderer>()->SetActiveCamera(m_camera.GetId());

    m_voxelGrid = GetEntityManager().GetSystem<VoxelGridSystem>();
    m_voxelGrid->Init(UIntPoint3{343, 343, 343});

    m_voxelGrid->DrawVoxel({15, 15, 6}, Colour(1, 0, 1, 1));
}

void Game::Init()
{
    throw std::runtime_error("Not implemented.");
}

void Game::Update(float dt)
{
    bool moved = false;
    std::cout << "Game.Update() -> FRAMETIME : " << dt << "ms" << std::endl;

    m_voxelGrid->DrawVoxel({5, 5, 5}, Colour(1, 0, 1, 1));

    glm::vec3 moveVector(1,0,0);

    if (m_gameWindow->GetKeyState(GLFW_KEY_UP) == GLFW_PRESS)
    {
        moveVector.y += 1;
    }

    if (m_gameWindow->GetKeyState(GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        moveVector.y -= 1;
    }

    if (m_gameWindow->GetKeyState(GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        moveVector.x -= 1;
    }

    if (m_gameWindow->GetKeyState(GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        moveVector.x += 1;
    }

    if (abs(moveVector.x) + abs(moveVector.y) + abs(moveVector.z > 0))
    {
        m_camera.SetMovementSpeed(1.5 * dt);
        m_camera.ClearTarget();
        m_camera.Move(moveVector);
        OutputCameraPosition();
    }
}

void Game::OutputCameraPosition()
{
    Transform& camTrans = m_camera.GetComponent<Transform>();
    glm::vec3 pos = camTrans.GetPosition();

    std::string msg;
    msg.append("Camera Pos : [");
    msg.append("x : " +  std::to_string(pos.x));
    msg.append(",");
    msg.append("y : " + std::to_string(pos.y));
    msg.append(",");
    msg.append("z : " + std::to_string(pos.z));
    msg.append("]");

    std::cout << msg.c_str() << std::endl;
}
