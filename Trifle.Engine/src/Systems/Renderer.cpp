#include "Renderer.h"

#include "../Core/System.h"
#include "../Core/EntityManager.h"
#include "../Core/Entity.h"

#include "../Util/ShaderUtil.h"

#include "../Graphics/Graphics.h"

#include <stdexcept>

using namespace tfl;

Renderer::Renderer(unsigned int id, const SystemContext& context) : System(id, context)
{
}

Renderer::~Renderer()
{
}

void Renderer::Init()
{
    unsigned int initResult = glewInit();

    if (initResult != GLEW_OK)
    {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(initResult));
        throw std::runtime_error("Renderer :: GLEW initialisation failure.");
    }

    EnableAlphaBlending();
}

void tfl::Renderer::OnEntityAdded(unsigned int entityId)
{
}

void tfl::Renderer::OnEntityRemoved(unsigned int entityId)
{
}

void Renderer::EnableAlphaBlending()
{
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
}

void Renderer::Update()
{
    glClearColor(0, 0, 0.3f, 1.0f);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    for (unsigned int entityId : GetEntityIds())
    {
        Entity e = Entity(entityId);
        Model3D& model3D = e.GetComponent<Model3D>();

        RenderModel(model3D);
    }

    glFlush();
}

void Renderer::RenderModel(Model3D& model)
{
    Mesh& mesh = model.GetMesh();
    Material& material = model.GetMaterial();

    if (!mesh.IsSet())
    {
        throw std::runtime_error("Renderer :: Model mesh has not been set. Call 'SetMeshData' on Mesh.");
    }

    Shader shader;

    if (material.shader.IsInitialised())
    {
        shader = material.shader;
    }
    else
    {
        shader.Initialise(ShaderUtil::DefaultVs, ShaderUtil::DefaultFs);
    }

    if (material.texture.IsInitialised())
    {
        RenderMesh(mesh, shader, material.texture);
    }
    else
    {
        RenderMesh(mesh, shader);
    }
}

void Renderer::RenderMesh(Mesh mesh, Shader shader)
{
    shader.Use();
    mesh.Bind();

    glDrawElements(GL_TRIANGLES, mesh.IndexCount(), GL_UNSIGNED_INT, 0);
}

void Renderer::RenderMesh(Mesh mesh, Shader shader, Texture2D txr)
{
    shader.Use();
    txr.Bind();
    mesh.Bind();

    glDrawElements(GL_TRIANGLES, mesh.IndexCount(), GL_UNSIGNED_INT, 0);
}
