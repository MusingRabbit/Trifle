#pragma once

#include "../../Core/Types.h"

#include <ft2build.h>
#include <freetype/freetype.h>

#include <vector>
#include <unordered_map>

namespace tfl
{
struct FontBitmap
{
    unsigned char* data = {};
    unsigned int dataSize = 0;
    unsigned int width = 0;
    unsigned int height = 0;
};

// Only for pairs of std::hash-able types for simplicity.
// You can of course template this struct to allow other hash functions
struct FontBitmapPairHash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1,T2> &p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);

        // Mainly for demonstration purposes, i.e. works but is overly simple
        // In the real world, use sth. like boost.hash_combine
        return h1 ^ h2;  
    }
};

class Font 
{
    private:
    FT_Face m_fontFace;
    FT_Library m_fontLib;

    std::unordered_map<std::pair<unsigned int, char32_t>, FontBitmap, FontBitmapPairHash> m_charSet;

    unsigned int m_fontSize = 16;

    void ErrorCheck(FT_Error error);

    void SetSize(unsigned int width, unsigned int height);

    public:
    Font();
    Font(const Font& rhs);
    ~Font();

    void SetSize(unsigned int size);
    unsigned int GetSize();

    void Load(const FontData& data);
    void Load(const char* filePath);

    bool IsLoaded();

    FontBitmap& GetCharacterBitmap(wchar_t charCode);
    void CreateCharacterSet();
};
}
