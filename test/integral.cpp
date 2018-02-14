//
// Created by jim on 28.01.18.
//

#include "catch/catch.hpp"
#include "common.h"
#include <orbital/common/common.h>
#include <orbital/math/Radian.h>
#include <orbital/math/elementary.h>

TEST_CASE("Integral", "[math]") // NOLINT
{

    SECTION("null area due same bounds results in 0")
    {
        CHECK(integral(1_df, 1_df, 100_df, &sq) == Approx(0_df));
    }

    SECTION("integrating square function")
    {
        CHECK(integral(1_df, 2_df, 100_df, &sq) == Approx(2.33_df).margin(0.01_df));
    }

    SECTION("integrating square function in opposite direction")
    {
        CHECK(integral(2_df, 1_df, 100_df, &sq) == Approx(-2.33_df).margin(0.01_df));
    }

    SECTION("integrating negated square function")
    {
        auto negativeSq = [](Decimal x) {
            return -x * x;
        };
        CHECK(integral(1_df, 2_df, 100_df, negativeSq) == Approx(-2.33_df).margin(0.01_df));
    }

    SECTION("integrating negated square function in opposite direction")
    {
        auto negativeSq = [](Decimal x) {
            return -x * x;
        };
        CHECK(integral(2_df, 1_df, 100_df, negativeSq) == Approx(2.33_df).margin(0.01_df));
    }

    SECTION("integrating square function on negative x-axis side")
    {
        CHECK(integral(-2_df, -1_df, 100_df, &sq) == Approx(2.33_df).margin(0.01_df));
    }

    SECTION("integrating square function on negative x-axis side in opposite direction")
    {
        CHECK(integral(-1_df, -2_df, 100_df, &sq) == Approx(-2.33_df).margin(0.01_df));
    }

    SECTION("integrating negated square function on negative x-axis side")
    {
        auto negativeSq = [](Decimal x) {
            return -x * x;
        };
        CHECK(integral(-2_df, -1_df, 100_df, negativeSq) == Approx(-2.33_df).margin(0.01_df));
    }

    SECTION("integrating negated square function on negative x-axis side in opposite direction")
    {
        auto negativeSq = [](Decimal x) {
            return -x * x;
        };
        CHECK(integral(-1_df, -2_df, 100_df, negativeSq) == Approx(2.33_df).margin(0.01_df));
    }

    SECTION("integrating sinus results in 0 due to self-elimination")
    {
        CHECK(integral(0_pi, 2_pi, 10000_df, &Radian::sin) == Approx(0).margin(0.00001));
    }

}
