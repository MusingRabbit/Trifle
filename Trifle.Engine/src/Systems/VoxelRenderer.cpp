#include "VoxelRenderer.h"

#include "../Graphics/Graphics.h"
#include "../Factory/EntityBuilder.h"
#include "../Components/Components.h"
#include "../Systems/Renderer.h"
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

void VoxelRenderer::Init()
{
    m_raster = Context.entityManager->GetSystem<VoxelRasteriser>();
   // TextUtil::LoadFont();

    m_raster->Init(Context.gameWindow->GetWidth(), Context.gameWindow->GetHeight());

    m_screenWidth = Context.gameWindow->GetWidth();
    m_screenHeight = Context.gameWindow->GetHeight();
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

}

void VoxelRenderer::OnEntityAdded(unsigned int entityId)
{
}

void VoxelRenderer::OnEntityRemoved(unsigned int entityId)
{
}



void VoxelRenderer::ProcessVoxelChunk(VoxelChunk& chunk, RenderMethod method)
{
    UpdateViewData(m_camera);

    switch (method)
    {
        case (RENDER_NORM):
            ProcessVoxelChunk(chunk, m_camera);         // NOT IMPLEMENTED
            break;

        case (RENDER_DEBUG):
            ProcessVoxelChunk_Debug_BoxRender(chunk, m_camera);
            break;
    }
}

void VoxelRenderer::ProcessVoxelChunk(VoxelChunk& chunk, Camera& camera)
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
        camera.GetComponent<Transform>().GetPosition(),
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
    return IsPointVisible(m_viewData, cell->GetPosition());
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

/// @brief // Check to see if any of the given points within the chunk are visible (essentially all 6 corners of the cube, and the centre point)
/// @param vd View data
/// @param chunk Chunk to be eval'd
/// @return (true/false) depending on whether chunk is visible
bool VoxelRenderer::IsChunkVisible(const ViewData& vd, VoxelChunk& chunk)
{
    return chunk.Contains({ (unsigned int)vd.viewPos.x, (unsigned int)vd.viewPos.y, (unsigned int)vd.viewPos.z }) || 
    IsPointVisible(vd, chunk.GetPosition()) || 
    IsPointVisible(vd, chunk.GetCentre())   ||
    IsPointVisible(vd, chunk.GetPosPlusX()) || 
    IsPointVisible(vd, chunk.GetPosPlusY()) || 
    IsPointVisible(vd, chunk.GetPosPlusZ()) || 
    IsPointVisible(vd, chunk.GetPosPlusSize());
}

/// @brief Check to see if the given point is visible for provided view data
/// @param vd View data
/// @param point Point to be eval'd
/// @return (true/false) depending on whether point is visible
bool VoxelRenderer::IsPointVisible(const ViewData& vd, UIntPoint3 point)
{
    glm::vec4 wPos = glm::vec4(point.x,point.y,point.z, 1.0f);                                 // World position
    glm::vec4 vPos = vd.mtxView * wPos;                                                                 // View position
    glm::vec4 cPos = VectorHelper::GetClipSpace(vPos, vd.zNear, vd.zFar, vd.viewPort.z, vd.viewPort.w); // Clip position

    return (cPos.w - abs(cPos.x) < 0 || cPos.w - abs(cPos.y) < 0) == false;
}

void VoxelRenderer::UpdateViewData(Camera& camera)
{
    m_viewData = GetViewData(camera);
}

void VoxelRenderer::ProcessVoxelChunk_Debug_BoxRender(VoxelChunk& chunk, Camera& camera)
{
    //Clear();
 
    if (!IsChunkVisible(m_viewData, chunk))
    {
        return;
    }

    VoxelGrid<VoxelGridCell>* grid = chunk.GetGrid();

/*     CreateViewBoundingBox(vd);
    std::function<bool(VoxelGridCell*)> cellVisibleFilter = [this](VoxelGridCell* cell) -> bool { return this->IsCellVisibleFilter(cell); }; */


    std::vector<VoxelGridCell*> litCells = grid->GetVisibleCells();

    for (unsigned int i = 0; i < litCells.size(); i++)
    {
        VoxelGridCell* cell = litCells[i];
        Transform t = cell->GetTransform();

        glm::vec4 wPos = glm::vec4(t.GetPosition(), 1.0f);          // World position
        glm::vec4 vPos = m_viewData.mtxView * wPos;                 // View position
        glm::vec4 cPos = VectorHelper::GetClipSpace(vPos, m_viewData.zNear, m_viewData.zFar, m_viewData.viewPort.z, m_viewData.viewPort.w);

        if (cPos.w - abs(cPos.x) < 0 || cPos.w - abs(cPos.y) < 0)
        {
            continue;
        }

        glm::vec4 nPos = VectorHelper::GetNormalisedDeviceCoords(cPos);
        glm::vec4 sPos = VectorHelper::GetScreenSpace(nPos, m_viewData.viewPort.z, m_viewData.viewPort.w, 0, 0);

        VoxelDrawItem drawItem;
        drawItem.screenPos = {sPos.x, sPos.y, vPos.z};
        drawItem.scale.x =  m_screenWidth * (float)(1.0f / roundf(abs(vPos.z)));
        drawItem.scale.y =  m_screenHeight * (float)(1.0f / roundf(abs(vPos.z)));
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

void VoxelRenderer::Draw()
{
    m_raster->Clear();
    m_raster->DrawNow();
}

void VoxelRenderer::Clear()
{
    m_raster->Clear();
}

} // namespace tfl
