#ifndef POINT2_H
#define POINT2_H

namespace tfl
{
struct Point2
{
    int x;
    int y;

    Point2()
    {
        x = 0;
        y = 0;
    }

    Point2(const Point2& rhs)
    {
        x = rhs.x;
        y = rhs.y;
    }

    Point2(int xVal, int yVal)
    {
        x = xVal;
        y = yVal;
    }

    int sum()
    {
        return x + y;
    }

    Point2 multiply(int rhs)
    {
        return Point2(x * rhs, y * rhs);
    }
};

inline Point2& operator+=(Point2& lhs, const Point2& rhs) { lhs.x += rhs.x; lhs.y += rhs.y;  return lhs; }
inline Point2& operator-=(Point2& lhs, const Point2& rhs) { lhs.x -= rhs.x; lhs.y -= rhs.y;  return lhs; } 
inline Point2 operator+(const Point2& lhs, const Point2& rhs) {  return Point2(lhs.x + rhs.x, lhs.y + rhs.y); }
inline Point2 operator-(const Point2& lhs, const Point2& rhs) {  return Point2(lhs.x - rhs.x, lhs.y - rhs.y); }
inline Point2 operator*(const Point2& lhs, const Point2& rhs) {  return Point2(lhs.x * rhs.x, lhs.y * rhs.y); }
inline Point2 operator/(const Point2& lhs, const Point2& rhs) {  return Point2(lhs.x / rhs.x, lhs.y / rhs.y); }

inline bool operator<(const Point2& lhs, const Point2& rhs) {  return lhs.x < rhs.x && lhs.y < rhs.y; }
inline bool operator>(const Point2& lhs, const Point2& rhs) {  return lhs.x > rhs.x && lhs.y > rhs.y; }
inline bool operator<=(const Point2& lhs, const Point2& rhs) {  return lhs.x <= rhs.x && lhs.y <= rhs.y; }
inline bool operator>=(const Point2& lhs, const Point2& rhs) {  return lhs.x >= rhs.x && lhs.y >= rhs.y; }
inline bool operator==(const Point2& lhs, const Point2& rhs) {  return lhs.x == rhs.x && lhs.y == rhs.y; }

inline Point2 operator+(const Point2& lhs, int rhs) {  return Point2(lhs.x + rhs, lhs.y + rhs); }

inline Point2 operator-(const Point2& lhs, int rhs) {  return Point2(lhs.x - rhs, lhs.y - rhs); }
inline Point2 operator/(const Point2& lhs, int rhs) {  return Point2(lhs.x / rhs, lhs.y / rhs); }

inline Point2 operator*(const Point2& lhs, float rhs) {  return Point2(lhs.x * rhs, lhs.y * rhs); }
inline Point2 operator*(const Point2& lhs, double rhs) {  return Point2(lhs.x * rhs, lhs.y * rhs); }
};

#endif // !POINT2_H