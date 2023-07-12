#include "VoxelGridSystem.h"

namespace trifle
{
VoxelGridSystem::VoxelGridSystem(EntityManager& manager) : System(manager)
{
}

VoxelGridSystem::~VoxelGridSystem()
{
}

void VoxelGridSystem::Init()
{
    m_renderer = GetEntityManager().GetSystem<VoxelRenderer>();
    m_grid.Init(10, 10, 10);
}

void VoxelGridSystem::Init(const UIntPoint3& gridScale)
{
    m_renderer = GetEntityManager().GetSystem<VoxelRenderer>();
    m_grid.Init(gridScale.x, gridScale.y, gridScale.z);
}

void VoxelGridSystem::DrawVoxels(const UIntPoint3& position, unsigned int brushSize, Colour fillColour)
{
    m_grid.PaintCells(position, brushSize, fillColour);
}

void VoxelGridSystem::DrawVoxel(const UIntPoint3& position, Colour colour)
{
    m_grid.PaintCell(position, colour);
}

void VoxelGridSystem::Update(float dt)
{
    m_renderer->RenderVoxelGrid(m_grid);
}
} // namespace trifle
