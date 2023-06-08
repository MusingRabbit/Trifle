#ifndef RENDERER_H
#define RENDERER_H

#include <glm/glm.hpp>

class Renderer
{
private:
public:
    Renderer();
    ~Renderer();

    void Clear(const glm::vec3& colour);
};




#endif // !RENDERER_H