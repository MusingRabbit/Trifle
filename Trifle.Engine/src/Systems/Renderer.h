#ifndef VOXELRENDERSYSTEM_H
#define VOXELRENDERSYSTEM_H

#include "../Core/System.h"
#include "../GLGameWindow.h"
#include "../Components/Components.h"
#include "../Graphics/Graphics.h"

#include <memory>

namespace trifle
{
class EntityManager;

class Renderer : public System
{
  private:
    void RenderModel(Model3D& model);

    void RenderMesh(Mesh mesh, Shader shader);
    void RenderMesh(Mesh mesh, Shader shader, Texture2D txr);

  public:
    Renderer(EntityManager& manager);

    ~Renderer();

    void Init() override;

    void Update(float dt) override;
};
} // namespace trifle

#endif // !VOXELRENDERSYSTEM_H
