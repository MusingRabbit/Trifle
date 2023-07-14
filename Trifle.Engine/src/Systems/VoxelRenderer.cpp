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

void VoxelRenderer::ForceDraw()
{
    std::shared_ptr < Renderer> r = GetEntityManager().GetSystem<Renderer>();
    UpdateScreenTexture();
    r->Update(0.0f); 
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





    Transform& camTrans = camera.GetComponent<Transform>();
    glm::vec3 camPos = camTrans.GetPosition();

    Target& camTarget = camera.GetComponent<Target>();

    Projection& proj = camera.GetComponent<Projection>();
    glm::mat4 mtxView = camera.GetViewMatrix();
    glm::mat4 mtxViewInv = glm::inverse(mtxView); // The cameras' view matrix. Translates from World position to view, and vice versa.
    glm::mat4 mtxProj = proj.GetMatrix();
    glm::mat4 mtxProjInv = glm::inverse(proj.GetMatrix());

    unsigned int zFar = (unsigned int)proj.GetFarPlane() - 1;
    unsigned int zNear = (unsigned int)proj.GetNearPlane();

    Colour stroke = Colour(1, 1, 1, 1);
    int itint = 5;

    unsigned int zDepth = zFar - zNear;

    for (unsigned int i = zFar; i >= zNear; i--) // Itterate through the depth frustrum, back to front.
    {
        unsigned int zCurr = i;
        unsigned int width = (zCurr * 1);                                // Width is equal to zCurr. As zCurr decreases, so does the screen width
        unsigned int height = (zCurr * 1);     // Height is equal to the zCurr times the projections' aspect ratio.
        unsigned int zRemaining = zCurr - zNear;

        float xScale = (m_screenImage.GetWidth() / 2) / ((float)zRemaining + 1);
        float yScale = (m_screenImage.GetHeight() / 2) / ((float)zRemaining + 1);
        int iHeightCount = height * 2 - 1;
        int iWidthCount = width * 2 - 1;
        float alpha = 1.0 - ((float)zRemaining / (float)zDepth);
        stroke.a = alpha;

        //DEBUG CODE FOR COLOURING BLOCKS

        //if (itint == 0)
        //{
        //    stroke.b += 0.05f;

        //    if (stroke.b > 0.2f)
        //    {
        //        itint = 1;
        //    }
        //}
        //else if (itint == 1)
        //{
        //    stroke.g += 0.05f;
        //    stroke.b -= 0.05f;

        //    if (stroke.g > 0.2f)
        //    {
        //        itint = 2;
        //    }
        //}
        //else if (itint == 2)
        //{
        //    stroke.r += 0.05f;
        //    stroke.g -= 0.05f;

        //    if (stroke.r > 0.2f)
        //    {
        //        itint = 1;
        //    }
        //}

        for (int y = 0; y < iHeightCount; y++)
        {
            for (int x = 0; x < iWidthCount; x++)
            {
                float fX = (float)x - (width);
                float fY = (float)y - (height);
                float fZ = (float)zCurr;

                glm::vec4 fPos = glm::vec4(fX, fY, fZ, 1.0f); // View Position
                glm::vec4 wPos = mtxViewInv * fPos;           // World position

                UIntPoint3 gridPoint{(unsigned int)wPos.x, (unsigned int)wPos.y, (unsigned int)wPos.z};

                //if (wPos.x != camTarget.position.x || wPos.y != camTarget.position.y)
                //{
                //    continue;
                //}

                if (grid.Contains(gridPoint))
                {
                    VoxelGridCell* cell = grid.GetCell(gridPoint);

                    glm::vec4 sPos;
                    sPos.x = roundf(((fPos.x + (float)width) * xScale) - (xScale / 2));
                    sPos.y = roundf(((fPos.y + (float)height) * yScale) - (yScale / 2));

                    UIntPoint2 screenPos{(unsigned int)sPos.x, (unsigned int)sPos.y};

                    m_screenImage.DrawBox(screenPos, xScale, yScale, cell->GetColour(), stroke);

                    //ForceDraw(); // FOR DEBUGING ONLY - REMOVE 
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
