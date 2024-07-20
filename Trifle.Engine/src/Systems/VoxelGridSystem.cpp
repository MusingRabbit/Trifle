#include "VoxelGridSystem.h"


namespace tfl
{
    VoxelGridSystem::VoxelGridSystem(unsigned int id, const SystemContext& context) : System(id, context)
    {
    }

    VoxelGridSystem::~VoxelGridSystem()
    {
        m_threadPool.Stop();
    }

    void VoxelGridSystem::Init()
    {
        m_threadPool.Start();
        m_renderer = Context.entityManager->GetSystem<VoxelRenderer>();
        m_grid.Init(1, 16);
    }

    /// @brief Initialises the voxel grid system
    /// @param chunkCount The number of chunks the voxel grid will contain
    /// @param voxelCount The number of voxels each chunk will contain.
    void VoxelGridSystem::Init(unsigned int chunkCount, unsigned int voxelCount)
    {
        m_threadPool.Start();
        m_renderer = Context.entityManager->GetSystem<VoxelRenderer>();
        m_grid.Init(chunkCount, voxelCount);
    }

    void VoxelGridSystem::FillChunk(const UIntPoint3& position, glm::vec4 colour)
    {
        m_grid.FindChunkByGlobalPos(position)->GetGrid()->Fill(colour);
    }

    void VoxelGridSystem::OnEntityAdded(unsigned int entityId)
    {
        VoxelEntity e;
        e.SetId(entityId);

        UIntPoint3 pos = e.GetPoint();
        UIntPoint3 localPos = GetLocalPoisition(pos);

        m_grid.FindChunkByGlobalPos(pos)->GetGrid()->PaintCells(localPos, e.GetSize(), e.GetColour());
    }

    void VoxelGridSystem::OnEntityRemoved(unsigned int entityId)
    {
        VoxelEntity e;
        e.SetId(entityId);
        Colour c = e.GetColour();

        UIntPoint3 pos = e.GetPoint();
        UIntPoint3 localPos = GetLocalPoisition(pos);

        m_grid.FindChunkByGlobalPos(pos)->GetGrid()->PaintCells(localPos, e.GetSize(),{-c.r, -c.g, -c.b, -c.a});
    }

    void VoxelGridSystem::Clear()
    {
        m_grid.Clear();
    }

    UIntPoint3 VoxelGridSystem::GetLocalPoisition(UIntPoint3 globalPosition)
    {
        VoxelChunk* chunk = m_grid.FindChunkByGlobalPos(globalPosition);
        UIntPoint3 cPos = chunk->GetPosition();
        UIntPoint3 localPos = globalPosition - (cPos.multiply(chunk->GetSize()));
        return localPos;
    }

    void VoxelGridSystem::Update()
    {
        auto entityIds = GetEntityIds();

        for (unsigned int id : entityIds)
        {
            VoxelEntity e;
            e.SetId(id);

            UIntPoint3 pos = e.GetPoint();
            UIntPoint3 localPos = GetLocalPoisition(pos);
            
            m_grid.FindChunkByGlobalPos(pos)->GetGrid()->PaintCells(pos, e.GetSize(), e.GetColour());
        }
    }

    void VoxelGridSystem::Draw()
    {
        std::vector<VoxelChunk*> chunks = m_grid.GetVisibleChunks();

        for (unsigned int i = 0; i < chunks.size(); i++)
        {
            m_renderer->ProcessVoxelChunk(*chunks[i], RenderMethod::RENDER_DEBUG); 
        }
    }

} // namespace tfl
