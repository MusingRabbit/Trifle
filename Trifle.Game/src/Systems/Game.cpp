#include "Game.h"

#include <glm/glm.hpp>
#include <string>

Game::Game(unsigned int id, const SystemContext& context) : System(id, context)
{
}

Game::~Game()
{
}

void Game::Init()
{
    float aspectRatio = (float)Context.gameWindow->GetWidth() / (float)Context.gameWindow->GetHeight();

    m_camera.Register();
    m_camera.Init(aspectRatio, 1.0f, 50);
    m_camera.SetPosition(glm::vec3(15.1, 15, 0));
    m_camera.SetTarget(glm::vec3(15, 15, 6));

    m_camera.GetComponent<Movement>().speed = 1.0f;

    Context.entityManager->GetSystem<VoxelRenderer>()->SetActiveCamera(m_camera.GetId());

    m_voxelGrid = Context.entityManager->GetSystem<VoxelGridSystem>();
    m_voxelGrid->Init(UIntPoint3{343, 343, 343});

    m_voxelGrid->DrawVoxel({15, 15, 6}, Colour(1, 0, 1, 1));
}

void Game::Update(float dt)
{
    bool moved = false;
    std::cout << "Game.Update() -> FRAMETIME : " << dt * 1000 << "ms" << std::endl;

    m_voxelGrid->DrawVoxel({5, 5, 5}, Colour(1, 0, 1, 1));

    glm::vec3 moveVector(0,0,0);

    KeyboardState kbState = Keyboard::GetState();

    if (kbState.IsKeyDown(Keys::Up))
    {
        moveVector.y += 1;
    }

    if (kbState.IsKeyDown(Keys::Down))
    {
        moveVector.y -= 1;
    }

    if (kbState.IsKeyDown(Keys::Left))
    {
        moveVector.x -= 1;
    }

    if (kbState.IsKeyDown(Keys::Right))
    {
        moveVector.x += 1;
    }

    if (abs(moveVector.x) + abs(moveVector.y) + abs(moveVector.z > 0))
    {
        m_camera.SetMovementSpeed(1.5 * (float)dt);
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
