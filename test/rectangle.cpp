//
// Created by jim on 27.01.18.
//

#include "catch/catch.hpp"
#include <orbital/math/Rectangle.h>

TEST_CASE("Rectangle", "[math]") // NOLINT
{

    SECTION("proper construction with positive extent")
    {
        Rectangle rect{{1, 2}, 3, 4};

        CHECK(rect.left() == Approx(1));
        CHECK(rect.right() == Approx(4));
        CHECK(rect.top() == Approx(6));
        CHECK(rect.bottom() == Approx(2));

        CHECK(rect.topLeft().x == Approx(1));
        CHECK(rect.topLeft().y == Approx(6));
        CHECK(rect.topRight().x == Approx(4));
        CHECK(rect.topRight().y == Approx(6));
        CHECK(rect.bottomLeft().x == Approx(1));
        CHECK(rect.bottomLeft().y == Approx(2));
        CHECK(rect.bottomRight().x == Approx(4));
        CHECK(rect.bottomRight().y == Approx(2));

        CHECK(rect.topCenter().x == Approx(2.5));
        CHECK(rect.topCenter().y == Approx(6));
        CHECK(rect.bottomCenter().x == Approx(2.5));
        CHECK(rect.bottomCenter().y == Approx(2));
        CHECK(rect.leftCenter().x == Approx(1));
        CHECK(rect.leftCenter().y == Approx(4));
        CHECK(rect.rightCenter().x == Approx(4));
        CHECK(rect.rightCenter().y == Approx(4));
        CHECK(rect.center().x == Approx(2.5));
        CHECK(rect.center().y == Approx(4));
    }

    SECTION("proper construction with negative extent")
    {
        Rectangle rect{{4, 6}, -3, -4};

        CHECK(rect.left() == Approx(1));
        CHECK(rect.right() == Approx(4));
        CHECK(rect.top() == Approx(6));
        CHECK(rect.bottom() == Approx(2));

        CHECK(rect.topLeft().x == Approx(1));
        CHECK(rect.topLeft().y == Approx(6));
        CHECK(rect.topRight().x == Approx(4));
        CHECK(rect.topRight().y == Approx(6));
        CHECK(rect.bottomLeft().x == Approx(1));
        CHECK(rect.bottomLeft().y == Approx(2));
        CHECK(rect.bottomRight().x == Approx(4));
        CHECK(rect.bottomRight().y == Approx(2));

        CHECK(rect.topCenter().x == Approx(2.5));
        CHECK(rect.topCenter().y == Approx(6));
        CHECK(rect.bottomCenter().x == Approx(2.5));
        CHECK(rect.bottomCenter().y == Approx(2));
        CHECK(rect.leftCenter().x == Approx(1));
        CHECK(rect.leftCenter().y == Approx(4));
        CHECK(rect.rightCenter().x == Approx(4));
        CHECK(rect.rightCenter().y == Approx(4));
        CHECK(rect.center().x == Approx(2.5));
        CHECK(rect.center().y == Approx(4));
    }

    SECTION("proper construction from two points")
    {
        Rectangle rect{{1, 2}, {4, 6}};

        CHECK(rect.left() == Approx(1));
        CHECK(rect.right() == Approx(4));
        CHECK(rect.top() == Approx(6));
        CHECK(rect.bottom() == Approx(2));

        CHECK(rect.topLeft().x == Approx(1));
        CHECK(rect.topLeft().y == Approx(6));
        CHECK(rect.topRight().x == Approx(4));
        CHECK(rect.topRight().y == Approx(6));
        CHECK(rect.bottomLeft().x == Approx(1));
        CHECK(rect.bottomLeft().y == Approx(2));
        CHECK(rect.bottomRight().x == Approx(4));
        CHECK(rect.bottomRight().y == Approx(2));

        CHECK(rect.topCenter().x == Approx(2.5));
        CHECK(rect.topCenter().y == Approx(6));
        CHECK(rect.bottomCenter().x == Approx(2.5));
        CHECK(rect.bottomCenter().y == Approx(2));
        CHECK(rect.leftCenter().x == Approx(1));
        CHECK(rect.leftCenter().y == Approx(4));
        CHECK(rect.rightCenter().x == Approx(4));
        CHECK(rect.rightCenter().y == Approx(4));
        CHECK(rect.center().x == Approx(2.5));
        CHECK(rect.center().y == Approx(4));
    }

    SECTION("proper construction from two flipped points")
    {
        Rectangle rect{{4, 6}, {1, 2}};

        CHECK(rect.left() == Approx(1));
        CHECK(rect.right() == Approx(4));
        CHECK(rect.top() == Approx(6));
        CHECK(rect.bottom() == Approx(2));

        CHECK(rect.topLeft().x == Approx(1));
        CHECK(rect.topLeft().y == Approx(6));
        CHECK(rect.topRight().x == Approx(4));
        CHECK(rect.topRight().y == Approx(6));
        CHECK(rect.bottomLeft().x == Approx(1));
        CHECK(rect.bottomLeft().y == Approx(2));
        CHECK(rect.bottomRight().x == Approx(4));
        CHECK(rect.bottomRight().y == Approx(2));

        CHECK(rect.topCenter().x == Approx(2.5));
        CHECK(rect.topCenter().y == Approx(6));
        CHECK(rect.bottomCenter().x == Approx(2.5));
        CHECK(rect.bottomCenter().y == Approx(2));
        CHECK(rect.leftCenter().x == Approx(1));
        CHECK(rect.leftCenter().y == Approx(4));
        CHECK(rect.rightCenter().x == Approx(4));
        CHECK(rect.rightCenter().y == Approx(4));
        CHECK(rect.center().x == Approx(2.5));
        CHECK(rect.center().y == Approx(4));
    }

    SECTION("extent")
    {
        Rectangle a{{1, 2}, {4, 3}};

        CHECK(a.extent().x == Approx(3));
        CHECK(a.extent().y == Approx(1));
    }

    SECTION("conjunction")
    {
        Rectangle a{{}, 4, 3};
        Rectangle b{{2, 1}, 3, 3};

        CHECK(a.conjunction(b).bottom() == Approx(1));
        CHECK(a.conjunction(b).left() == Approx(2));
        CHECK(a.conjunction(b).top() == Approx(3));
        CHECK(a.conjunction(b).right() == Approx(4));
    }

    SECTION("conjunction but no overlap")
    {
        Rectangle a{{}, 4, 3};

        Rectangle above{{2, 3}, 3, 3};
        CHECK(a.conjunction(above).bottom() == Approx(Rectangle::zeroRectangle().bottom()));
        CHECK(a.conjunction(above).left() == Approx(Rectangle::zeroRectangle().left()));
        CHECK(a.conjunction(above).top() == Approx(Rectangle::zeroRectangle().top()));
        CHECK(a.conjunction(above).right() == Approx(Rectangle::zeroRectangle().right()));

        Rectangle below{{2, -3}, 3, 3};
        CHECK(a.conjunction(below).bottom() == Approx(Rectangle::zeroRectangle().bottom()));
        CHECK(a.conjunction(below).left() == Approx(Rectangle::zeroRectangle().left()));
        CHECK(a.conjunction(below).top() == Approx(Rectangle::zeroRectangle().top()));
        CHECK(a.conjunction(below).right() == Approx(Rectangle::zeroRectangle().right()));

        Rectangle right{{2, 3}, 4, 3};
        CHECK(a.conjunction(right).bottom() == Approx(Rectangle::zeroRectangle().bottom()));
        CHECK(a.conjunction(right).left() == Approx(Rectangle::zeroRectangle().left()));
        CHECK(a.conjunction(right).top() == Approx(Rectangle::zeroRectangle().top()));
        CHECK(a.conjunction(right).right() == Approx(Rectangle::zeroRectangle().right()));

        Rectangle left{{2, 3}, -3, 3};
        CHECK(a.conjunction(left).bottom() == Approx(Rectangle::zeroRectangle().bottom()));
        CHECK(a.conjunction(left).left() == Approx(Rectangle::zeroRectangle().left()));
        CHECK(a.conjunction(left).top() == Approx(Rectangle::zeroRectangle().top()));
        CHECK(a.conjunction(left).right() == Approx(Rectangle::zeroRectangle().right()));
    }

    SECTION("contains a transformed point")
    {
        Rectangle rect{{}, 1, 1};
        Transform t;
        t.scale(0.5);

        CHECK_FALSE(rect.containsTransformed(t, {1, 1}));
        CHECK(rect.containsTransformed(t, {0.5, 0.5}));
    }

}
