#ifndef UINTPOINT2_H
#define UINTPOINT2_H

struct UIntPoint2
{
    unsigned int x;
    unsigned int y;

    bool IsEqual(const UIntPoint2& rhs)
    {
        return x == rhs.x && y == rhs.y;
    }
};

#endif // !UINTPOINT2_H
