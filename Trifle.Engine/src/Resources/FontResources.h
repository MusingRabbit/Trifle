#pragma once

#include "../Core/Types.h"
#include "../Graphics/Text/Font.h"

namespace tfl
{
class FontResources
{
  private:
    static Font defaultFont;

  public:
    static FontData Windows_Fonts_Arial_ttf;

    static Font& GetDefaultFont();
};
} // namespace tfl