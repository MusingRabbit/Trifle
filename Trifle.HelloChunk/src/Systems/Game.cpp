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
    m_gameTimer.Reset();
    m_gameTimer.Start();
    
    std::shared_ptr<CameraSystem> camSys = Context.entityManager->GetSystem<CameraSystem>();
    m_camera = camSys->CreateCamera((float)Context.gameWindow->GetWidth(), (float)Context.gameWindow->GetHeight(), 1.0f, 300);

    m_camera.SetPosition(glm::vec3(0, 0, -100));
    m_camera.SetTarget(glm::vec3(0, 0, 0));

    m_camera.GetComponent<Movement>().speed = 1.0f;

    m_gridSys = Context.entityManager->GetSystem<VoxelGridSystem>();
    Context.entityManager->GetSystem<VoxelRenderer>()->SetActiveCamera(m_camera.GetId());

    m_gridSys->Init(3, 32);
    
    std::vector<VoxelChunk*> chunks = m_gridSys->GetChunksByRange({0,0,0}, 3);

    for (int i = 0; i < chunks.size(); i++)
    {
        chunks[i]->Fill(glm::vec4 {Random::GetFloat(), Random::GetFloat(), Random::GetFloat(), 1.0f});
    }
}

void Game::Update()
{
    m_gameTimer.Tick();

    bool moved = false;
    

    glm::vec3 moveVector(0,0,0);
    glm::vec3 rotate(0,0,0);

    KeyboardState kbState = Keyboard::GetState();

    if (kbState.IsKeyDown(Keys::W))
    {
        moveVector.z += 1;
    }

    if (kbState.IsKeyDown(Keys::S))
    {
        moveVector.z -= 1;
    }

    if (kbState.IsKeyDown(Keys::A))
    {
        moveVector.x -= 1;
    }

    if (kbState.IsKeyDown(Keys::D))
    {
        moveVector.x += 1;
    }

    if (kbState.IsKeyDown(Keys::Up))
    {
        rotate.x += 0.01;
    }

    if (kbState.IsKeyDown(Keys::Down))
    {
        rotate.x -= 0.01;
    }

    if (kbState.IsKeyDown(Keys::Left))
    {
        rotate.y -= 0.01;
    }

    if (kbState.IsKeyDown(Keys::Right))
    {
        rotate.y += 0.01;
    }

    bool isMoving = abs(moveVector.x) + abs(moveVector.y) + abs(moveVector.z) > 0;
    bool isRotating = abs(rotate.x) + abs(rotate.y) + abs(rotate.z) > 0;

    m_camera.SetMovementSpeed(0.01f * (float)m_gameTimer.DeltaTime());
    m_camera.ClearTarget();

    if (isMoving)
    {
        m_camera.Move(moveVector);
       // OutputCameraPosition();
    }

    if (isRotating)
    {
        m_camera.Rotate(rotate);
       // OutputCameraTarget();
    }

    
    
    OutputFrameTime();
}

void Game::OnEntityAdded(unsigned int entityId)
{
    
}

void Game::OnEntityRemoved(unsigned int entityId)
{

}

void Game::OutputFrameTime()
{
    std::cout << "Game.Update() -> FRAMETIME : " << m_gameTimer.DeltaTime() << "ms" << std::endl;
}

void Game::OutputCameraTarget()
{
    Transform& camTrans = m_camera.GetComponent<Transform>();
    Target& camTarget = m_camera.GetComponent<Target>();
    glm::vec3 cPos = camTrans.GetPosition();
    glm::vec3 pos = camTarget.position;
    glm::vec3 rot = camTrans.GetRotaion();

    std::string msg;
    msg.append("Camera Pos : [");
    msg.append("x : " +  std::to_string(cPos.x));
    msg.append(",");
    msg.append("y : " + std::to_string(cPos.y));
    msg.append(",");
    msg.append("z : " + std::to_string(cPos.z));
    msg.append("]\n");

    msg.append("Camera Tgt : [");
    msg.append("x : " +  std::to_string(pos.x));
    msg.append(",");
    msg.append("y : " + std::to_string(pos.y));
    msg.append(",");
    msg.append("z : " + std::to_string(pos.z));
    msg.append("]\n");

    msg.append("Camera Rot : [");
    msg.append("x : " +  std::to_string(rot.x));
    msg.append(",");
    msg.append("y : " + std::to_string(rot.y));
    msg.append(",");
    msg.append("z : " + std::to_string(rot.z));
    msg.append("]\n\n");

    std::cout << msg.c_str() << std::endl;
}

void Game::OutputCameraPosition()
{
    Transform& camTrans = m_camera.GetComponent<Transform>();
    glm::vec3 pos = camTrans.GetPosition();
    glm::vec3 rot = camTrans.GetRotaion();

    std::string msg;
    msg.append("Camera Pos : [");
    msg.append("x : " +  std::to_string(pos.x));
    msg.append(",");
    msg.append("y : " + std::to_string(pos.y));
    msg.append(",");
    msg.append("z : " + std::to_string(pos.z));
    msg.append("]");

    msg.append("Camera Rot : [");
    msg.append("x : " +  std::to_string(rot.x));
    msg.append(",");
    msg.append("y : " + std::to_string(rot.y));
    msg.append(",");
    msg.append("z : " + std::to_string(rot.z));
    msg.append("]");

    std::cout << msg.c_str() << std::endl;
}
