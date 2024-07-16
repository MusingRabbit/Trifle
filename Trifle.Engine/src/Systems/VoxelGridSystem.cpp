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

void VoxelGridSystem::Update(float dt)
{
    auto entityIds = GetEntityIds();

    for (unsigned int id : entityIds)
    {
        VoxelEntity e;
        e.SetId(id);
        
        m_grid.PaintCells(e.GetPoint(), e.GetSize(), e.GetColour());

        //Transform& transform = e.GetComponent<Transform>();
        //VoxelBlock& voxelBlock = e.GetComponent<VoxelBlock>();
        //glm::vec3 pos = transform.GetPosition();
        //UIntPoint3 point{(unsigned int)pos.x, (unsigned int)pos.y, (unsigned int)pos.z};
        //m_grid.PaintCells(point, voxelBlock.size, voxelBlock.colour);

        //m_renderer->RenderVoxelGrid(m_grid, RenderMethod::RENDER_DEBUG);
    }

    //m_grid.Clear();

    //while (!m_drawQueue.empty())
    //{
    //    VoxelDrawArgs& args = m_drawQueue.front();
    //    m_grid.PaintCells(args.pos, args.brushSize, args.colour);

    //    m_drawQueue.pop();
    //}

    m_renderer->ProcessVoxelGrid(m_grid, RenderMethod::RENDER_DEBUG);
}



} // namespace tfl
