#ifndef CONVERTER_H
#define CONVERTER_H

#include <Data/Point2.h>
#include <Data/Point3.h>
#include <Data/UIntPoint2.h>
#include <Data/UIntPoint3.h>

#include <glm/glm.hpp>

namespace tfl
{
    class Convert
    {
        public :
            static Point2 ToPoint2(const UIntPoint2& v);
            static UIntPoint2 ToUIntPoint2(const Point2& v);
            static Point3 ToPoint3(const UIntPoint3& v);
            static UIntPoint3 ToUIntPoint3(const Point3& v);
            static glm::vec3 ToGlmVec3(const Point3& v);
            static Point3 ToPoint3(const glm::vec3 v);
    };
}
#endif