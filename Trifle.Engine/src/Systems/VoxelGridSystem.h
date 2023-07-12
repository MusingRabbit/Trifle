#ifndef VOXELGRIDSYSTEM_H
#define VOXELGRIDSYSTEM_H

#include <memory.h>
#include "../Data/VoxelGrid.h"
#include "../Core/Types.h"
#include "VoxelRenderer.h"

namespace trifle
{
class VoxelGridSystem : public System
{
  private:
    std::shared_ptr<VoxelRenderer> m_renderer;
    VoxelGrid<VoxelGridCell> m_grid;

  public:
    VoxelGridSystem(EntityManager& manager);
    ~VoxelGridSystem();

    void Init() override;
    void Update(float dt) override;

    void Init(const UIntPoint3& gridScale);
    void DrawVoxels(const UIntPoint3& position, unsigned int brushSize, Colour fillColour);
    void DrawVoxel(const UIntPoint3& position, Colour colour);
};
} // namespace trifle

#endif