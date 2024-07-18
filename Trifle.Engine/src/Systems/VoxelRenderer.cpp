#include "VoxelRenderer.h"

#include "../Graphics/Graphics.h"
#include "../Factory/EntityBuilder.h"
#include "../Components/Components.h"
#include "../Systems/Renderer.h"
#include "../Data/VoxelGrid.h"
#include "../Resources/Resources.h"
#include "../Threading/ThreadPool.h"

#include <array>
#include <format>
#include <limits>
#include <string>

namespace tfl
{
VoxelRenderer::VoxelRenderer(unsigned int id, const SystemContext& context) 
: System(id, context)
{
}

VoxelRenderer::~VoxelRenderer()
{
}

/* void VoxelRenderer::SetImageSize(unsigned int width, unsigned int height)
{
    m_imageWidth = width;
    m_imageHeight = height;

    m_canvas.Resize(m_imageWidth, m_imageHeight);
    m_canvas.ClearColour(m_clearColour);
} */

void VoxelRenderer::Init()
{
    m_raster = Context.entityManager->GetSystem<VoxelRasteriser>();
   // TextUtil::LoadFont();

    m_raster->Init(Context.gameWindow->GetWidth(), Context.gameWindow->GetHeight());

    //m_canvas.SetAdditiveBlend(true);
    //SetImageSize(Context.gameWindow->GetWidth(), Context.gameWindow->GetHeight());

    //m_screenEntity = EntityBuilder::CreateTexturedQuad();
    //m_screenEntity.AddSystem<Renderer>();

    //Model3D& model3d = m_screenEntity.GetComponent<Model3D>();
    //m_screenTexture = &model3d.GetMaterial().texture;
    //m_screenTexture->SetDataByColour(m_canvas.GetWidth(), m_canvas.GetHeight(), m_canvas.GetData());
}

void VoxelRenderer::Update()
{
/*      if ((int)(round(10 * (int)m_totalElapsedTime) / 10) % 10 == 0)
    {
         DoCommadore64LoadingScreen();
    } */

    //m_screenTexture->SubDataByColour(m_canvas.GetData());
    //m_raster->Clear();
}

void VoxelRenderer::OnEntityAdded(unsigned int entityId)
{
}

void VoxelRenderer::OnEntityRemoved(unsigned int entityId)
{
}

//void VoxelRenderer::UpdateScreenTexture()
//{
//    m_screenTexture->SubDataByColour(m_canvas.GetData());
//}

void VoxelRenderer::ProcessVoxelGrid(VoxelGrid<VoxelGridCell>& grid, RenderMethod method)
{
    switch (method)
    {
        case (RENDER_NORM):
            ProcessVoxelGrid(grid, m_camera);
            break;

        case (RENDER_DEBUG):
            ProcessVoxelGrid_Debug_BoxRender(grid, m_camera);
            break;
    }
}

void VoxelRenderer::ProcessVoxelGrid(VoxelGrid<VoxelGridCell>& grid, Camera& camera)
{
    //m_canvas.ClearColour(m_emtpyColour);
}

glm::vec4 VoxelRenderer::TransformWorldView(Camera& camera, glm::vec4 fPos)
{
    glm::mat4 mtxView = camera.GetViewMatrix();
    glm::mat4 mtxViewInv = glm::inverse(mtxView);

    return mtxViewInv * fPos; 
}

ViewData VoxelRenderer::GetViewData(Camera& camera)
{
    glm::mat4 mtxProj = camera.GetProjectionMatrix();
    glm::mat4 mtxView = camera.GetViewMatrix();
    glm::mat4 mtxViewProj = camera.GetViewMatrix() * camera.GetProjectionMatrix();

    return
    {
        mtxView,
        mtxProj,
        mtxViewProj,
        glm::inverse(mtxView),
        glm::vec4(0.0f, 0.0f, Context.gameWindow->GetWidth(), Context.gameWindow->GetHeight()),
        camera.GetNearPlane(),
        camera.GetFarPlane()
    };
}

/// @brief 
/// @param viewData 
void VoxelRenderer::CreateViewBoundingBox(const ViewData& viewData)
{
    float nearZ = viewData.zNear;
    float farZ = viewData.zFar;

    glm::vec3 bottomLeft = glm::vec3{-farZ, -farZ, 0};
    glm::vec3 topRight = glm::vec3{farZ, farZ, farZ};

    glm::vec3 lPos =  viewData.mtxView * glm::vec4(bottomLeft, 1.0f);
    glm::vec3 rPos =  viewData.mtxView * glm::vec4(topRight, 1.0f);;

    lPos.x = fmax(lPos.x, 0);
    lPos.y = fmax(lPos.y, 0);
    lPos.z = fmax(lPos.z, 0);

    rPos.x = fmax(rPos.x, 0);
    rPos.y = fmax(rPos.y, 0);
    rPos.z = fmax(rPos.z, 0);

    bool lPosSmaller = lPos.x < rPos.x && lPos.y < rPos.y;

    if (lPosSmaller)
    {
        m_viewBox.SetMax(rPos);
        m_viewBox.SetMin({ lPos.x, lPos.y, lPos.z });
    }
    else 
    {
        m_viewBox.SetMax(lPos);
        m_viewBox.SetMin({ rPos.x, rPos.y, rPos.z });
    }
}

bool VoxelRenderer::IsCellVisibleFilter(VoxelGridCell* cell)
{
    auto cellPos = cell->GetPosition();
    return m_viewBox.Contains({(float)cellPos.x,(float)cellPos.y,(float)cellPos.z});
}

bool VoxelRenderer::IsCellLitFilter(VoxelGridCell* cell)
{
    return cell->GetColour().a > 0.0f;
}

glm::vec3 GetWorldPosFromScreenPos(glm::mat4& mtxView, unsigned int x, unsigned int y, unsigned int z)
{
    glm::mat4 mtxViewInv = glm::inverse(mtxView); // The cameras' view matrix. Translates from World position to view, and vice versa.

    unsigned int width = (z * 1);       // Width is equal to zCurr. As zCurr decreases, so does the screen width
    unsigned int height = (z * 1);      // Height is equal to the zCurr times the projections' aspect ratio.
    float fX = (float)x - width;
    float fY = (float)y - height;
    float fZ = (float)z;

    glm::vec4 fPos = glm::vec4(fX, fY, fZ, 1.0f); // View Position
    glm::vec4 wPos = mtxViewInv * fPos;           // World position

    return {wPos.x, wPos.y, wPos.z};
}

void VoxelRenderer::ProcessVoxelGrid_Debug_BoxRender(VoxelGrid<VoxelGridCell>& grid, Camera& camera)
{
    Clear();

    ViewData vd = GetViewData(camera);

/*     CreateViewBoundingBox(vd);
    std::function<bool(VoxelGridCell*)> cellVisibleFilter = [this](VoxelGridCell* cell) -> bool { return this->IsCellVisibleFilter(cell); }; */

    unsigned int screenWidth = Context.gameWindow->GetWidth();
    unsigned int screenHeight = Context.gameWindow->GetHeight();
    float cMaxX = screenWidth / 100;
    float cMaxY = screenHeight / 100;

    std::vector<VoxelGridCell*> litCells = grid.GetPaintedCells();

    for (unsigned int i = 0; i < litCells.size(); i++)
    {
        VoxelGridCell* cell = litCells[i];
        Transform t = cell->GetTransform();

        glm::vec4 wPos = glm::vec4(t.GetPosition(), 1.0f);  // World position
        glm::vec4 vPos = vd.mtxView * wPos;                 // View position
        glm::vec4 cPos = VectorHelper::GetClipSpace(vPos, vd.zNear, vd.zFar, vd.viewPort.z, vd.viewPort.w);

        if (cPos.w - abs(cPos.x) < 0 || cPos.w - abs(cPos.y) < 0)
        {
            continue;
        }

        glm::vec4 nPos = VectorHelper::GetNormalisedDeviceCoords(cPos);
        glm::vec4 sPos = VectorHelper::GetScreenSpace(nPos, vd.viewPort.z, vd.viewPort.w, 0, 0);

        VoxelDrawItem drawItem;
        drawItem.screenPos = {sPos.x, sPos.y, vPos.z};
        drawItem.scale.x =  screenWidth * (float)(1.0f / roundf(abs(vPos.z)));
        drawItem.scale.y =  screenHeight * (float)(1.0f / roundf(abs(vPos.z)));
        drawItem.colour = cell->GetColour();

        // Send to the rasteriser....
        m_raster->AddDrawItem(drawItem);
    }
}

void VoxelRenderer::DrawDebugInfo(std::string strContent)
{
    //m_canvas.DrawString({0, 0}, strContent, 8);
}

void VoxelRenderer::SetActiveCamera(unsigned int entityId)
{
    m_camera.SetId(entityId);
}

//void VoxelRenderer::ForceDraw()
//{
   //std::shared_ptr<Renderer> r = Context.entityManager->GetSystem<Renderer>();
   //UpdateScreenTexture();
   //r->Update(0.0f); 
//}

void VoxelRenderer::Draw()
{
    ThreadPool::GetInstance()->QueueJob([this]{m_raster->DrawNow();});
}

void VoxelRenderer::Clear()
{
    m_raster->Clear();
    //m_canvas.ClearColour(m_emtpyColour);
}

//void VoxelRenderer::DoCommadore64LoadingScreen()
//{
/*     unsigned int maxX = m_canvas.GetWidth() - 1;
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
    } */
//}
} // namespace tfl
