#ifndef UINTPOINT3_H
#define UINTPOINT3_H

namespace tfl
{

struct UIntPoint3
{
    unsigned int x;
    unsigned int y;
    unsigned int z;

    UIntPoint3()
    {
        x = 0;
        y = 0;
        z = 0;
    }

    UIntPoint3(const UIntPoint3& rhs)
    {
        x = rhs.x;
        y = rhs.y;
        z = rhs.z;
    }

    UIntPoint3(unsigned int xVal, unsigned int yVal, unsigned int zVal)
    {
        x = xVal;
        y = yVal;
        z = zVal;
    }
    unsigned int sum()
    {
        return x + y + z;
    }
};

inline UIntPoint3& operator+=(UIntPoint3& lhs, const UIntPoint3& rhs) { lhs.x += rhs.x; lhs.y += rhs.y; lhs.z += rhs.z;  return lhs; }
inline UIntPoint3& operator-=(UIntPoint3& lhs, const UIntPoint3& rhs) { lhs.x -= rhs.x; lhs.y -= rhs.y; lhs.z -= rhs.z;  return lhs; } 
inline UIntPoint3 operator+(const UIntPoint3& lhs, const UIntPoint3& rhs) {  return UIntPoint3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z); }
inline UIntPoint3 operator-(const UIntPoint3& lhs, const UIntPoint3& rhs) {  return UIntPoint3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z); }
inline UIntPoint3 operator*(const UIntPoint3& lhs, const UIntPoint3& rhs) {  return UIntPoint3(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z); }
inline bool operator==(const UIntPoint3& lhs, const UIntPoint3& rhs) {  return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z; }

}

#endif // !UINT