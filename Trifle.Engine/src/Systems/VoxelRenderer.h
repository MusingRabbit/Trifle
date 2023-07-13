#ifndef VOXELRENDERER_H
#define VOXELRENDERER_H

#include "../Core/System.h"
#include "../Core/Entity.h"
#include "../Core/EntityManager.h"
#include "../Data/Data.h"
#include "../Core/Types.h"

#include "../Entities/Camera.h"
#include "../Graphics/Texture2D.h"

namespace trifle
{
class VoxelRenderer : public System
{
  private:
    unsigned int m_imageWidth, m_imageHeight;
    Entity m_screenEntity;
    Image m_screenImage;
    Texture2D* m_screenTexture;

    Camera m_camera;

    Colour m_clearColour = Colour(1.0f, 0.0f, 1.0f, 1.0f);
    Colour m_emtpyColour = Colour(1.0f, 1.0f, 1.0f, 0.0f);

    void DoCommadore64LoadingScreen();
    void UpdateScreenTexture();

  public:
    VoxelRenderer(EntityManager& manager);
    ~VoxelRenderer();

    void SetImageSize(unsigned int width, unsigned int height);

    void Init() override;
    void Update(float dt) override;

    void SetActiveCamera(unsigned int entityId);

    void RenderVoxelGrid(VoxelGrid<VoxelGridCell>& grid);
    void RenderVoxelGrid(VoxelGrid<VoxelGridCell>& grid, Camera& camera);
};
} // namespace trifle

#endif // !VOXELRENDERER_H
