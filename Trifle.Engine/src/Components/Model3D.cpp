#include "Model3D.h"

#include <stdexcept>

namespace trifle
{
Model3D::Model3D()
{
}

Model3D::Model3D(const Model3D& rhs)
{
    m_material = rhs.m_material;
    m_mesh = rhs.m_mesh;
}

Model3D::~Model3D()
{
}

void Model3D::SetMaterial(const Material& material)
{
    m_material.shader = material.shader;
    m_material.texture = material.texture;
}

void Model3D::SetMesh(const Mesh& mesh)
{
    m_mesh = mesh;
}

void Model3D::AddSubModel(Model3D model)
{
    throw std::runtime_error("Not Implemented");
}

Mesh& Model3D::GetMesh()
{
    return m_mesh;
}

Material& Model3D::GetMaterial()
{
    return m_material;
}

std::vector<Model3D>& Model3D::GetSubModels()
{
    return models;
}
}; // namespace trifle
