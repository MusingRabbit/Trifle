#ifndef POINT2_H
#define POINT2_H

namespace tfl
{
struct Point2
{
    int x = 0;
    int y = 0;

    bool IsEqual(const Point2& rhs)
    {
        return x == rhs.x && y == rhs.y;
    }
};
}

#endif // !POINT2_H