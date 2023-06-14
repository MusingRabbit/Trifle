#include "Renderer.h"

#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
namespace trifle
{
Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::Clear(const glm::vec3 &colour)
{
    glClearColor(colour.r, colour.g, colour.b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}
} // namespace trifle