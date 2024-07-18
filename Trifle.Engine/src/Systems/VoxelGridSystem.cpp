#include "VoxelGridSystem.h"


namespace tfl
{
VoxelGridSystem::VoxelGridSystem(unsigned int id, const SystemContext& context) : System(id, context)
{
}

VoxelGridSystem::~VoxelGridSystem()
{
}

void VoxelGridSystem::Init()
{
    m_renderer = Context.entityManager->GetSystem<VoxelRenderer>();
    m_grid.Init(255, 255, 255);
}

void VoxelGridSystem::Init(const UIntPoint3& gridScale)
{
    m_renderer = Context.entityManager->GetSystem<VoxelRenderer>();
    m_grid.Init(gridScale.x, gridScale.y, gridScale.z);
}

void VoxelGridSystem::OnEntityAdded(unsigned int entityId)
{
    VoxelEntity e;
    e.SetId(entityId);

    m_grid.PaintCells(e.GetPoint(), e.GetSize(), e.GetColour());
}

void VoxelGridSystem::OnEntityRemoved(unsigned int entityId)
{
    VoxelEntity e;
    e.SetId(entityId);
    Colour c = e.GetColour();

    m_grid.PaintCells(e.GetPoint(), e.GetSize(), {-c.r, -c.g, -c.b, -c.a});
}

void VoxelGridSystem::Clear()
{
    m_grid.Clear();
}

void VoxelGridSystem::Update()
{
    ThreadPool::GetInstance()->QueueTask([this] 
    {
        auto entityIds = GetEntityIds();

        for (unsigned int id : entityIds)
        {
            VoxelEntity e;
            e.SetId(id);
            
            m_grid.PaintCells(e.GetPoint(), e.GetSize(), e.GetColour());
        }
    }
    );


    m_renderer->ProcessVoxelGrid(m_grid, RenderMethod::RENDER_DEBUG);
}



} // namespace tfl
