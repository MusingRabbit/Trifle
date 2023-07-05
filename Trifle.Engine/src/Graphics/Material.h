#ifndef MATERIAL_H
#define MATERIAL_H

#include "Shader.h"
#include "Texture2D.h"
#include "../Components/Component.h"

namespace trifle
{
struct Material
{
    Shader shader;
    Texture2D texture;
};
} // namespace trifle

#endif // !MATERIAL_H
