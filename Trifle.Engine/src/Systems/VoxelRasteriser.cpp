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

    bool VoxelRasteriser::IsDrawn(const BoundingBox& box)
    {
        glm::vec3 min = box.min;
        glm::vec3 max = box.max;
        glm::vec3 centre = box.GetCentre();

        bool minSet = m_canvas.IsPixelSet({(int)roundf(min.x), (int)roundf(min.y)});
        bool maxSet = m_canvas.IsPixelSet({(int)roundf(max.x), (int)roundf(max.y)});
        bool centreSet = m_canvas.IsPixelSet({(int)roundf(centre.x), (int)roundf(centre.y)});

        return minSet && maxSet && centreSet;
    }

    void VoxelRasteriser::FillCanvas()
    {
        m_debugStopwatch.Start();
        auto f = [this](const int zDepth, const VoxelDrawSet& voxels) { DrawVoxels(zDepth, voxels); };

        for (auto kvp : m_drawMap)
        {
            m_threadPool.QueueTask(f, kvp.first, kvp.second);
        }

        m_threadPool.Wait();
        m_debugStopwatch.Stop();
        std::cout << "VoxelRasteriser.FillCanvas() took " << m_debugStopwatch.GetMilliseconds() << "ms." << std::endl;
    }

    void VoxelRasteriser::DrawVoxels(const int zDepth, const VoxelDrawSet& voxels)
    {
        for (auto value : voxels)
        {
            if (!IsDrawn(value.box))
            {
                m_canvas.DrawBox(value.box, value.colour, value.colour); 
            }
        }
    }

    void VoxelRasteriser::Init()
    {
        m_canvas.SetOverwriteExisting(false);
        //m_treeNodes.clear();
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
        //m_drawTree.Init(m_treeNodes);
        FillCanvas();
        std::shared_ptr<Renderer> r = Context.entityManager->GetSystem<Renderer>();
        m_screenTexture->SubDataByColour(m_canvas.GetData());
        r->Update(); 
        //m_drawTree.Clear();
    }

    void VoxelRasteriser::DrawNow()
    {
        //m_drawTree.Init(m_treeNodes);
        FillCanvas();
        std::shared_ptr<Renderer> r = Context.entityManager->GetSystem<Renderer>();
        m_screenTexture->SubDataByColour(m_canvas.GetData());
        r->Update(); 
        //m_drawTree.Clear();
    }

    void VoxelRasteriser::Clear()
    {
        m_canvas.ClearColour(m_clearColour);
        m_drawMap.clear();
        m_textItems.clear();
        //m_drawTree.Clear();
    }

    void VoxelRasteriser::AddDrawItem(const VoxelDrawItem& drawItem)
    {
        int key = (int)roundf(drawItem.box.min.z);

        if (m_drawMap.find(key) == m_drawMap.end())
        {
            m_drawMap.insert({ key, VoxelDrawSet() });
        }

        m_drawMap[key].push_back(drawItem);


        //KDNode node;
        //node.data = drawItem;
        //node.pos = {drawItem.box.min.x, drawItem.box.min.y, drawItem.box.min.z};
        //m_treeNodes.push_back(node);
    }

    void VoxelRasteriser::AddDrawItem(const TextDrawItem& drawItem)
    {
        m_textItems.push_back(drawItem);
    }


} // namespace tfl