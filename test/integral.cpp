//
// Created by jim on 28.01.18.
//

#include <gtest/gtest.h>
#include <constants.h>

TEST(Integral, NullArea)
{
    ASSERT_DOUBLE_EQ(integral(&sq, 1, 1, 100), 0);
}

TEST(Integral, SquareFunction)
{
    ASSERT_NEAR(integral(&sq, 1, 2, 100), 2.33, 0.01);
}

TEST(Integral, SquareFunctionOppositeDirection)
{
    ASSERT_NEAR(integral(&sq, 2, 1, 100), -2.33, 0.01);
}

TEST(Integral, NegatedSquareFunction)
{
    auto negativeSq = [](Decimal x) {
        return -x * x;
    };
    ASSERT_NEAR(integral(negativeSq, 1, 2, 100), -2.33, 0.01);
}

TEST(Integral, NegatedSquareFunctionOppositeDirection)
{
    auto negativeSq = [](Decimal x) {
        return -x * x;
    };
    ASSERT_NEAR(integral(negativeSq, 2, 1, 100), 2.33, 0.01);
}

TEST(Integral, SquareFunctionNegative)
{
    ASSERT_NEAR(integral(&sq, -2, -1, 100), 2.33, 0.01);
}

TEST(Integral, SquareFunctionNegativeOppositeDirection)
{
    ASSERT_NEAR(integral(&sq, -1, -2, 100), -2.33, 0.01);
}

TEST(Integral, NegatedSquareFunctionNegative)
{
    auto negativeSq = [](Decimal x) {
        return -x * x;
    };
    ASSERT_NEAR(integral(negativeSq, -2, -1, 100), -2.33, 0.01);
}

TEST(Integral, NegatedSquareFunctionNegativeOppositeDirection)
{
    auto negativeSq = [](Decimal x) {
        return -x * x;
    };
    ASSERT_NEAR(integral(negativeSq, -1, -2, 100), 2.33, 0.01);
}

TEST(Integral, SinusSelfElimination)
{
    auto sin = [](Decimal x) {
        return std::sin(x);
    };
    ASSERT_NEAR(integral(sin, 0, 2_pi, 100), 0, 0.00001);
}
