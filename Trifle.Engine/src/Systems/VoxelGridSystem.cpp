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
    m_grid.Init(10, 10, 10);
}

void VoxelGridSystem::Init(const UIntPoint3& gridScale)
{
    m_renderer = Context.entityManager->GetSystem<VoxelRenderer>();
    m_grid.Init(gridScale.x, gridScale.y, gridScale.z);
}

void VoxelGridSystem::DrawVoxels(const UIntPoint3& position, unsigned int brushSize, Colour fillColour)
{
    //m_drawQueue.push(VoxelDrawArgs{position, fillColour, brushSize});

    m_grid.PaintCells(position, brushSize, fillColour);
}

void VoxelGridSystem::DrawVoxel(const UIntPoint3& position, Colour colour)
{
    m_grid.PaintCells(position, 1, colour);
}

void VoxelGridSystem::Clear()
{
    //m_drawQueue.empty();
}

void VoxelGridSystem::Update(float dt)
{
    m_grid.Clear();

    //while (!m_drawQueue.empty())
    //{
    //    VoxelDrawArgs& args = m_drawQueue.front();
    //    m_grid.PaintCells(args.pos, args.brushSize, args.colour);

    //    m_drawQueue.pop();
    //}

    m_renderer->RenderVoxelGrid(m_grid, RenderMethod::RENDER_DEBUG);
}
} // namespace tfl
