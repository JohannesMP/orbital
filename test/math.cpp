//
// Created by jim on 29.01.18.
//

#include <orbital/common/common.h>
#include <orbital/math/elementary.h>

#include "catch/catch.hpp"
#include "common.h"

TEST_CASE("Constants", "[math]") // NOLINT
{
    CHECK(G() == Approx(6.67408e-11_df));
    CHECK(au() == Approx(149597870700_df));

    SECTION("identity matrix has valid values")
    {
        CHECK(identityMatrix()[0][0] == Approx(1));
        CHECK(identityMatrix()[0][1] == Approx(0));
        CHECK(identityMatrix()[0][2] == Approx(0));

        CHECK(identityMatrix()[1][0] == Approx(0));
        CHECK(identityMatrix()[1][1] == Approx(1));
        CHECK(identityMatrix()[1][2] == Approx(0));

        CHECK(identityMatrix()[2][0] == Approx(0));
        CHECK(identityMatrix()[2][1] == Approx(0));
        CHECK(identityMatrix()[2][2] == Approx(1));
    }
}

TEST_CASE("VectorFunctions", "[math]") // NOLINT
{
    SECTION("vector length")
    {
        CHECK(length(vec(0, 0)) == Approx(0));
        CHECK(length(vec(1, 0)) == Approx(1));
        CHECK(length(vec(0, 1)) == Approx(1));
        CHECK(length(vec(1, 1)) == Approx(std::sqrt(2)));
        CHECK(length(vec(2, 2)) == Approx(std::sqrt(8)));
        CHECK(length(vec(-1, 0)) == Approx(1));
        CHECK(length(vec(0, -1)) == Approx(1));
        CHECK(length(vec(-1, 1)) == Approx(std::sqrt(2)));
        CHECK(length(vec(2, -2)) == Approx(std::sqrt(8)));
    }

    SECTION("distance between two vectors")
    {
        CHECK(distance(vec(0, 0), vec()) == Approx(0));
        CHECK(distance(vec(1, 0), vec()) == Approx(1));
        CHECK(distance(vec(0, 1), vec()) == Approx(1));
        CHECK(distance(vec(-1, 0), vec()) == Approx(1));
        CHECK(distance(vec(0, -1), vec()) == Approx(1));
    }
}

TEST_CASE("Radians", "[math]")
{
    Radian radian{2_pi};

    SECTION("math operators")
    {
        CHECK(radian + radian == 4_pi);
        CHECK(radian - radian == 0_pi);
        CHECK(radian * 2 == 4_pi);
        CHECK(radian / 2 == 1_pi);
    }

    SECTION("trigonometric functions")
    {
        CHECK(radian.sin() == Approx{0}.margin(0.000001));
        CHECK(radian.cos() == Approx{1}.margin(0.000001));
        CHECK(radian.tan() == Approx{0}.margin(0.000001));
    }

    SECTION("inverse trigonometric functions")
    {
        CHECK(Radian::arcsin(1) == approx(0.5_pi).margin(0.000001));
        CHECK(Radian::arccos(1) == approx(0_pi).margin(0.000001));
        CHECK(Radian::arctan(1) == Approx{std::atan(1)}.margin(0.000001));
        CHECK(Radian::arctan2(2, 3) == Approx{std::atan2(2, 3)}.margin(0.000001));
    }
}
