#ifndef VOXELRENDERSYSTEM_H
#define VOXELRENDERSYSTEM_H

#include "../GLInclude.h"

#include "../Core/System.h"
#include "../GameWindow.h"
#include "../Components/Components.h"
#include "../Graphics/Graphics.h"

#include <memory>

namespace tfl
{
class EntityManager;

class Renderer : public System
{
  private:
    void RenderModel(Model3D& model);

    void RenderMesh(Mesh mesh, Shader shader);
    void RenderMesh(Mesh mesh, Shader shader, Texture2D txr);

  public:
    Renderer(unsigned int id, const SystemContext& context);

    ~Renderer();

    void Init() override;
    void OnEntityAdded(unsigned int entityId) override;
    void OnEntityRemoved(unsigned int entityId) override;

    void EnableAlphaBlending();

    void Update() override;
    void Draw() override;
};
} // namespace tfl

#endif // !VOXELRENDERSYSTEM_H
