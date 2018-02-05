//
// Created by jim on 05.02.18.
//

#include <gtest/gtest.h>
#include <orbital/DynamicArray.h>
#include <orbital/constants.h>

TEST(DynamicArray, Basic)
{
    DynamicArray<Decimal, 1> dy;

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

TEST(DynamicArray, Iterators)
{
    DynamicArray<Decimal, 5> dy;

    ASSERT_DOUBLE_EQ(dy.push_back(3), 3);
    ASSERT_DOUBLE_EQ(*dy.begin(), 3);
    ASSERT_EQ(std::distance(dy.begin(), dy.end()), 1);
}

