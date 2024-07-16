#include "trifle.h"

#include "GLInclude.h"

namespace tfl
{
    
Trifle::Trifle()
{
}

Trifle::~Trifle()
{
}

void Trifle::Init()
{
    std::cout << "Trifle.Init()" << std::endl;

    int initResult = glfwInit();

    if (initResult == GL_FALSE)
    {
        std::cout << "GLFW initialisation failed" << std::endl;
        return;
    }

    std::cout << "Creating game window" << std::endl;

    m_gameWindow = std::make_shared<GameWindow>(800, 600, "Trifle");

    std::function<void(EventArgs&)> resizedFunc = [this](EventArgs& e) { this->GameWindow_OnResized(e); };
    m_gameWindow->OnWindowResized.Subscribe(resizedFunc);
    m_gameWindow->SetActive(true);

    std::cout << "Initialising ECS" << std::endl;
    m_entityManager = std::make_shared<EntityManager>();
    m_entityManager->Init();

    Entity::Init(m_entityManager);

    RegisterComponents();
    RegisterSystems();
    InitSystems();

    srand(time(0));

    m_isInitialised = true;
}

int Trifle::Run()
{
    std::cout << "Trifle.Run()" << std::endl;
    std::cout << "Starting main loop" << std::endl;

    auto currTime = std::chrono::high_resolution_clock::now();

    while (m_gameWindow->IsOpen())
    {
        KeyboardState kbState = Keyboard::GetState();

        if (kbState.IsKeyDown(Keys::Escape))
        {
            std::cout << "Escape key pressed. Ending program." << std::endl;
            return 0;
        }

        GLenum errorResult = glGetError();

        if (errorResult != GL_NO_ERROR)
        {
            std::cout << "OpenGL Error : " << errorResult << ". Ending program." << std::endl;
            return errorResult;
        }

        m_gameWindow->Update();

        const auto prevTime = currTime;
        currTime = std::chrono::high_resolution_clock::now();
        const auto deltaTime = (float)std::chrono::duration_cast<std::chrono::milliseconds>(currTime - prevTime).count() / 1000;

        GameUpdateSystems(deltaTime);

        RenderSystems(deltaTime);
    }

    return 0;
}

void Trifle::RegisterComponents()
{
    m_entityManager->RegisterComponent<Collider>();
    m_entityManager->RegisterComponent<Model3D>();
    m_entityManager->RegisterComponent<Movement>();
    m_entityManager->RegisterComponent<Target>();
    m_entityManager->RegisterComponent<Projection>();
    m_entityManager->RegisterComponent<Transform>();
    m_entityManager->RegisterComponent<ColourComponent>();
}

void Trifle::RegisterSystems()
{
    m_entityManager->RegisterSystem<Renderer>({m_gameWindow, m_entityManager});
    m_entityManager->RegisterSystem<VoxelRenderer>({m_gameWindow, m_entityManager});
    m_entityManager->RegisterSystem<VoxelGridSystem>({m_gameWindow, m_entityManager});
    m_entityManager->RegisterSystem<VoxelRasteriser>({m_gameWindow, m_entityManager});
}

void Trifle::InitSystems()
{
    m_entityManager->GetSystem<Renderer>()->Init();

    std::shared_ptr<VoxelRenderer> vRenderer = m_entityManager->GetSystem<VoxelRenderer>();
    std::shared_ptr<VoxelRasteriser> vRaster = m_entityManager->GetSystem<VoxelRasteriser>();

    //vRenderer->SetImageSize(m_gameWindow->GetWidth(), m_gameWindow->GetHeight());
    
    vRaster->Init();
    vRenderer->Init();
}

void Trifle::GameUpdateSystems(float dt)
{
    System::UpdateTime(dt);

    auto systems = m_entityManager->GetSystems();

    for (auto system : systems)
    {
        system->Update(dt);
    }
}

void Trifle::RenderSystems(float dt)
{
    auto systems = m_entityManager->GetSystems();

    for (auto system : systems)
    {
        system->Draw(dt);
    }
}

void Trifle::GameWindow_OnResized(const EventArgs& e)
{
    std::shared_ptr<VoxelRenderer> vRenderer = m_entityManager->GetSystem<VoxelRenderer>();
    //vRenderer->SetImageSize(m_gameWindow->GetWidth(), m_gameWindow->GetHeight());
}

} // namespace tfl
