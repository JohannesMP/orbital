//
// Created by jim on 29.01.18.
//


#include <gtest/gtest.h>
#include <orbit/constants.h>

TEST(Constants, Validity)
{
    ASSERT_DOUBLE_EQ(G, 6.67408e-11_df);
    ASSERT_DOUBLE_EQ(AU, 149597870700_df);

    ASSERT_DOUBLE_EQ(S_PER_MIN, 60_df);
    ASSERT_DOUBLE_EQ(S_PER_HOUR, 3600_df);
    ASSERT_DOUBLE_EQ(S_PER_DAY, 86400_df);
    ASSERT_DOUBLE_EQ(S_PER_MONTH, 86400_df * 30.436875_df);
    ASSERT_DOUBLE_EQ(S_PER_YEAR, 86400_df * 365.24219052_df);
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

TEST(Constants, IdentityMatrix)
{
    ASSERT_DOUBLE_EQ(IDENTITY_MATRIX[0][0], 1);
    ASSERT_DOUBLE_EQ(IDENTITY_MATRIX[0][1], 0);
    ASSERT_DOUBLE_EQ(IDENTITY_MATRIX[0][2], 0);

    ASSERT_DOUBLE_EQ(IDENTITY_MATRIX[1][0], 0);
    ASSERT_DOUBLE_EQ(IDENTITY_MATRIX[1][1], 1);
    ASSERT_DOUBLE_EQ(IDENTITY_MATRIX[1][2], 0);

    ASSERT_DOUBLE_EQ(IDENTITY_MATRIX[2][0], 0);
    ASSERT_DOUBLE_EQ(IDENTITY_MATRIX[2][1], 0);
    ASSERT_DOUBLE_EQ(IDENTITY_MATRIX[2][2], 1);
}
