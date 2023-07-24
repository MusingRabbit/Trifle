#include "../Components/Components.h"
#include "MeshBuilder.h"
#include "MaterialBuilder.h"
#include "EntityBuilder.h"

namespace tfl
{

Entity EntityBuilder::MakeCamera(float aspectRatio, float nearPlane, float farPlane)
{
    Entity result = Entity::Create();

    Projection proj = Projection(aspectRatio, nearPlane, farPlane);

    result.AddComponent<Projection>(proj);
    result.AddComponent<Movement>();
    result.AddComponent<Target>();

    return result;
}

Entity EntityBuilder::CreateTexturedQuad()
{
    Entity result = Entity::Create();

    Model3D model;

    MeshData data = MeshBuilder::CreateQuad();
    model.GetMesh().SetMeshData(data);
    model.SetMaterial(MaterialBuilder::CreateBasicTextureMaterial());

    result.AddComponent<Model3D>(model);

    return result;
}
} // namespace tfl
