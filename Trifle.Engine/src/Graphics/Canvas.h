#pragma once

#include "../Graphics/Text/Font.h"
#include "../Core/Types.h"
#include "../Data/Data.h"
#include <glm/glm.hpp>
#include <stdexcept>
#include <vector>

#include "../Resources/FontResources.h"

namespace tfl
{
class Canvas
{
  private:
    unsigned int m_width, m_height;

    std::vector<Colour> m_data;

    Colour m_clearColour;

    bool m_additiveBlend;
    bool m_overwrite;

    unsigned int GetIndex(const Point2& point)
    {
        return point.x + (point.y * m_width);
    }

    bool IsValidPoint(const Point2& point);

  public:
    Canvas();

    Canvas(unsigned int width, unsigned int height);

    ~Canvas();

    void Resize(unsigned int width, unsigned int height);

    unsigned int GetWidth();

    unsigned int GetHeight();
    
    float GetAspectRatio();
    
    void SetAdditiveBlend(bool value);

    void SetOverwriteExisting(bool value);

    void SetPixel(const Point2& point, const Colour& colour);
    
    void DrawCircle(const Point2& centre, const Colour& stroke, double radius);
    
    void DrawFilledCircle(const Point2& centre, const Colour& stroke, const Colour& fill, double radius);

    void DrawLine(const Point2& pointA, const Point2& pointB, const Colour& color);

    void DrawString(const Point2& point, std::string content, unsigned int fontSize, const Colour& colour = {1, 1, 1, 1});

    void DrawBox(const BoundingBox& box, const Colour& fill, const Colour& stroke);

    void DrawCharacter(const Point2& point, char32_t charCode, unsigned int fontSize, const Colour& colour = {1, 1, 1, 1});

    bool IsPixelSet(const Point2& point);

    Colour& GetPixel(const Point2& point);
    
    Colour* GetData();
    
    void ClearColour(const Colour& colour);
    
    void Clear();
    
};
} // namespace tfl