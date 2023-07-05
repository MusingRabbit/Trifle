#ifndef MATERIALFACTORY_H
#define MATERIALFACTORY_H

#include "../Graphics/Graphics.h"
#include "../Util/ShaderUtil.h"

namespace trifle
{
class MaterialBuilder
{
  public:
    static Material CreateDefaultMaterial()
    {
        Material result;
        result.shader.Initialise(ShaderUtil::DefaultVs, ShaderUtil::DefaultFs);
        return result;
    }

    static Material CreateBasicTextureMaterial()
    {
        Material result;

        result.shader.Initialise(ShaderUtil::BasicTextureVs, ShaderUtil::BasicTextureFs);

        return result;
    }
};
}; // namespace trifle

#endif // !MATERIALFACTORY_H