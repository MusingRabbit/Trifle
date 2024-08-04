#include "VoxelGridSystem.h"


namespace tfl
{
    VoxelGridSystem::VoxelGridSystem(unsigned int id, const SystemContext& context) : System(id, context)
    {
    }

    VoxelGridSystem::~VoxelGridSystem()
    {
        //m_threadPool.Stop();
    }

    void VoxelGridSystem::Init()
    {
        //m_threadPool.Start();
        m_renderer = Context.entityManager->GetSystem<VoxelRenderer>();
        m_grid.Init(1, 16);
    }

    /// @brief Initialises the voxel grid system
    /// @param chunkCount The number of chunks the voxel grid will contain
    /// @param voxelCount The number of voxels each chunk will contain.
    void VoxelGridSystem::Init(unsigned int chunkCount, unsigned int voxelCount)
    {
        //m_threadPool.Start();
        m_renderer = Context.entityManager->GetSystem<VoxelRenderer>();
        m_grid.Init(chunkCount, voxelCount);
    }

    std::vector<VoxelChunk*> VoxelGridSystem::GetChunksByRange(const Point3 position, unsigned int size)
    {
        return m_grid.GetAllChunksByRange(position, size);
    }

    void VoxelGridSystem::FillChunk(const Point3& position, glm::vec4 colour)
    {
        m_grid.GetChunk(position)->Fill(colour);
    }

    void VoxelGridSystem::OnEntityAdded(unsigned int entityId)
    {
        VoxelEntity e;
        e.SetId(entityId);

        Point3 pos = e.GetPoint();

        UIntPoint3 localPos = GetLocalPoisition(pos);

        m_grid.GetChunk(pos)->GetGrid()->PaintCells(localPos, e.GetSize(), e.GetColour());
    }

    void VoxelGridSystem::OnEntityRemoved(unsigned int entityId)
    {
        VoxelEntity e;
        e.SetId(entityId);
        Colour c = e.GetColour();

        Point3 pos = e.GetPoint();
        UIntPoint3 localPos = GetLocalPoisition(pos);

        m_grid.GetChunk(pos)->GetGrid()->PaintCells(localPos, e.GetSize(),{-c.r, -c.g, -c.b, -c.a});
    }

    void VoxelGridSystem::Clear()
    {
        m_grid.Clear();
    }

    UIntPoint3 VoxelGridSystem::GetLocalPoisition(const Point3& globalPosition)
    {
        VoxelChunk* chunk = m_grid.GetChunk(globalPosition);
        UIntPoint3 cPos =  chunk->GetLocalPosition();
        cPos =  (cPos).multiply(chunk->GetSize());
        Point3 gPos = globalPosition - Point3(cPos.x, cPos.y, cPos.z);
        UIntPoint3 localPos = Convert::ToUIntPoint3(gPos);
        return localPos;
    }

    void VoxelGridSystem::Update()
    {
        auto f = [this]() { UpdateEntities(); };
        m_threadPool.QueueTask(f);
    }

    void VoxelGridSystem::UpdateEntities()
    {
        auto entityIds = GetEntityIds();

        for (unsigned int id : entityIds)
        {
            VoxelEntity e;
            e.SetId(id);

            Point3 pos = e.GetPoint();
            UIntPoint3 localPos = GetLocalPoisition(pos);
            
            m_grid.GetChunk(pos)->GetGrid()->PaintCells(localPos, e.GetSize(), e.GetColour());
        }
    }

    void VoxelGridSystem::Draw()
    {
        m_renderer->ProcessVoxelChunkGrid(m_grid, 1000);
    }

} // namespace tfl
