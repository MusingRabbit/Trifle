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

bool OnPositionChanged_Fired = false;

TEST(Camera, OnTransformedChanged)
{
    OnPositionChanged_Fired = false;

    Entity::Init(GTestHelper::CreateEntityManager());

    Camera camera;

    camera.Register();
    camera.Init(1.0f, 1.0f, 1000.0f);

    Transform& transform = camera.GetComponent<Transform>();

    std::function<void(EventArgs&)> func = [](const EventArgs& e) { OnPositionChanged_Fired = true; };
    transform.OnPositionChanged.Subscribe(func);

    transform.SetPosition(glm::vec3(1, 3, 5));

    ASSERT_TRUE(OnPositionChanged_Fired);
}

TEST(Camera, Dev_DeleteMe_Test)
{
    Entity::Init(GTestHelper::CreateEntityManager());

    Camera camera;

    camera.Register();
    camera.Init(1.0f, 1.0f, 10.0f);

    Transform& camTransform = camera.GetComponent<Transform>();
    camTransform.SetPosition(glm::vec3(5, 5, 0));

    camera.SetTarget({5, 5, 5});
}