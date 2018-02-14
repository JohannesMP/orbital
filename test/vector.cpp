//
// Created by jim on 14.02.18.
//

#include "common.h"

#include <orbital/math/Vector.h>

TEST_CASE("Vector", "[math]")
{

    SECTION("element access")
    {
        Vector<Decimal, 4> vn{1, 2, 3};
        CHECK(vn[0] == 1);
        CHECK(vn[1] == 2);
        CHECK(vn[2] == 3);
        CHECK(vn[3] == 0);

        Vector2d<Decimal> v2{5, 6};
        CHECK(v2.x() == 5);
        CHECK(v2.y() == 6);

        Vector3d<Decimal> v3{7, 9, 1};
        CHECK(v3.x() == 7);
        CHECK(v3.y() == 9);
        CHECK(v3.z() == 1);
    }

    SECTION("add")
    {
        Vector2d<Decimal> v0{3, 4};
        Vector2d<Decimal> v1{7, 8};
        auto v2 = v0 + v1;

        CHECK(v2 == Vector2d<Decimal>{10, 12});
    }

    SECTION("subtract")
    {
        Vector2d<Decimal> v0{5, 6};
        Vector2d<Decimal> v1{2, 1};
        auto v2 = v0 - v1;

        CHECK(v2 == Vector2d<Decimal>{3, 5});
    }
}
