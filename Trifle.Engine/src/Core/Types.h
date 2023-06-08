#ifndef TYPES_H
#define TYPES_H

#include <bitset>

// ECS 
using EventId = unsigned int;
using ParamId = unsigned int;

const unsigned int MAX_COMPONENTS = 32;
const unsigned int MAX_ENTITIES = 5000;

using Signature = std::bitset<MAX_COMPONENTS>;

#endif // !TYPES_H
