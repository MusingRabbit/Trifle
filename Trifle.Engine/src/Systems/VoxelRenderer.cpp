#include "VoxelRenderer.h"

#include "../Graphics/Graphics.h"
#include "../Factory/EntityBuilder.h"
#include "../Components/Components.h"
#include "../Systems/Renderer.h"
#include "../Data/VoxelGrid.h"
#include "../Resources/Resources.h"

#include <array>
#include <format>
#include <limits>
#include <string>

namespace tfl
{
VoxelRenderer::VoxelRenderer(unsigned int id, const SystemContext& context) : System(id, context)
{
}

VoxelRenderer::~VoxelRenderer()
{
}

void VoxelRenderer::SetImageSize(unsigned int width, unsigned int height)
{
    m_imageWidth = width;
    m_imageHeight = height;

    m_canvas.Resize(m_imageWidth, m_imageHeight);
    m_canvas.ClearColour(m_clearColour);
}

void VoxelRenderer::Init()
{
   // TextUtil::LoadFont();

    
    m_canvas.SetAdditiveBlend(true);
    SetImageSize(Context.gameWindow->GetWidth(), Context.gameWindow->GetHeight());

    m_screenEntity = EntityBuilder::CreateTexturedQuad();
    m_screenEntity.AddSystem<Renderer>();

    Model3D& model3d = m_screenEntity.GetComponent<Model3D>();

    m_screenTexture = &model3d.GetMaterial().texture;

    m_screenTexture->SetDataByColour(m_canvas.GetWidth(), m_canvas.GetHeight(), m_canvas.GetData());
}

void VoxelRenderer::Update(float dt)
{
    // if ((int)(round(10 * (int)m_totalElapsedTime) / 10) % 10 == 0)
    //{
    //     DoCommadore64LoadingScreen();
    // }

    m_screenTexture->SubDataByColour(m_canvas.GetData());
}

void VoxelRenderer::UpdateScreenTexture()
{
    m_screenTexture->SubDataByColour(m_canvas.GetData());
}

void VoxelRenderer::RenderVoxelGrid(VoxelGrid<VoxelGridCell>& grid, RenderMethod method)
{
    switch (method)
    {
    case (RENDER_NORM):
        RenderVoxelGrid(grid, m_camera);
        break;

    case (RENDER_DEBUG):
        RenderVoxelGrid_Debug(grid, m_camera);
        break;
    }
}

void VoxelRenderer::RenderVoxelGrid(VoxelGrid<VoxelGridCell>& grid, Camera& camera)
{
    m_canvas.ClearColour(m_emtpyColour);


}

glm::vec4 VoxelRenderer::TransformWorldView(Camera& camera, glm::vec4 fPos)
{
    glm::mat4 mtxView = camera.GetViewMatrix();
    glm::mat4 mtxViewInv = glm::inverse(mtxView);

    return mtxViewInv * fPos; 
}

void VoxelRenderer::RenderVoxelGrid_Debug(VoxelGrid<VoxelGridCell>& grid, Camera& camera)
{
    m_canvas.ClearColour(m_emtpyColour);

    // Colour stroke{1.0, 1.0, 1.0, 1.0};
    // Colour red{1.0f, 0.0f, 0.0f, 1.0f};
    // Colour green{0.0f, 1.0f, 0.0f, 1.0f};
    // Colour blue{0.0f, 0.0f, 1.0f, 1.0f};
    // Colour white{1.0f, 1.0f, 1.0f, 1.0f};

    // m_canvas.DrawBox({0, 0}, 100, 100, red, stroke);
    // m_canvas.DrawBox({0, m_canvas.GetHeight() - 101}, 100, 100, green, stroke);
    // m_canvas.DrawBox({m_canvas.GetWidth() - 101, 0}, 100, 100, blue, stroke);
    // m_canvas.DrawBox({m_canvas.GetWidth() - 101, m_canvas.GetHeight() - 101}, 100, 100, white, stroke);

    // return;

    Transform& camTrans = camera.GetComponent<Transform>();
    glm::vec3 camPos = camTrans.GetPosition();

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
        //m_canvas.ClearColour(m_emtpyColour);
        
        unsigned int zCurr = i;
        unsigned int width = (zCurr * 1);                                // Width is equal to zCurr. As zCurr decreases, so does the screen width
        unsigned int height = (zCurr * 1);     // Height is equal to the zCurr times the projections' aspect ratio.
        float xOffset = (float)width / 2;
        float yOffset = (float)height / 2;

       //float xScale = (m_canvas.GetWidth()) / ((float)zCurr); 
       //float yScale = (m_canvas.GetHeight()) / ((float)zCurr);
        float alpha = 1.0f; // 1.0 - ((float)i / (float)zDepth);
        stroke.a = alpha;

        float xScale = (m_canvas.GetWidth() / (float)zCurr);
        float yScale = (m_canvas.GetHeight() / (float)zCurr);
        float zScale = 100;

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
        //Clear(); // Test Only - Remove
        for (int y = 0; y < height * 2; y++)
        {
            for (int x = 0; x < width * 2; x++)
            {
                float fX = (float)x - width;
                float fY = (float)y - height;
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

                    glm::vec4 sPos = fPos;
                    sPos.x = (sPos.x + (xOffset)) * xScale;
                    sPos.y = (sPos.y + (yOffset)) * yScale;
                    sPos.z = fPos.z;

                    Point2 screenPos{(int)sPos.x, (int)sPos.y};

                    //m_canvas.DrawBox(screenPos, xScale, yScale, cell->GetColour(), stroke);
                    
                    //ForceDraw(); // FOR DEBUGING ONLY - REMOVE 

                    float multiplier = 6;
                    float r = grid.GetWidth() / (wPos.x * multiplier);
                    float b = (wPos.x * multiplier) / grid.GetWidth();
                    float g = (1.0 / r) - b;

                    Colour cellColour = cell->GetColour();

                    if (roundf(wPos.x) == 15.0f && roundf(wPos.y) == 15.0f)
                    {
                        cellColour = {1,0,0,1};
                    }
                    
                    m_canvas.DrawBox(screenPos, xScale, yScale, cellColour, {r,g,b,1.0f});
                    
                    if (false && zCurr < 8)
                    {
                        unsigned int fontSize = 3 + (8 - zCurr);
                        std::string strPos = std::format("[x:{0},y:{1}z:{2}]", gridPoint.x, gridPoint.y, gridPoint.z);
                        m_canvas.DrawString({screenPos.x + 5, screenPos.y + 5}, strPos, fontSize);
                    }
                }
            }
        }

        //ForceDraw(); // FOR DEBUGING ONLY - REMOVE 
    }
}

void VoxelRenderer::SetActiveCamera(unsigned int entityId)
{
    m_camera.SetId(entityId);
}

void VoxelRenderer::ForceDraw()
{
    std::shared_ptr < Renderer> r = Context.entityManager->GetSystem<Renderer>();
    UpdateScreenTexture();
    r->Update(0.0f); 
}

void VoxelRenderer::Clear()
{
    m_canvas.ClearColour(m_emtpyColour);
}


void VoxelRenderer::DoCommadore64LoadingScreen()
{
    unsigned int maxX = m_canvas.GetWidth() - 1;
    unsigned int height = m_canvas.GetHeight();
    unsigned int rowHeight = height * 0.01;
    unsigned int rows = (height / rowHeight);

    for (int i = 0; i < rows; i++)
    {
        float rR = (float)(rand()) / (float)(RAND_MAX);
        float rG = (float)(rand()) / (float)(RAND_MAX);
        float rB = (float)(rand()) / (float)(RAND_MAX);

        Colour c = Colour(rR, rG, rB, 1.0f);
        m_canvas.DrawBox({0, (int)rowHeight * i}, maxX, rowHeight - 1, c, c);
    }
}
} // namespace tfl
