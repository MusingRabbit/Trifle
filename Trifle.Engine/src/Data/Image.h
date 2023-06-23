#ifndef IMAGE_H
#define IMAGE_H

#include "../Core/Types.h"
#include "UIntPoint2.h"
#include <glm/glm.hpp>
#include <stdexcept>
#include <vector>

namespace trifle
{
class Image
{
  private:
    unsigned int m_width, m_height;

    std::vector<Colour> m_data;

    unsigned int GetIndex(const UIntPoint2& point)
    {
        return point.x + (point.y * m_width);
    }

  public:
    Image()
    {
    }

    Image(unsigned int width, unsigned int height)
    {
        Resize(width, height);
    }

    ~Image()
    {
    }

    void Resize(unsigned int width, unsigned int height)
    {
        m_width = width;
        m_height = height;
        Clear();
        m_data = std::vector<Colour>(width * height, Colour{0, 0, 0, 0});
    }

    unsigned int GetWidth()
    {
        return m_width;
    }

    unsigned int GetHeight()
    {
        return m_height;
    }

    void SetPixel(const UIntPoint2& point, const Colour& colour)
    {
        unsigned int idx = GetIndex(point);

        if (idx > m_data.size())
        {
            throw std::runtime_error("Index out of range. The point provided exceeds the range of the image.");
        }

        m_data[idx] = Colour(colour.r, colour.g, colour.b, colour.a);
    }

    void DrawCircle(const UIntPoint2& centre, const Colour& stroke, double radius)
    {
        DrawFilledCircle(centre, stroke, Colour(0, 0, 0, 0), radius);
    }

    void DrawFilledCircle(const UIntPoint2& centre, const Colour& stroke, const Colour& fill, double radius)
    {
        float diam = radius * 2;

        for (unsigned int x = centre.x - radius; x <= centre.x + radius; x++)
        {
            for (unsigned int y = centre.y - radius; y <= centre.y + radius; y++)
            {
                UIntPoint2 point = UIntPoint2{x, y};
                int dX = point.x - centre.x;
                int dY = point.y - centre.y;
                double p = pow(static_cast<double>(dX), 2) + pow(static_cast<double>(dY), 2);
                double d = sqrt(p);

                int iD = (int)d;

                if (iD < (int)radius)
                {
                    SetPixel(point, fill);
                }
                else if (iD == (int)radius)
                {
                    SetPixel(point, stroke);
                }
            }
        }
    }

    void DrawBox(const UIntPoint2& pos, unsigned int width, unsigned int height, const Colour& fill,
                 const Colour& stroke)
    {
        unsigned int minX = pos.x;
        unsigned int minY = pos.y;
        unsigned int maxX = pos.x + width;
        unsigned int maxY = pos.y + height;

        for (unsigned int x = minX; x <= maxX; x++)
        {
            for (unsigned int y = minY; y <= maxY; y++)
            {

                if (x == minX || x == maxX || y == minY || y == maxY)
                {
                    SetPixel({x, y}, stroke);
                }
                else
                {
                    SetPixel({x, y}, fill);
                }
            }
        }
    }

    void DrawLine(const UIntPoint2& pointA, const UIntPoint2& pointB, const Colour& color)
    {
        UIntPoint2 currPoint = {pointA.x, pointA.y};
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

    Colour GetPixel(const UIntPoint2 point)
    {
        return m_data[GetIndex(point)];
    }

    Colour* GetData()
    {
        return m_data.data();
    }

    void ClearColour(const Colour& colour)
    {
        std::fill(m_data.begin(), m_data.end(), colour);
    }

    void Clear()
    {
        std::fill(m_data.begin(), m_data.end(), Colour(0, 0, 0, 1.0f));
    }
};
} // namespace trifle

#endif //  IMAGE_H