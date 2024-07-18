#ifndef VOXELGRIDSYSTEM_H
#define VOXELGRIDSYSTEM_H

#include <memory.h>
#include <queue>

#include "../Data/VoxelGrid.h"
#include "../Core/Core.h"
#include "../Components/Components.h"
#include "../Entities/VoxelEntity.h"
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

  protected:
    void OnEntityAdded(unsigned int entityId) override;
    void OnEntityRemoved(unsigned int entityId) override;

  public:
    VoxelGridSystem(unsigned int id, const SystemContext& context);
    ~VoxelGridSystem();


    void Init(const UIntPoint3& gridScale);
    void Init() override;
    void Update() override;

    

    //void DrawVoxels(const UIntPoint3& position, unsigned int brushSize, const Colour& fillColour);
    //void DrawVoxel(const UIntPoint3& position, const Colour& colour);
    void Clear();
};
} // namespace tfl

#endif