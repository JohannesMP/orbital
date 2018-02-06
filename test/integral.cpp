//
// Created by jim on 28.01.18.
//

#include <gtest/gtest.h>
#include <orbital/constants.h>

TEST(Integral, NullArea) // NOLINT
{
    ASSERT_DOUBLE_EQ(integral(&sq, 1, 1, 100), 0);
}

TEST(Integral, SquareFunction) // NOLINT
{
    ASSERT_NEAR(integral(&sq, 1, 2, 100), 2.33, 0.01);
}

TEST(Integral, SquareFunctionOppositeDirection) // NOLINT
{
    ASSERT_NEAR(integral(&sq, 2, 1, 100), -2.33, 0.01);
}

TEST(Integral, NegatedSquareFunction) // NOLINT
{
    auto negativeSq = [](Decimal x) {
        return -x * x;
    };
    ASSERT_NEAR(integral(negativeSq, 1, 2, 100), -2.33, 0.01);
}

TEST(Integral, NegatedSquareFunctionOppositeDirection) // NOLINT
{
    auto negativeSq = [](Decimal x) {
        return -x * x;
    };
    ASSERT_NEAR(integral(negativeSq, 2, 1, 100), 2.33, 0.01);
}

TEST(Integral, SquareFunctionNegative) // NOLINT
{
    ASSERT_NEAR(integral(&sq, -2, -1, 100), 2.33, 0.01);
}

TEST(Integral, SquareFunctionNegativeOppositeDirection) // NOLINT
{
    ASSERT_NEAR(integral(&sq, -1, -2, 100), -2.33, 0.01);
}

TEST(Integral, NegatedSquareFunctionNegative) // NOLINT
{
    auto negativeSq = [](Decimal x) {
        return -x * x;
    };
    ASSERT_NEAR(integral(negativeSq, -2, -1, 100), -2.33, 0.01);
}

TEST(Integral, NegatedSquareFunctionNegativeOppositeDirection) // NOLINT
{
    auto negativeSq = [](Decimal x) {
        return -x * x;
    };
    ASSERT_NEAR(integral(negativeSq, -1, -2, 100), 2.33, 0.01);
}

TEST(Integral, SinusSelfElimination) // NOLINT
{
    auto sin = [](Decimal x) {
        return std::sin(x);
    };
    ASSERT_NEAR(integral(sin, 0, 2_pi, 100), 0, 0.00001);
}
