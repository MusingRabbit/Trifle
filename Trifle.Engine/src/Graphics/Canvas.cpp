#include "Canvas.h"

namespace tfl
{
Canvas::Canvas()
{

}

Canvas::Canvas(unsigned int width, unsigned int height)
{
    Resize(width, height);
}

Canvas::~Canvas()
{
}

void Canvas::Resize(unsigned int width, unsigned int height)
{
    m_width = width;
    m_height = height;
    Clear();
    m_data = std::vector<Colour>(width * height, Colour{0, 0, 0, 0});
}

unsigned int Canvas::GetWidth()
{
    return m_width;
}

unsigned int Canvas::GetHeight()
{
    return m_height;
}

float Canvas::GetAspectRatio()
{
    return (float)m_width / (float)m_height;
}

void Canvas::SetAdditiveBlend(bool value)
{
    m_additiveBlend = value;
}

void Canvas::SetOverwriteExisting(bool value)
{
    m_overwrite = value;
}

bool Canvas::IsValidPoint(const Point2& point)
{
    if (point.x > m_width || point.y > m_height)
    {
        return false;
    }
    unsigned int idx = GetIndex(point);
    if (idx > m_data.size() - 1)
    {
        return false;
        // throw std::runtime_error("Index out of range. The point provided exceeds the range of the Canvas.");
    }

    return true;
}

void Canvas::SetPixel(const Point2& point, const Colour& colour)
{
    if (!IsValidPoint(point))
    {
        return;
    }

    Colour& pixel = m_data[GetIndex(point)];

    if (pixel.a > 0.99f && m_overwrite == false)
    {
        return;
    }
    
    if (m_additiveBlend)
    {
        pixel.r += colour.r;
        pixel.g += colour.g;
        pixel.b += colour.b;
        pixel.a += colour.a;
    }
    else
    {
        pixel.r = colour.r;
        pixel.g = colour.g;
        pixel.b = colour.b;
        pixel.a = colour.a;
    }
}

void Canvas::DrawCircle(const Point2& centre, const Colour& stroke, double radius)
{
    DrawFilledCircle(centre, stroke, Colour(0, 0, 0, 0), radius);
}

void Canvas::DrawFilledCircle(const Point2& centre, const Colour& stroke, const Colour& fill, double radius)
{
    int uintRad = (int)roundf((float)radius);
    for (int x = centre.x - uintRad; x <= centre.x + uintRad; x++)
    {
        for (int y = centre.y - uintRad; y <= centre.y + uintRad; y++)
        {
            Point2 point = Point2{x, y};
            int dX = point.x - centre.x;
            int dY = point.y - centre.y;
            double p = pow(static_cast<double>(dX), 2) + pow(static_cast<double>(dY), 2);
            double d = sqrt(p);
            int iD = (int)d;
            if (iD < (int)uintRad)
            {
                SetPixel(point, fill);
            }
            else if (iD == (int)uintRad)
            {
                SetPixel(point, stroke);
            }
        }
    }
}

void Canvas::DrawLine(const Point2& pointA, const Point2& pointB, const Colour& color)
{
    Point2 currPoint = {pointA.x, pointA.y};
    int dx = abs((int)(pointB.x - pointA.x)), sx = pointA.x < pointB.x ? 1 : -1;
    int dy = abs((int)(pointB.y - pointA.y)), sy = pointA.y < pointB.y ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2, e2;
    for (;;)
    {
        SetPixel(currPoint, color);
        if (currPoint.IsEqual(pointB))
            break;
        e2 = err;
        if (e2 > -dx)
        {
            err -= dy;
            currPoint.x += sx;
        }
        if (e2 < dy)
        {
            err += dx;
            currPoint.y += sy;
        }
    }
}

void Canvas::DrawString(const Point2& point, std::string content, unsigned int fontSize, const Colour& colour)
{
    Font& font = FontResources::GetDefaultFont();
    font.SetSize(fontSize);

    Point2 currPos;
    currPos.x = point.x;
    currPos.y = point.y;

    for (int x = 0; x < content.size(); x++)
    {
        char c = content[x];
        int padding = 1;

        FontBitmap& bitmap = font.GetCharacterBitmap(c);

        for (int x = 0; x < bitmap.width; x++)
        {
            for (int y = 0; y < bitmap.height; y++)
            {
                int idx = (bitmap.width * y) + x;

                if (idx < bitmap.dataSize && bitmap.data[idx])
                {
                    SetPixel({currPos.x + x, currPos.y + y}, colour);
                }
            }
        }

        currPos.x += bitmap.width + padding;
    }
}

void Canvas::DrawCharacter(const Point2& point, char32_t charCode, unsigned int fontSize, const Colour& colour)
{
    Font& font = FontResources::GetDefaultFont();
    font.SetSize(fontSize);

    FontBitmap bitmap = font.GetCharacterBitmap(charCode);

    for (int x = 0; x < bitmap.width; x++)
    {
        for (int y = 0; y < bitmap.height; y++)
        {
            int idx = (bitmap.width * y) + x;

            if (idx < bitmap.dataSize && bitmap.data[idx])
            {
                SetPixel({point.x + x, point.y + y}, colour);
            }
        }
    }
}

bool Canvas::IsPixelSet(const Point2& point)
{
    return IsValidPoint(point) == false || m_data[GetIndex(point)].a > 0.99f;
}

Colour& Canvas::GetPixel(const Point2& point)
{
    if (!IsValidPoint(point))
    {
        throw std::runtime_error("Index out of range. The point provided exceeds the range of the Canvas.");
    }

    return m_data[GetIndex(point)];
}

Colour* Canvas::GetData()
{
    return m_data.data();
}

void Canvas::ClearColour(const Colour& colour)
{
    m_clearColour = colour;
    std::fill(m_data.begin(), m_data.end(), colour);
}

void Canvas::Clear()
{
    std::fill(m_data.begin(), m_data.end(), Colour(0, 0, 0, 1.0f));
}

void Canvas::DrawBox(const Point2& pos, unsigned int width, unsigned int height, const Colour& fill, const Colour& stroke)
{
    int minX = pos.x < 0 ? 0 : pos.x;
    int minY = pos.y < 0 ? 0 : pos.y;

    int maxX = pos.x + width;
    int maxY = pos.y + height;
    maxX = maxX > m_width ? m_width : maxX;
    maxY = maxY > m_height ? m_height : maxY;

    bool hasFill = fill.a > 0;
    bool hasStroke = stroke.a > 0;
    bool hasPaint = hasFill || hasStroke;
    
    if (!hasPaint)
    {
        return;
    }
    
    for (int y = minY; y <= maxY; y++)
    {
        for (int x = minX; x <= maxX; x++)
        {
            if (hasStroke && (x == minX || x == maxX || y == minY || y == maxY))
            {
                SetPixel({x, y}, stroke);
            }
            else if (hasFill)
            {
                SetPixel({x, y}, fill);
            }
        }
    }
}

} // namespace tfl