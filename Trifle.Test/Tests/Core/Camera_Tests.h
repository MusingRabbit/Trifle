#pragma once

#include <cstdlib>
#include <glm/glm.hpp>
#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <functional>

#include "../../GTestHelper.h"

#include <trifle.h>

using namespace tfl;

TEST(Camera, View)
{
    GTestHelper::CreateEntityManager();

    Camera cam;
    cam.SetPosition({0.0f, 0.0f, 0.0f});
    cam.SetTarget({0.0f, 0.0f, 5.0f});

    Transform camTrans = cam.GetComponent<Transform>();

    glm::vec4 wPos = {camTrans.GetPosition(), 1.0f};
    glm::vec4 vPos = cam.GetViewMatrix() * wPos;
    glm::vec4 cPos = VectorHelper::GetClipSpace(vPos, 1, 10, 300, 300);
}