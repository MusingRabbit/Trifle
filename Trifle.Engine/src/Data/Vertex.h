#ifndef VERTEX_H
#define VERTEX_H

#include <glm/glm.hpp>

namespace trifle
{
struct Vertex
{
    glm::vec3 position;
    glm::vec3 colour;
    glm::vec3 normal;
    glm::vec2 uv;

    Vertex(glm::vec3 pos)
    {
        position = pos;
    }

    Vertex(glm::vec3 pos, glm::vec3 norm)
    {
        position = pos;
        normal = norm;
    }

    Vertex(glm::vec3 pos, glm::vec3 norm, glm::vec2 txrPos)
    {
        position = pos;
        normal = norm;
        uv = txrPos;
    }

    Vertex(glm::vec3 pos, glm::vec2 txrPos)
    {
        position = pos;
        uv = txrPos;
    }
};
} // namespace trifle

#endif // !VERTEX_H