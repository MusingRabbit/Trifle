#include "Mesh.h"

namespace tfl
{

Mesh::Mesh()
{
}

Mesh::Mesh(const Mesh& rhs)
{
    m_id = rhs.m_id;

    for (int i = 0; i < BUFFER_COUNT; i++)
    {
        m_arrayBuffers[i] = rhs.m_arrayBuffers[i];
    }

    m_drawCount = rhs.m_drawCount;
}

Mesh::~Mesh()
{
}

unsigned int Mesh::IndexCount()
{
    return m_drawCount;
}

void Mesh::SetMeshData(MeshData data)
{
    Clear();

    glGenVertexArrays(1, &m_id);

    unsigned int vertexByteSize = sizeof(Vertex);
    unsigned int indexByteSize = sizeof(unsigned int);

    glBindVertexArray(m_id);

    glGenBuffers(BUFFER_COUNT, m_arrayBuffers);

    glBindBuffer(GL_ARRAY_BUFFER, m_arrayBuffers[VERTEX_BUFFER]);
    glBufferData(GL_ARRAY_BUFFER, data.vertices.size() * vertexByteSize, data.vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_arrayBuffers[INDEX_BUFFER]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.indices.size() * indexByteSize, data.indices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0); // Attrib pointer for Vertex Position
    glEnableVertexAttribArray(1); // Attrib pointer for Vertex Colour
    glEnableVertexAttribArray(2); // Attrib pointer for Vertex Normal
    glEnableVertexAttribArray(3); // Attrib pointer for Vertex Texture Coord

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexByteSize, 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertexByteSize, (void*)(sizeof(float) * 3));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, vertexByteSize, (void*)(sizeof(float) * 6));
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, vertexByteSize, (void*)(sizeof(float) * 9));

    m_drawCount = data.indices.size();

    Unbind();
}

void Mesh::Bind()
{
    glBindVertexArray(m_id);
}

void Mesh::Unbind()
{
    glBindVertexArray(0);
}

bool Mesh::IsSet()
{
    return m_id != -1;
}

void Mesh::Clear()
{
    if (m_id != -1)
    {
        glDeleteBuffers(BUFFER_COUNT, m_arrayBuffers);
        glDeleteVertexArrays(1, &m_id);
    }
}
} // namespace tfl