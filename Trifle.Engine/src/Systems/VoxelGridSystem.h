#ifndef VOXELGRIDSYSTEM_H
#define VOXELGRIDSYSTEM_H

#include <memory.h>
#include <queue>

#include "../Data/VoxelGrid.h"
#include "../Core/Types.h"
#include "VoxelRenderer.h"

namespace tfl
{
struct VoxelDrawArgs
{
    UIntPoint3 pos;
    Colour colour;
    unsigned int brushSize;
};

class VoxelGridSystem : public System
{
  private:
    std::shared_ptr<VoxelRenderer> m_renderer;
    VoxelGrid<VoxelGridCell> m_grid;
    //std::queue<VoxelDrawArgs> m_drawQueue;

  public:
    VoxelGridSystem(unsigned int id, const SystemContext& context);
    ~VoxelGridSystem();

    void Init() override;
    void Update(float dt) override;

    void Init(const UIntPoint3& gridScale);
    void DrawVoxels(const UIntPoint3& position, unsigned int brushSize, Colour fillColour);
    void DrawVoxel(const UIntPoint3& position, Colour colour);
    void Clear();
};
} // namespace tfl

#endif