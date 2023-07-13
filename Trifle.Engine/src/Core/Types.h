#ifndef TYPES_H
#define TYPES_H

#include "glm/glm.hpp"
#include <bitset>

// ECS
using EventId = unsigned int;
using ParamId = unsigned int;

const unsigned int MAX_COMPONENTS = 32;
const unsigned int MAX_ENTITIES = 10000;

using Signature = std::bitset<MAX_COMPONENTS>;

using ComponentType = std::uint8_t;

using Colour = glm::vec4;

#endif // !TYPES_H
