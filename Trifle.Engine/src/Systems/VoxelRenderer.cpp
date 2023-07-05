#include "VoxelRenderer.h"

#include "../Graphics/Graphics.h"
#include "../Factory/EntityBuilder.h"
#include "../Components/Components.h"
#include "../Systems/Renderer.h"
#include "../Data/VoxelGrid.h"

namespace trifle
{
VoxelRenderer::VoxelRenderer(EntityManager& manager) : System(manager)
{
}

VoxelRenderer::~VoxelRenderer()
{
}

void VoxelRenderer::SetImageSize(unsigned int width, unsigned int height)
{
    m_imageWidth = width;
    m_imageHeight = height;

    m_screenImage.Resize(m_imageWidth, m_imageHeight);
    m_screenImage.ClearColour(m_clearColour);
}

void VoxelRenderer::Init()
{
    m_screenImage.ClearColour(m_clearColour);

    m_screenEntity = EntityBuilder::CreateTexturedQuad();
    m_screenEntity.AddSystem<Renderer>();

    Model3D& model3d = m_screenEntity.GetComponent<Model3D>();

    m_screenTexture = &model3d.GetMaterial().texture;

    m_screenTexture->SetDataByColour(m_screenImage.GetWidth(), m_screenImage.GetHeight(), m_screenImage.GetData());

    srand(time(0));
}

void VoxelRenderer::Update(float dt)
{
    m_totalElapsedTime += dt;

    if ((int)(round(10 * (int)m_totalElapsedTime) / 10) % 10 == 0)
    {
        DoCommadore64LoadingScreen();
    }

    m_screenTexture->SubDataByColour(m_screenImage.GetData());
}

void VoxelRenderer::RenderVoxelGrid(const VoxelGrid<VoxelGridCell>& grid)
{
}

void VoxelRenderer::DoCommadore64LoadingScreen()
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
} // namespace trifle
