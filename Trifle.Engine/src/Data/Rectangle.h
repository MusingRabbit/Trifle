#pragma once

#include "Point2.h"

namespace tfl
{
struct Rectangle
{
    public:
    float x;
    float y;
    float width;
    float height;

    Rectangle()
    {
        float x = 0.0f;
        float y = 0.0f;
        float width = 0.0f;
        float height = 0.0f;
    }

    Rectangle(float _x, float _y, float _width, float _height)
    {
        x = _x;
        y = _y;
        width = _width;
        height = _height;
    }

    ~Rectangle() { }

    void SetPosition(const Point2& position)
    {
        x = (float)position.x;
        y = (float)position.y;
    }

    void SetSize(const Point2& scale)
    {
        width = (float)scale.x;
        height = (float)scale.y;
    }

    void SetSize(float size)
    {
        width = size; 
        height = size;
    }

    Point2 GetPosition() const
    {
        return {(int)x, (int)y};
    }

    Point2 TopLeft() const
    {
        return {(int)x, (int)y};
    }

    Point2 TopRight() const
    {
        return {(int)(x + width), (int)y};
    }

    Point2 BottomLeft() const
    {
        return {(int)x, (int)(y + height)};
    }

    Point2 BottomRight() const
    {
        return GetMax();
    }

    Point2 GetMax() const
    {
        Point2 result = {};
        result.x = (int)(x + width);
        result.y = (int)(y + height);
        return result;
    }

    Point2 GetSize() const
    {
        return {(int)width, (int)height};
    }

    bool IsEqual(const Rectangle& rhs) const
    {
        return x == rhs.x && y == rhs.y && height == rhs.height && width == rhs.width;
    }

    bool Contains(const Point2& point) const
    {
        Point2 max = GetMax();
        return x < point.x && y < point.y && max.x > point.x && max.y > point.y;
    }
};
}

