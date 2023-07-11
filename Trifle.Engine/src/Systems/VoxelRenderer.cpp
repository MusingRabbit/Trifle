#include "VoxelRenderer.h"

#include "../Graphics/Graphics.h"
#include "../Factory/EntityBuilder.h"
#include "../Components/Components.h"
#include "../Systems/Renderer.h"
#include "../Data/VoxelGrid.h"

#include <array>
#include <limits>

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
    m_screenImage.SetAdditiveBlend(true);

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

    // if ((int)(round(10 * (int)m_totalElapsedTime) / 10) % 10 == 0)
    //{
    //     DoCommadore64LoadingScreen();
    // }

    m_screenTexture->SubDataByColour(m_screenImage.GetData());
}

void VoxelRenderer::UpdateScreenTexture()
{
    m_screenTexture->SubDataByColour(m_screenImage.GetData());
}

void VoxelRenderer::RenderVoxelGrid(VoxelGrid<VoxelGridCell>& grid)
{
    RenderVoxelGrid(grid, m_camera);
}

void VoxelRenderer::SetActiveCamera(unsigned int entityId)
{
    m_camera.SetId(entityId);
}

void VoxelRenderer::RenderVoxelGrid(VoxelGrid<VoxelGridCell>& grid, Camera& camera)
{
    m_screenImage.ClearColour(m_emtpyColour);

    // Colour stroke{1.0, 1.0, 1.0, 1.0};
    // Colour red{1.0f, 0.0f, 0.0f, 1.0f};
    // Colour green{0.0f, 1.0f, 0.0f, 1.0f};
    // Colour blue{0.0f, 0.0f, 1.0f, 1.0f};
    // Colour white{1.0f, 1.0f, 1.0f, 1.0f};

    // m_screenImage.DrawBox({0, 0}, 100, 100, red, stroke);
    // m_screenImage.DrawBox({0, m_screenImage.GetHeight() - 101}, 100, 100, green, stroke);
    // m_screenImage.DrawBox({m_screenImage.GetWidth() - 101, 0}, 100, 100, blue, stroke);
    // m_screenImage.DrawBox({m_screenImage.GetWidth() - 101, m_screenImage.GetHeight() - 101}, 100, 100, white, stroke);

    // return;

    // TODO : DEBUGGING ONLY
    // std::shared_ptr<Renderer> r = GetEntityManager().GetSystem<Renderer>();

    Projection& proj = camera.GetComponent<Projection>();
    glm::mat4 mtxView = camera.GetViewMatrix(); // The cameras' view matrix. Translates from World position to view, and vice versa.

    unsigned int zFar = (unsigned int)proj.GetFarPlane() - 1;
    unsigned int zNear = (unsigned int)proj.GetNearPlane();

    for (unsigned int i = zFar; i >= zNear; i--) // Itterate through the depth frustrum, back to front.
    {
        unsigned int zCurr = i;
        unsigned int width = zCurr * 1;                            // Width is equal to zCurr. As zCurr decreases, so does the screen width
        unsigned int height = zCurr * (1 / proj.GetAspectRatio()); // Height is equal to the zCurr times the projections' aspect ratio.

        for (unsigned int x = 0; x < width; x++)
        {
            for (unsigned int y = 0; y < height; y++)
            {
                float fX = (float)x;
                float fY = (float)y;
                float fZ = (float)zCurr;

                glm::vec3 fPos = glm::vec3(fX, fY, fZ); // Frustum Position

                glm::vec4 wPos = glm::inverse(mtxView) * glm::vec4(fPos.x, fPos.y, fPos.z, 1.0f); // World position

                if (wPos.x < 0 || wPos.y < 0 || wPos.z < 0)
                {
                    continue;
                }

                UIntPoint3 currPoint{(unsigned int)wPos.x, (unsigned int)wPos.y, (unsigned int)wPos.z};

                if (grid.Contains(currPoint))
                {
                    unsigned int scaleX = 50; // m_screenImage.GetWidth() / width;
                    unsigned int scaleY = 50; // m_screenImage.GetHeight() / height;

                    VoxelGridCell* cell = grid.GetCell(currPoint);

                    UIntPoint2 screenPos{(unsigned int)fPos.x * scaleX, (unsigned int)fPos.y * scaleY};
                    m_screenImage.DrawBox(screenPos, scaleX, scaleY, cell->GetColour(), Colour{1.0f, 1.0f, 1.0f, 1.0f});

                    // UpdateScreenTexture();
                    // r->Update(0.0f); // TODO : DELETE ME
                }
                else
                {
                    // m_screenImage.SetPixel({screenX, screenY}, Colour(1, 1, 1, 0));
                }
            }
        }
    }
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
