#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include "../Core/Types.h"
#include "../Data/Image.h"
#include <array>

namespace trifle
{
class Texture2D
{
  private:
    unsigned int m_id, m_width, m_height;

  public:
    Texture2D();
    ~Texture2D();

    void SetDataByColour(unsigned int width, unsigned int height, Colour* data);
    void SubDataByColour(Colour* data);
    void Bind();
    void Unbind();
};
} // namespace trifle

#endif // !TEXTURE2D_H