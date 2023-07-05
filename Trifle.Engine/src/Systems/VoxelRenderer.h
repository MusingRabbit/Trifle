#ifndef VOXELRASTERISER_H
#define VOXELRASTERISER_H

#include "../Core/System.h"
#include "../Core/Entity.h"
#include "../Core/EntityManager.h"
#include "../Data/Data.h"
#include "../Core/Types.h"

#include "../Graphics/Texture2D.h"

namespace trifle
{
class VoxelRenderer : public System
{
  private:
    unsigned int m_imageWidth, m_imageHeight;
    double m_totalElapsedTime;
    Entity m_screenEntity;
    Image m_screenImage;
    Texture2D* m_screenTexture;

    Colour m_clearColour = Colour(1.0f, 0.0f, 1.0f, 1.0f);

    void DoCommadore64LoadingScreen();

  public:
    VoxelRenderer(EntityManager& manager);
    ~VoxelRenderer();

    void SetImageSize(unsigned int width, unsigned int height);

    void Init() override;
    void Update(float dt) override;
    void RenderVoxelGrid(const VoxelGrid<VoxelGridCell>& grid);
};
} // namespace trifle

#endif // !VOXELRASTERISER_H
