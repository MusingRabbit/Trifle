#ifndef SHAPEDATA_H
#define SHAPEDATA_H

#include <vector>
#include "Vertex.h"

namespace trifle
{
struct ShapeData
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    ShapeData()
    {
    }

    ShapeData(ShapeData& rhs)
    {
        vertices = rhs.vertices;
        indices = rhs.indices;
    }
};
}; // namespace trifle

#endif // !SHAPEDATA_H
