#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include "../Core/Types.h"
#include <array>

namespace tfl
{
class Texture2D
{
  private:
    unsigned int m_id = -1;
    unsigned int m_width, m_height;

  public:
    Texture2D();
    Texture2D(const Texture2D& rhs);
    ~Texture2D();

    void SetDataByColour(unsigned int width, unsigned int height, Colour* data);
    void SubDataByColour(Colour* data);
    void Bind();
    void Unbind();

    bool IsInitialised();
};
} // namespace tfl

#endif // !TEXTURE2D_H