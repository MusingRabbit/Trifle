#ifndef TARGET_H
#define TARGET_H

#include <glm/glm.hpp>

namespace trifle
{
enum TargetType
{
    TARGET_NONE,
    TARGET_ENTITY,
    TARGET_POSITION
};

struct Target
{
    TargetType targetType = TARGET_POSITION;

    unsigned int entityId;
    glm::vec3 position;
};
} // namespace trifle

#endif // !TARGET_H
