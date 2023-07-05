#ifndef MODEL3D_H
#define MODEL3D_H

#include "../Graphics/Graphics.h"
#include <vector>

namespace trifle
{
class Model3D
{
  private:
    Mesh m_mesh;
    Material m_material;

    std::vector<Model3D> models;

  public:
    Model3D();
    Model3D(const Model3D& rhs);
    ~Model3D();

    void SetMaterial(const Material& material);
    void SetMesh(const Mesh& mesh);
    void AddSubModel(Model3D model);

    Mesh& GetMesh();
    Material& GetMaterial();
    std::vector<Model3D>& GetSubModels();
};
} // namespace trifle

#endif // !MODEL3D_H
