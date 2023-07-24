#include "Font.h"

#include <stdexcept>
#include <string>
#include <iostream>

#include <freetype/ftglyph.h>
#include "../../Data/Data.h"

namespace tfl
{
Font::Font()
{
    m_charSet = {};
    FT_Error error = FT_Init_FreeType(&m_fontLib);
    ErrorCheck(error);
}

Font::Font(const Font& rhs)
{
    m_fontFace = rhs.m_fontFace;
    m_fontLib = rhs.m_fontLib;
    m_fontSize = rhs.m_fontSize;
}

Font::~Font()
{

}

void Font::SetSize(unsigned int size)
{
    m_fontSize = size;
    SetSize(0, m_fontSize);
}

unsigned int Font::GetSize()
{
    return m_fontSize;
}

void Font::SetSize(unsigned int width, unsigned int height)
{
    FT_Error error = FT_Set_Char_Size(m_fontFace, width * 64, height * 64, 300, 300);
    ErrorCheck(error);
}

void Font::Load(const FontData& fontData)
{
    FT_Error error = FT_New_Memory_Face(m_fontLib, fontData.data, fontData.size, 0, &m_fontFace);
    ErrorCheck(error);

    SetSize(m_fontSize);
}

void Font::Load(const char* filePath)
{
    FT_Error error = FT_New_Face(m_fontLib, filePath, 0, &m_fontFace);
    ErrorCheck(error);

    SetSize(m_fontSize);
}

bool Font::IsLoaded()
{
    return m_fontFace != NULL;
}

FontBitmap& Font::GetCharacterBitmap(wchar_t charCode)
{
    auto itr = m_charSet.find({m_fontSize, charCode});

    if (itr != m_charSet.end())
    {
        return itr->second;
    }

    unsigned int idxGlyth = FT_Get_Char_Index(m_fontFace, charCode);

    ErrorCheck(FT_Load_Glyph(m_fontFace, idxGlyth, FT_LOAD_DEFAULT));

    ErrorCheck(FT_Render_Glyph(m_fontFace->glyph, FT_Render_Mode::FT_RENDER_MODE_NORMAL));

    FT_GlyphSlot glyth = m_fontFace->glyph;
    FT_Glyph_Metrics metrics = glyth->metrics;

    unsigned int maxAscent = int(m_fontFace->ascender * (m_fontFace->size->metrics.y_scale / 65536.0)) >> 6;
    unsigned int maxDescent = int(abs(m_fontFace->descender * (m_fontFace->size->metrics.y_scale / 65536.0))) >> 6;

    unsigned int advance = metrics.horiAdvance / 64;
    unsigned int imgWidth = glyth->bitmap.width;
    unsigned int imgHeight = maxAscent + maxDescent;

    if (charCode == 32)
    {
        imgWidth = advance;
        imgHeight = advance;
    }

    unsigned int imgSize = imgWidth * imgHeight;

    unsigned int glythWidth = metrics.width / 64;
    unsigned int glythHeight = metrics.height / 64;
    
    unsigned int yOffset = maxAscent - glyth->bitmap_top;

    // Top Left of glyth
    UIntPoint2 minPoint = {0, 0};   
    // Bottom right of glyth
    UIntPoint2 maxPoint = {minPoint.x + glythWidth, minPoint.y + glythHeight};  

    FontBitmap result = {};
    result.data = new unsigned char[imgSize]{0};
    result.width = imgWidth;
    result.height = imgHeight;
    result.dataSize = imgSize;

    for (unsigned int x = 0; x < imgWidth; x++)
    {
        for (unsigned int y = 0; y < imgHeight; y++)
        {
            bool boundsCheck = x > minPoint.x && y > minPoint.y && x < maxPoint.x && y < maxPoint.y;

            if (boundsCheck)
            {
                unsigned int glythIdx = x + (imgWidth * y);
                unsigned int resIdx = (x) + (imgWidth * (y + yOffset));

                result.data[resIdx] = glyth->bitmap.buffer[glythIdx];
            }
        }
    }

    m_charSet.insert({{m_fontSize, charCode}, result});

    return m_charSet[{m_fontSize, charCode}];
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
