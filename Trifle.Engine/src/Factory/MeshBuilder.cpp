#include "MeshBuilder.h"

#include "../Core/Types.h"
#include "../Data/Vertex.h"

using namespace glm;

namespace trifle
{

MeshData MeshBuilder::CreateQuad()
{
    MeshData result;

    // Vertex declerations...
    Vertex v0 = Vertex(vec3(1.0, 1.0, 0.0), vec2(1.0, 0.0));
    Vertex v1 = Vertex(vec3(1.0, -1.0, 0.0), vec2(1.0, 1.0));
    Vertex v2 = Vertex(vec3(-1.0, -1.0, 0.0), vec2(0.0, 1.0));
    Vertex v3 = Vertex(vec3(-1.0, 1.0, 0.0), vec2(0.0, 0.0));

    result.vertices.push_back(v0);
    result.vertices.push_back(v1);
    result.vertices.push_back(v2);
    result.vertices.push_back(v3);

    // First triangle
    result.indices.push_back(3);
    result.indices.push_back(2);
    result.indices.push_back(1);

    // Second triangle
    result.indices.push_back(3);
    result.indices.push_back(1);
    result.indices.push_back(0);

    return result;
}

} // namespace trifle
