#pragma once

#include "../../Core/Types.h"

#include <ft2build.h>
#include <freetype/freetype.h>

namespace tfl
{
class Font 
{
    private:
    FT_Face m_fontFace;
    FT_Library m_fontLib;

    void ErrorCheck(FT_Error error);

    public:
    Font();
    Font(const Font& rhs);
    ~Font();

    void Load(const FontData& data);
    void Load(const char* filePath);
    
};
}
