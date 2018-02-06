//
// Created by jim on 29.01.18.
//


#include <gtest/gtest.h>
#include <orbital/constants.h>

TEST(Constants, Validity)
{
    ASSERT_DOUBLE_EQ(G(), 6.67408e-11_df);
    ASSERT_DOUBLE_EQ(au(), 149597870700_df);
}

TEST(VectorFunctions, Length)
{
    ASSERT_DOUBLE_EQ(length(vec(0, 0)), 0);
    ASSERT_DOUBLE_EQ(length(vec(1, 0)), 1);
    ASSERT_DOUBLE_EQ(length(vec(0, 1)), 1);
    ASSERT_DOUBLE_EQ(length(vec(1, 1)), std::sqrt(2));
    ASSERT_DOUBLE_EQ(length(vec(2, 2)), std::sqrt(8));
    ASSERT_DOUBLE_EQ(length(vec(-1, 0)), 1);
    ASSERT_DOUBLE_EQ(length(vec(0, -1)), 1);
    ASSERT_DOUBLE_EQ(length(vec(-1, 1)), std::sqrt(2));
    ASSERT_DOUBLE_EQ(length(vec(2, -2)), std::sqrt(8));
}

TEST(VectorFunctions, Distance)
{
    ASSERT_DOUBLE_EQ(distance(vec(0, 0), vec()), 0);
    ASSERT_DOUBLE_EQ(distance(vec(1, 0), vec()), 1);
    ASSERT_DOUBLE_EQ(distance(vec(0, 1), vec()), 1);
    ASSERT_DOUBLE_EQ(distance(vec(-1, 0), vec()), 1);
    ASSERT_DOUBLE_EQ(distance(vec(0, -1), vec()), 1);
}

TEST(Constants, IdentityMatrix) // NOLINT
{
    ASSERT_DOUBLE_EQ(identityMatrix()[0][0], 1);
    ASSERT_DOUBLE_EQ(identityMatrix()[0][1], 0);
    ASSERT_DOUBLE_EQ(identityMatrix()[0][2], 0);

    ASSERT_DOUBLE_EQ(identityMatrix()[1][0], 0);
    ASSERT_DOUBLE_EQ(identityMatrix()[1][1], 1);
    ASSERT_DOUBLE_EQ(identityMatrix()[1][2], 0);

    ASSERT_DOUBLE_EQ(identityMatrix()[2][0], 0);
    ASSERT_DOUBLE_EQ(identityMatrix()[2][1], 0);
    ASSERT_DOUBLE_EQ(identityMatrix()[2][2], 1);
}
