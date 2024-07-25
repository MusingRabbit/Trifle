#include "Converter.h"
#include <climits>

namespace tfl 
{
    Point2 Convert::ToPoint2(const UIntPoint2 & v)
    {
        int x = v.x > INT_MAX ? -(v.x - INT_MAX) : v.x;
        int y = v.y > INT_MAX ? -(v.y - INT_MAX) : v.y;

        return Point2( x, y );
    }

    UIntPoint2 Convert::ToUIntPoint2(const Point2& v)
    {
        return UIntPoint2((unsigned int)v.x, (unsigned int)v.y);
    }

    Point3 Convert::ToPoint3(const UIntPoint3& v)
    {
        int x = v.x > INT_MAX ? -(v.x - INT_MAX) : v.x;
        int y = v.y > INT_MAX ? -(v.y - INT_MAX) : v.y;
        int z = v.z > INT_MAX ? -(v.z - INT_MAX) : v.z;

        return Point3( x, y, z );
    }

    UIntPoint3 Convert::ToUIntPoint3(const Point3& v)
    {
        return UIntPoint3((unsigned int)v.x, (unsigned int)v.y, (unsigned int)v.z);
    }

    glm::vec3 Convert::ToGlmVec3(const Point3& v)
    {
        return {v.x, v.y, v.z};
    }

    Point3 Convert::ToPoint3(const glm::vec3 v)
    {
        return Point3((int)v.x, (int)v.y, (int)v.z);
    }

} // namespace tfl
