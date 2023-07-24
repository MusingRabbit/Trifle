#ifndef VOXELRENDERER_H
#define VOXELRENDERER_H

#include "../Core/System.h"
#include "../Core/Entity.h"
#include "../Core/EntityManager.h"
#include "../Data/Data.h"
#include "../Core/Types.h"

#include "../Entities/Camera.h"
#include "../Graphics/Graphics.h"

namespace tfl
{
enum RenderMethod
{
    RENDER_NORM, 
    RENDER_DEBUG
};

class VoxelRenderer : public System
{
  private:
    unsigned int m_imageWidth, m_imageHeight;
    Entity m_screenEntity;
    Canvas m_canvas;
    Texture2D* m_screenTexture;

    Camera m_camera;

    Colour m_clearColour = Colour(1.0f, 0.0f, 1.0f, 1.0f);
    Colour m_emtpyColour = Colour(0.0f, 0.0f, 0.0f, 0.0f);

    void DoCommadore64LoadingScreen();
    void UpdateScreenTexture();

    void ForceDraw();

    glm::vec4 TransformWorldView(Camera& camera, glm::vec4 fPos);

  public:
    VoxelRenderer(unsigned int id, const SystemContext& context);
    ~VoxelRenderer();

    void SetImageSize(unsigned int width, unsigned int height);

    void Init() override;
    void Update(float dt) override;

    void SetActiveCamera(unsigned int entityId);

    void RenderVoxelGrid(VoxelGrid<VoxelGridCell>& grid, RenderMethod method);
    void RenderVoxelGrid(VoxelGrid<VoxelGridCell>& grid, Camera& camera);
    
    void RenderVoxelGrid_Debug(VoxelGrid<VoxelGridCell>& grid, Camera& camera);

    void Clear();
};
} // namespace tfl

#endif // !VOXELRENDERER_H
