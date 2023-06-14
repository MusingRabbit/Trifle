#ifndef RENDERER_H
#define RENDERER_H

#include <glm/glm.hpp>
namespace trifle
{
class Renderer
{
  private:
  public:
    Renderer();
    ~Renderer();

    void Clear(const glm::vec3 &colour);
};
} // namespace trifle

#endif // !RENDERER_H