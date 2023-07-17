#ifndef MESH_H
#define MESH_H

#include "../Data/MeshData.h"
#include <vector>
#include <GL/glew.h>

namespace tfl
{
class Mesh
{
  private:
    unsigned int m_id = -1;

    enum BufferType
    {
        VERTEX_BUFFER,
        INDEX_BUFFER,
        BUFFER_COUNT
    };

    GLuint m_arrayBuffers[BUFFER_COUNT];

    unsigned int m_drawCount;

    void Clear();

  public:
    Mesh();
    Mesh(const Mesh& rhs);
    ~Mesh();

    unsigned int IndexCount();
    void SetMeshData(MeshData data);

    void Bind();
    void Unbind();

    bool IsSet();
};
} // namespace tfl

#endif // !MESH_H