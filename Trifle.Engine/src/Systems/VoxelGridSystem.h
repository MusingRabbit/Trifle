#ifndef VOXELGRIDSYSTEM_H
#define VOXELGRIDSYSTEM_H

#include <memory.h>
#include <queue>

#include "VoxelRenderer.h"
#include "../Core/Core.h"
#include "../Components/Components.h"
#include "../Entities/VoxelEntity.h"
#include "../Threading/ThreadPool.h"
#include "../Voxel/VoxelChunkGrid.h"

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
    //VoxelGrid<VoxelGridCell> m_grid;
    VoxelChunkGrid m_grid;

    ThreadPool m_threadPool = ThreadPool((unsigned int)1);
    //std::queue<VoxelDrawArgs> m_drawQueue;

  protected:
    void OnEntityAdded(unsigned int entityId) override;
    void OnEntityRemoved(unsigned int entityId) override;
    UIntPoint3 GetLocalPoisition(UIntPoint3 globalPosition);
  public:
    VoxelGridSystem(unsigned int id, const SystemContext& context);
    ~VoxelGridSystem();

    void Init(unsigned int chunkCount, unsigned int voxelCount);
    void FillChunk(const UIntPoint3& position, glm::vec4 colour);

    void Init() override;
    void Update() override;
    void Draw() override;

    //void DrawVoxels(const UIntPoint3& position, unsigned int brushSize, const Colour& fillColour);
    //void DrawVoxel(const UIntPoint3& position, const Colour& colour);
    void Clear();
    
};
} // namespace tfl

#endif