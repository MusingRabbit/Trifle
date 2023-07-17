#ifndef MATERIAL_H
#define MATERIAL_H

#include "Shader.h"
#include "Texture2D.h"
#include "../Components/Component.h"

namespace tfl
{
struct Material
{
    Shader shader;
    Texture2D texture;
};
} // namespace tfl

#endif // !MATERIAL_H
