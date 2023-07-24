#include "FontResources.h"

namespace tfl
{
Font FontResources::defaultFont = Font();

Font& FontResources::GetDefaultFont()
{
    if (!defaultFont.IsLoaded())
    {
        defaultFont.Load(Windows_Fonts_Arial_ttf);
    }
    
    return defaultFont;
}
}

