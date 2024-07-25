#ifndef POINT3_H
#define POINT3_H

namespace tfl
{

struct Point3
{
    int x;
    int y;
    int z;

    Point3()
    {
        x = 0;
        y = 0;
        z = 0;
    }

    Point3(const Point3& rhs)
    {
        x = rhs.x;
        y = rhs.y;
        z = rhs.z;
    }

    Point3(int xVal, int yVal, int zVal)
    {
        x = xVal;
        y = yVal;
        z = zVal;
    }
    int sum()
    {
        return x + y + z;
    }

    Point3 multiply(int rhs)
    {
        return Point3(x * rhs, y * rhs, z * rhs);
    }
};

inline Point3& operator+=(Point3& lhs, const Point3& rhs) { lhs.x += rhs.x; lhs.y += rhs.y; lhs.z += rhs.z;  return lhs; }
inline Point3& operator-=(Point3& lhs, const Point3& rhs) { lhs.x -= rhs.x; lhs.y -= rhs.y; lhs.z -= rhs.z;  return lhs; } 
inline Point3 operator+(const Point3& lhs, const Point3& rhs) {  return Point3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z); }
inline Point3 operator-(const Point3& lhs, const Point3& rhs) {  return Point3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z); }
inline Point3 operator*(const Point3& lhs, const Point3& rhs) {  return Point3(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z); }
inline Point3 operator/(const Point3& lhs, const Point3& rhs) {  return Point3(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z); }

inline bool operator<(const Point3& lhs, const Point3& rhs) {  return lhs.x < rhs.x && lhs.y < rhs.y && lhs.z < rhs.z; }
inline bool operator>(const Point3& lhs, const Point3& rhs) {  return lhs.x > rhs.x && lhs.y > rhs.y && lhs.z > rhs.z; }
inline bool operator<=(const Point3& lhs, const Point3& rhs) {  return lhs.x <= rhs.x && lhs.y <= rhs.y && lhs.z <= rhs.z; }
inline bool operator>=(const Point3& lhs, const Point3& rhs) {  return lhs.x >= rhs.x && lhs.y >= rhs.y && lhs.z >= rhs.z; }
inline bool operator==(const Point3& lhs, const Point3& rhs) {  return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z; }

inline Point3 operator+(const Point3& lhs, int rhs) {  return Point3(lhs.x + rhs, lhs.y + rhs, lhs.z + rhs); }

inline Point3 operator-(const Point3& lhs, int rhs) {  return Point3(lhs.x - rhs, lhs.y - rhs, lhs.z - rhs); }
inline Point3 operator/(const Point3& lhs, int rhs) {  return Point3(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs); }

inline Point3 operator*(const Point3& lhs, float rhs) {  return Point3(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs); }
inline Point3 operator*(const Point3& lhs, double rhs) {  return Point3(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs); }
}

#endif // !UINT