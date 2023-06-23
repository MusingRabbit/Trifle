#include "Model.h"

namespace trifle
{

Model::Model()
{
}

Model::~Model()
{
    Clear();
}

void Model::SetModelData(ShapeData data)
{
    Clear();

    m_data = data;

    unsigned int vertexByteSize = sizeof(Vertex);
    unsigned int indexByteSize = sizeof(unsigned int);

    glGenVertexArrays(1, &m_id);
    glBindVertexArray(m_id);

    glGenBuffers(BUFFER_COUNT, m_arrayBuffers);

    glBindBuffer(GL_ARRAY_BUFFER, m_arrayBuffers[VERTEX_BUFFER]);
    glBufferData(GL_ARRAY_BUFFER, m_data.vertices.size() * vertexByteSize, m_data.vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_arrayBuffers[INDEX_BUFFER]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_data.indices.size() * indexByteSize, m_data.indices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0); // Attrib pointer for Vertex Position
    glEnableVertexAttribArray(1); // Attrib pointer for Vertex Colour
    glEnableVertexAttribArray(2); // Attrib pointer for Vertex Normal
    glEnableVertexAttribArray(3); // Attrib pointer for Vertex Texture Coord

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexByteSize, 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertexByteSize, (void*)(sizeof(float) * 3));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, vertexByteSize, (void*)(sizeof(float) * 6));
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, vertexByteSize, (void*)(sizeof(float) * 9));

    m_drawCount = m_data.indices.size();
}

void Model::Draw()
{
    // render container
    glBindVertexArray(m_id);
    glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, 0);
}

void Model::Clear()
{
    if (m_id != -1)
    {
        glDeleteBuffers(BUFFER_COUNT, m_arrayBuffers);
        glDeleteVertexArrays(1, &m_id);
    }
}
} // namespace trifle