//
// Created by jim on 28.01.18.
//

#include <gtest/gtest.h>
#include <orbital/common/common.h>
#include <orbital/math/Radian.h>
#include <orbital/math/elementary.h>

TEST(Integral, NullArea) // NOLINT
{
    ASSERT_DOUBLE_EQ(integral(1_df, 1_df, 100_df, &sq), 0_df);
}

TEST(Integral, SquareFunction) // NOLINT
{
    ASSERT_NEAR(integral(1_df, 2_df, 100_df, &sq), 2.33_df, 0.01_df);
}

TEST(Integral, SquareFunctionOppositeDirection) // NOLINT
{
    ASSERT_NEAR(integral(2_df, 1_df, 100_df, &sq), -2.33_df, 0.01_df);
}

TEST(Integral, NegatedSquareFunction) // NOLINT
{
    auto negativeSq = [](Decimal x) {
        return -x * x;
    };
    ASSERT_NEAR(integral(1_df, 2_df, 100_df, negativeSq), -2.33_df, 0.01_df);
}

TEST(Integral, NegatedSquareFunctionOppositeDirection) // NOLINT
{
    auto negativeSq = [](Decimal x) {
        return -x * x;
    };
    ASSERT_NEAR(integral(2_df, 1_df, 100_df, negativeSq), 2.33_df, 0.01_df);
}

TEST(Integral, SquareFunctionNegative) // NOLINT
{
    ASSERT_NEAR(integral(-2_df, -1_df, 100_df, &sq), 2.33_df, 0.01_df);
}

TEST(Integral, SquareFunctionNegativeOppositeDirection) // NOLINT
{
    ASSERT_NEAR(integral(-1_df, -2_df, 100_df, &sq), -2.33_df, 0.01_df);
}

TEST(Integral, NegatedSquareFunctionNegative) // NOLINT
{
    auto negativeSq = [](Decimal x) {
        return -x * x;
    };
    ASSERT_NEAR(integral(-2_df, -1_df, 100_df, negativeSq), -2.33_df, 0.01_df);
}

TEST(Integral, NegatedSquareFunctionNegativeOppositeDirection) // NOLINT
{
    auto negativeSq = [](Decimal x) {
        return -x * x;
    };
    ASSERT_NEAR(integral(-1_df, -2_df, 100_df, negativeSq), 2.33_df, 0.01_df);
}

TEST(Integral, SinusSelfElimination) // NOLINT
{
    ASSERT_NEAR(integral(0_pi, 2_pi, 100_pi, &Radian::sin).getRaw(), 0, 0.00001);
}
