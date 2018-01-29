//
// Created by jim on 29.01.18.
//

#include <gtest/gtest.h>
#include <orbit/Transform.h>

TEST(Transform, Basic)
{
    Transform transform;

    ASSERT_DOUBLE_EQ(transform.transformation()[0][0], 1);
}
