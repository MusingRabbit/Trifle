#ifndef SHAPEDATA_H
#define SHAPEDATA_H

#include <vector>
#include "Vertex.h"

namespace tfl
{
struct MeshData
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    MeshData()
    {
    }

    MeshData(MeshData& rhs)
    {
        vertices = rhs.vertices;
        indices = rhs.indices;
    }
};
}; // namespace tfl

#endif // !SHAPEDATA_H
