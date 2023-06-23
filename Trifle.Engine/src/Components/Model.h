#ifndef MODEL_H
#define MODEL_H

#include "../Data/ShapeData.h"
#include <vector>
#include <GL/glew.h>

namespace trifle
{
class Model
{
  private:
    unsigned int m_id = -1;

    enum
    {
        VERTEX_BUFFER,
        INDEX_BUFFER,
        BUFFER_COUNT
    };

    GLuint m_arrayBuffers[BUFFER_COUNT];

    unsigned int m_drawCount;

    ShapeData m_data;

    void Clear();

  public:
    Model();
    ~Model();

    void SetModelData(ShapeData data);
    void Draw();
};
} // namespace trifle

#endif // !MODEL_H