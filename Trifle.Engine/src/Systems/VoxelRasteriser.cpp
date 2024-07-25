#include "VoxelRasteriser.h"
#include "Renderer.h"
#include "../Factory/EntityBuilder.h"
#include "../Threading/ThreadPool.h"
#include <functional>

namespace tfl
{
    VoxelRasteriser::VoxelRasteriser(unsigned int id, const SystemContext& context)
        : System(id, context)
    {
    }

    VoxelRasteriser::~VoxelRasteriser()
    {
        m_threadPool.Stop();
    }

    void VoxelRasteriser::Init(unsigned int imgWidth, unsigned int imgHeight)
    {
        m_threadPool.Start();

        m_canvas.SetAdditiveBlend(false);
        SetImageSize(imgWidth, imgHeight);

        m_screenEntity = EntityBuilder::CreateTexturedQuad();
        m_screenEntity.AddSystem<Renderer>();
        Model3D& model3d = m_screenEntity.GetComponent<Model3D>();
        m_screenTexture = &model3d.GetMaterial().texture;
        m_screenTexture->SetDataByColour(m_canvas.GetWidth(), m_canvas.GetHeight(), m_canvas.GetData());
    }

    void VoxelRasteriser::SetImageSize(unsigned int width, unsigned int height)
    {
        m_imgWidth = width;
        m_imgHeight = height;

        m_canvas.Resize(m_imgWidth, m_imgHeight);
        m_canvas.ClearColour(m_clearColour);
    }

    bool VoxelRasteriser::IsDrawn(const Rectangle& rect)
    {
        return m_canvas.IsPixelSet(rect.TopLeft()) || m_canvas.IsPixelSet(rect.TopRight()) || m_canvas.IsPixelSet(rect.BottomLeft()) || m_canvas.IsPixelSet(rect.BottomRight());
    }

    void VoxelRasteriser::FillCanvas()
    {
        auto f = [this](const int zDepth, const VoxelDrawSet& voxels) { DrawVoxels(zDepth, voxels); };

        for (auto kvp : m_drawMap)
        {
            m_threadPool.QueueTask(f, kvp.first, kvp.second);
        }

        m_threadPool.Wait();

        //for (auto item : m_textItems)
        //{
        //    m_canvas.DrawString(Point2(roundf(item.screenPos.x), roundf(item.screenPos.y)), item.text, 8, item.colour);
        //}

    }

    void VoxelRasteriser::DrawVoxels(const int zDepth, const VoxelDrawSet& voxels)
    {
        for (auto value : voxels)
        {
            int x = (int)roundf(value.screenPos.x);
            int y = (int)roundf(value.screenPos.y);

            m_canvas.DrawBox({x, y}, value.scale.x, value.scale.y, value.colour, value.colour); 
        }
    }

    void VoxelRasteriser::Init()
    {
    }

    void VoxelRasteriser::Update()
    {

    }

    void VoxelRasteriser::OnEntityAdded(unsigned int entityId)
    {
    }

    void VoxelRasteriser::OnEntityRemoved(unsigned int entityId)
    {
    }

    void VoxelRasteriser::Draw()
    {
        FillCanvas();
        std::shared_ptr<Renderer> r = Context.entityManager->GetSystem<Renderer>();
        m_screenTexture->SubDataByColour(m_canvas.GetData());
        r->Update(); 
    }

    void VoxelRasteriser::DrawNow()
    {
        FillCanvas();
        std::shared_ptr<Renderer> r = Context.entityManager->GetSystem<Renderer>();
        m_screenTexture->SubDataByColour(m_canvas.GetData());
        r->Update(); 
    }

    void VoxelRasteriser::Clear()
    {
        m_canvas.ClearColour(m_clearColour);
        m_drawMap.clear();
        m_textItems.clear();
    }

    void VoxelRasteriser::AddDrawItem(const VoxelDrawItem& drawItem)
    {
        int key = (int)roundf(-drawItem.screenPos.z);

        if (m_drawMap.find(key) == m_drawMap.end())
        {
            m_drawMap.insert({ key, VoxelDrawSet() });
        }

        m_drawMap[key].push_back(drawItem);
    }

    void VoxelRasteriser::AddDrawItem(const TextDrawItem& drawItem)
    {
        m_textItems.push_back(drawItem);
    }


} // namespace tfl