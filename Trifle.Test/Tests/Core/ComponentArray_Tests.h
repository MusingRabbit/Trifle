#pragma once

#include <trifle.h>

#include <gtest/gtest.h>

#include <cstdlib>
#include <glm/glm.hpp>

using namespace trifle;

/// @brief Populates component array with colliders for 200 entities
/// @param cmpArray Component array to be populated
void Populate_ColliderCompArray(ComponentArray<Collider>& cmpArray)
{
    srand((unsigned int)time(0));

    for (unsigned int i = 0; i < 200; i++)
    {
        Collider col;
        float x = (float)std::rand();
        float y = (float)std::rand();
        float z = (float)std::rand();
        col.SetCentre(glm::vec3(x, y, z));
        col.SetScale(1.0f);

        cmpArray.Insert(i, col);
    }
}

/// @brief Populates component array with transforms for 200 entities
/// @param cmpArray Component array to be populated
void Populate_TransformCompArray(trifle::ComponentArray<Transform>& cmpArray)
{
    for (unsigned int i = 0; i < 200; i++)
    {
        Transform tran;

        float pos_x = (float)std::rand();
        float pos_y = (float)std::rand();
        float pos_z = (float)std::rand();

        float rot_x = (float)std::rand();
        float rot_y = (float)std::rand();
        float rot_z = (float)std::rand();

        tran.SetPosition(glm::vec3(pos_x, pos_y, pos_z));
        tran.Rotate(glm::vec3(rot_x, rot_y, rot_z));
        tran.Scale(1.0f);

        cmpArray.Insert(i, tran);
    }
}

TEST(ComponentArray, Insert)
{
    unsigned int entityId = 2;
    Collider collider;

    collider.SetMaximum(glm::vec3(1, 1, 1));
    collider.SetMinimum(glm::vec3(1, 1, 1));
    collider.SetScale(glm::vec3(1, 2, 1));

    ComponentArray<Collider> cmpArray;

    cmpArray.Insert(entityId, collider);
    Collider& result = cmpArray.Get(entityId);

    ASSERT_TRUE(result.IsEqual(collider));
}

TEST(ComponentArray, Get)
{
    Collider col1;
    col1.SetMaximum(glm::vec3(1, 1, 1));
    col1.SetMinimum(glm::vec3(0, 0, 0));

    Collider col2;
    col2.SetMaximum(glm::vec3(2, 2, 2));
    col2.SetScale(glm::vec3(1, 1, 1));

    Collider col3;
    col3.SetMaximum(glm::vec3(3, 3, 3));
    col3.SetMinimum(glm::vec3(2, 2, 2));

    ComponentArray<Collider> cmpArray;

    cmpArray.Insert(1, col1);
    cmpArray.Insert(2, col2);
    cmpArray.Insert(3, col3);

    Collider& result1 = cmpArray.Get(1);
    Collider& result2 = cmpArray.Get(2);
    Collider& result3 = cmpArray.Get(3);

    ASSERT_TRUE(result1.IsEqual(col1));
    ASSERT_TRUE(result2.IsEqual(col2));
    ASSERT_TRUE(result3.IsEqual(col3));

    ASSERT_FALSE(result1.IsEqual(col2));
    ASSERT_FALSE(result1.IsEqual(col3));
    ASSERT_FALSE(result3.IsEqual(col1));
    ASSERT_FALSE(result3.IsEqual(col2));
}

TEST(ComponentArray, Remove)
{
    ComponentArray<Collider> cmpArray;
    Populate_ColliderCompArray(cmpArray);

    Collider& colBeforeRemove = cmpArray.Get(100);

    cmpArray.Remove(100);

    ASSERT_DEATH(cmpArray.Get(100), "Retrieving non-existent component.");
}

TEST(ComponentArray, EntityDestroyed)
{
    ComponentArray<Transform> cmpArray;
    Populate_TransformCompArray(cmpArray);

    Transform& colBeforeRemove = cmpArray.Get(100);

    cmpArray.EntityDestroyed(100);

    ASSERT_DEATH(cmpArray.Get(100), "Retrieving non-existent component.");
}

TEST(ComponentArray, Insert_Duplicate_Component_Test)
{
    ComponentArray<Transform> cmpArray;
    Populate_TransformCompArray(cmpArray);

    Transform& orig = cmpArray.Get(10); // Ensure that transform does indeed exist.

    Transform newTransform;
    newTransform.SetPosition(glm::vec3(999, 999, 999));
    newTransform.Rotate(glm::vec3(999, 999, 999));
    newTransform.Scale(999);

    ASSERT_DEATH(cmpArray.Insert(10, newTransform), "Duplicate addition of existing component. A component of the same "
                                                    "type has already been mapped to this entity.");
}

TEST(ComponentArray, Get_NotFound_Test)
{
    ComponentArray<Collider> cmpArray;

    Populate_ColliderCompArray(cmpArray);

    ASSERT_DEATH(cmpArray.Get(201), "Retrieving non-existent component."); // Index not set
}
