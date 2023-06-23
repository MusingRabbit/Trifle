#ifndef UINTPOINT3_H
#define UINTPOINT3_H

struct UIntPoint3
{
    unsigned int x;
    unsigned int y;
    unsigned int z;

    bool IsEqual(const UIntPoint3& rhs)
    {
        return x == rhs.x && y == rhs.y && z == rhs.z;
    }
};

#endif // !UINT