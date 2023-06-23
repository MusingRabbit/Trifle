#include "VoxelRenderSystem.h"
#include "../Data/ShapeBuilder.h"

#include <stdexcept>

namespace trifle
{
VoxelRenderSystem::VoxelRenderSystem()
{
}

VoxelRenderSystem::~VoxelRenderSystem()
{
}

void VoxelRenderSystem::SetGameWindow(GLGameWindow* gameWindow)
{
    m_gameWindow = gameWindow;
}

void VoxelRenderSystem::Init()
{
    if (m_gameWindow == nullptr)
    {
        throw std::runtime_error(
            "VoxelRenderSystem :: Game window not set. Set game window by calling SetGameWindow() before initialisation.");
    }

    unsigned int initResult = glewInit();

    if (initResult != GLEW_OK)
    {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(initResult));
        throw std::runtime_error("VoxelRenderSystem :: GLEW initialisation failure.");
    }

    m_screenImage.Resize(m_gameWindow->GetScreenWidth(), m_gameWindow->GetScreenHeight());

    UIntPoint2 drawPoint{(m_gameWindow->GetScreenWidth() / 2) - 1, (m_gameWindow->GetScreenHeight() / 2) - 1};
    Colour fillColour(1.0f, 0, 0, 1.0);
    Colour strokeColour(0, 0, 0, 1.0);

    unsigned int maxX = m_screenImage.GetWidth() - 1;
    unsigned int maxY = m_screenImage.GetHeight() - 1;

    // m_screenImage.ClearColour(fillColour);
    m_screenTexture.SetDataByColour(m_screenImage.GetWidth(), m_screenImage.GetHeight(), m_screenImage.GetData());

    m_screenShader.Initialise(DefaultVs, DefaultFs);

    m_screenQuad.SetModelData(ShapeBuilder::CreateQuad());

    srand(time(0));
}

void VoxelRenderSystem::DoCommadore64LoadingScreen()
{
    unsigned int maxX = m_screenImage.GetWidth() - 1;
    unsigned int height = m_screenImage.GetHeight();
    unsigned int rowHeight = height * 0.01;
    unsigned int rows = (height / rowHeight);

    for (unsigned int i = 0; i < rows; i++)
    {
        float rR = (float)(rand()) / (float)(RAND_MAX);
        float rG = (float)(rand()) / (float)(RAND_MAX);
        float rB = (float)(rand()) / (float)(RAND_MAX);

        Colour c = Colour(rR, rG, rB, 1.0f);
        m_screenImage.DrawBox({0, rowHeight * i}, maxX, rowHeight - 1, c, c);
    }
}

void VoxelRenderSystem::Update(float dt)
{
    System::Update(dt);

    glClearColor(0, 0, 0, 1.0f);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    if ((int)(round(10 * (int)m_totalElapsedTime) / 10) % 10 == 0)
    {
        DoCommadore64LoadingScreen();
    }

    m_screenShader.Use();
    m_screenTexture.SubDataByColour(m_screenImage.GetData());
    m_screenQuad.Draw();

    glFlush();

    // m_gameWindow->SwapBuffers();
}
} // namespace trifle
