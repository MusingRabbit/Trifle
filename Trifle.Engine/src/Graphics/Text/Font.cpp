#include "Font.h"

#include <stdexcept>
#include <string>
#include <iostream>

namespace tfl
{
Font::Font()
{
    FT_Error error = FT_Init_FreeType(&m_fontLib);
    ErrorCheck(error);
}
Font::Font(const Font& rhs)
{
    m_fontFace = rhs.m_fontFace;
    m_fontLib = rhs.m_fontLib;
}
Font::~Font()
{
}

void Font::Load(const FontData& fontData)
{
    FT_Error error = FT_New_Memory_Face(m_fontLib, fontData.data, fontData.size, 0, &m_fontFace);
    ErrorCheck(error);
}

void Font::Load(const char* filePath)
{
    FT_Error error = FT_New_Face(m_fontLib, filePath, 0, &m_fontFace);
    ErrorCheck(error);
}

void Font::ErrorCheck(FT_Error error)
{
    if (error)
    {
        std::string msgErr = "Failed to load font. Error : ";
        msgErr.append(FT_Error_String(error));
        std::cout << msgErr.c_str() << std::endl;
        throw std::runtime_error(msgErr.c_str());
    }
}
} // namespace tfl
