#include "../Components/Components.h"
#include "MeshBuilder.h"
#include "MaterialBuilder.h"
#include "EntityBuilder.h"

namespace trifle
{

Entity EntityBuilder::MakeCamera(float aspectRatio, float nearPlane, float farPlane)
{
    Entity result = Entity::Create();

    Projection proj = Projection(aspectRatio, nearPlane, farPlane);

    result.AddComponent<Projection>(proj);
    result.AddComponent<Movement>();

    return result;
}

Entity EntityBuilder::CreateTexturedQuad()
{
    Entity result = Entity::Create();

    Model3D model;
    model.GetMesh().SetMeshData(MeshBuilder::CreateQuad());
    model.SetMaterial(MaterialBuilder::CreateBasicTextureMaterial());

    result.AddComponent<Model3D>(model);

    return result;
}
} // namespace trifle
