#ifndef VOXELRENDERER_H
#define VOXELRENDERER_H

#include "../Core/System.h"
#include "../Core/Entity.h"
#include "../Core/EntityManager.h"
#include "../Data/Data.h"
#include "../Core/Types.h"

#include "../Entities/Camera.h"
#include "../Graphics/Graphics.h"

#include "VoxelRasteriser.h"
#include "../Voxel/Voxel.h"

namespace tfl
{
  enum RenderMethod
  {
      RENDER_NORM, 
      RENDER_DEBUG
  };

  struct ViewData
  {
    glm::vec3 viewPos;
    glm::mat4 mtxView;
    glm::mat4 mtxProj;
    glm::mat4 mtxViewProj;
    glm::mat4 mtxInvViewProj;
    glm::vec4 viewPort;
    float zNear;
    float zFar;
  };

  class VoxelRenderer : public System
  {
    private:
      unsigned int m_screenWidth, m_screenHeight;
      //Entity m_screenEntity;
      //Canvas m_canvas;
      //Texture2D* m_screenTexture;
      std::shared_ptr<VoxelRasteriser> m_raster;
      
      BoundingBox m_viewBox;

      Camera m_camera;

      ViewData m_viewData;

      //Colour m_clearColour = Colour(1.0f, 0.0f, 1.0f, 1.0f);
      //Colour m_emtpyColour = Colour(0.0f, 0.0f, 0.0f, 0.0f);

      //void DoCommadore64LoadingScreen();
      //void UpdateScreenTexture();

      //void ForceDraw();

      glm::vec4 TransformWorldView(Camera& camera, glm::vec4 fPos);
      ViewData GetViewData(Camera& camera);
      void CreateViewBoundingBox(const ViewData& viewData);

      bool IsCellVisibleFilter(VoxelGridCell* cell);
      bool IsCellLitFilter(VoxelGridCell* cell);

      bool IsChunkVisible(const ViewData& vd, VoxelChunk& chunk);
      bool IsPointVisible(const ViewData& vd, UIntPoint3 point);
      void UpdateViewData(Camera& camera);

      void ProcessVoxelChunk(VoxelChunk& chunk, Camera& camera);
      void ProcessVoxelChunk_Debug_BoxRender(VoxelChunk& grid, Camera& camera);

    protected:
      void OnEntityAdded(unsigned int entityId) override;
      void OnEntityRemoved(unsigned int entityId) override;
      


    public:
      VoxelRenderer(unsigned int id, const SystemContext& context);
      ~VoxelRenderer();

      //void SetImageSize(unsigned int width, unsigned int height);

      void Init() override;
      void Update() override;

      void ProcessVoxelChunk(VoxelChunk& chunk, RenderMethod method);
      //void UpdateScreenTexture();

      void SetActiveCamera(unsigned int entityId);


      //void ProcessVoxelGrid_Debug_Slow(VoxelGrid<VoxelGridCell>& grid, Camera& camera);
      //void ProcessVoxelGrid_Debug_BoxRender(VoxelGrid<VoxelGridCell>& grid, Camera& camera, bool drawCellOutlines);
      

      void DrawDebugInfo(std::string strContent);

      void Draw();

      void Clear();
  };
} // namespace tfl

#endif // !VOXELRENDERER_H
