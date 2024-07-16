#ifndef VIEWPORTHELPER_H
#define VIEWPORTHELPER_H

#include <glm/glm.hpp>
#include "../../Data/Data.h"

class ViewportHelper
{
    private:
    UIntPoint2 m_screenSize;
    UIntPoint2 m_viewSize;


    public:

    static UIntPoint2 GetViewPosFromScreen(const UIntPoint2& screenPoint)
    {
        float sMaxX = 


        float sx, sy;           // scaling factors for x & y coordinates



        // calculating sx and sy
        sx = (float)
    }

    static UIntPoint2 GetScreenPosFromView(const UIntPoint2& screenPoint)
    {
        
    }
}

#endif