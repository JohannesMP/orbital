//
// Created by jim on 05.02.18.
//

#include <gtest/gtest.h>
#include <orbital/common/DynamicArray.h>
#include <orbital/common/common.h>
#include <orbital/math/Radian.h>

TEST(DynamicArray, Basic) // NOLINT
{
    DynamicArray<Radian, 1> dy;

    ASSERT_EQ(dy.size(), 0);
    ASSERT_EQ(dy.capacity(), 1);

    dy.push_back(1_pi);

    ASSERT_EQ(dy.size(), 1);
    ASSERT_EQ(dy.capacity(), 1);

    // Capacity would be exceeded:
    ASSERT_ANY_THROW(dy.push_back(1_pi));
    ASSERT_EQ(dy.size(), 1);
    ASSERT_EQ(dy.capacity(), 1);
}

TEST(DynamicArray, Iterators) // NOLINT
{
    DynamicArray<Decimal, 5> dy;
    auto const &constantDy = dy;

    ASSERT_DOUBLE_EQ(dy.push_back(3), 3);

    ASSERT_DOUBLE_EQ(*dy.begin(), 3);
    ASSERT_DOUBLE_EQ(*constantDy.begin(), 3);

    ASSERT_EQ(std::distance(dy.begin(), dy.end()), 1);
    ASSERT_EQ(std::distance(constantDy.begin(), constantDy.end()), 1);
}

TEST(DynamicArray, FrontBack) // NOLINT
{
    DynamicArray<Decimal, 5> dy;
    auto const &constantDy = dy;

    dy.push_back(3);

    ASSERT_EQ(dy.front(), 3);
    ASSERT_EQ(constantDy.front(), 3);
    ASSERT_EQ(dy.back(), 3);
    ASSERT_EQ(constantDy.back(), 3);

    dy.push_back(5);

    ASSERT_EQ(dy.front(), 3);
    ASSERT_EQ(constantDy.front(), 3);
    ASSERT_EQ(dy.back(), 5);
    ASSERT_EQ(constantDy.back(), 5);
}

