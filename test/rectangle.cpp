//
// Created by jim on 27.01.18.
//

#include <gtest/gtest.h>
#include <orbital/Rectangle.h>

TEST(Rectangle, ProperConstructionWithPositiveExtent) // NOLINT
{
    Rectangle rect{{1, 2}, 3, 4};

    ASSERT_DOUBLE_EQ(rect.left(), 1);
    ASSERT_DOUBLE_EQ(rect.right(), 4);
    ASSERT_DOUBLE_EQ(rect.top(), 6);
    ASSERT_DOUBLE_EQ(rect.bottom(), 2);

    ASSERT_DOUBLE_EQ(rect.topLeft().x, 1);
    ASSERT_DOUBLE_EQ(rect.topLeft().y, 6);
    ASSERT_DOUBLE_EQ(rect.topRight().x, 4);
    ASSERT_DOUBLE_EQ(rect.topRight().y, 6);
    ASSERT_DOUBLE_EQ(rect.bottomLeft().x, 1);
    ASSERT_DOUBLE_EQ(rect.bottomLeft().y, 2);
    ASSERT_DOUBLE_EQ(rect.bottomRight().x, 4);
    ASSERT_DOUBLE_EQ(rect.bottomRight().y, 2);

    ASSERT_DOUBLE_EQ(rect.topCenter().x, 2.5);
    ASSERT_DOUBLE_EQ(rect.topCenter().y, 6);
    ASSERT_DOUBLE_EQ(rect.bottomCenter().x, 2.5);
    ASSERT_DOUBLE_EQ(rect.bottomCenter().y, 2);
    ASSERT_DOUBLE_EQ(rect.leftCenter().x, 1);
    ASSERT_DOUBLE_EQ(rect.leftCenter().y, 4);
    ASSERT_DOUBLE_EQ(rect.rightCenter().x, 4);
    ASSERT_DOUBLE_EQ(rect.rightCenter().y, 4);
    ASSERT_DOUBLE_EQ(rect.center().x, 2.5);
    ASSERT_DOUBLE_EQ(rect.center().y, 4);
}

TEST(Rectangle, ProperConstructionWithNegativeExtent) // NOLINT
{
    Rectangle rect{{4, 6}, -3, -4};

    ASSERT_DOUBLE_EQ(rect.left(), 1);
    ASSERT_DOUBLE_EQ(rect.right(), 4);
    ASSERT_DOUBLE_EQ(rect.top(), 6);
    ASSERT_DOUBLE_EQ(rect.bottom(), 2);

    ASSERT_DOUBLE_EQ(rect.topLeft().x, 1);
    ASSERT_DOUBLE_EQ(rect.topLeft().y, 6);
    ASSERT_DOUBLE_EQ(rect.topRight().x, 4);
    ASSERT_DOUBLE_EQ(rect.topRight().y, 6);
    ASSERT_DOUBLE_EQ(rect.bottomLeft().x, 1);
    ASSERT_DOUBLE_EQ(rect.bottomLeft().y, 2);
    ASSERT_DOUBLE_EQ(rect.bottomRight().x, 4);
    ASSERT_DOUBLE_EQ(rect.bottomRight().y, 2);

    ASSERT_DOUBLE_EQ(rect.topCenter().x, 2.5);
    ASSERT_DOUBLE_EQ(rect.topCenter().y, 6);
    ASSERT_DOUBLE_EQ(rect.bottomCenter().x, 2.5);
    ASSERT_DOUBLE_EQ(rect.bottomCenter().y, 2);
    ASSERT_DOUBLE_EQ(rect.leftCenter().x, 1);
    ASSERT_DOUBLE_EQ(rect.leftCenter().y, 4);
    ASSERT_DOUBLE_EQ(rect.rightCenter().x, 4);
    ASSERT_DOUBLE_EQ(rect.rightCenter().y, 4);
    ASSERT_DOUBLE_EQ(rect.center().x, 2.5);
    ASSERT_DOUBLE_EQ(rect.center().y, 4);
}

TEST(Rectangle, ProperConstructionFromTwoPoints) // NOLINT
{
    Rectangle rect{{1, 2}, {4, 6}};

    ASSERT_DOUBLE_EQ(rect.left(), 1);
    ASSERT_DOUBLE_EQ(rect.right(), 4);
    ASSERT_DOUBLE_EQ(rect.top(), 6);
    ASSERT_DOUBLE_EQ(rect.bottom(), 2);

    ASSERT_DOUBLE_EQ(rect.topLeft().x, 1);
    ASSERT_DOUBLE_EQ(rect.topLeft().y, 6);
    ASSERT_DOUBLE_EQ(rect.topRight().x, 4);
    ASSERT_DOUBLE_EQ(rect.topRight().y, 6);
    ASSERT_DOUBLE_EQ(rect.bottomLeft().x, 1);
    ASSERT_DOUBLE_EQ(rect.bottomLeft().y, 2);
    ASSERT_DOUBLE_EQ(rect.bottomRight().x, 4);
    ASSERT_DOUBLE_EQ(rect.bottomRight().y, 2);

    ASSERT_DOUBLE_EQ(rect.topCenter().x, 2.5);
    ASSERT_DOUBLE_EQ(rect.topCenter().y, 6);
    ASSERT_DOUBLE_EQ(rect.bottomCenter().x, 2.5);
    ASSERT_DOUBLE_EQ(rect.bottomCenter().y, 2);
    ASSERT_DOUBLE_EQ(rect.leftCenter().x, 1);
    ASSERT_DOUBLE_EQ(rect.leftCenter().y, 4);
    ASSERT_DOUBLE_EQ(rect.rightCenter().x, 4);
    ASSERT_DOUBLE_EQ(rect.rightCenter().y, 4);
    ASSERT_DOUBLE_EQ(rect.center().x, 2.5);
    ASSERT_DOUBLE_EQ(rect.center().y, 4);
}

TEST(Rectangle, ProperConstructionFromTwoPointsFlipped) // NOLINT
{
    Rectangle rect{{4, 6}, {1, 2}};

    ASSERT_DOUBLE_EQ(rect.left(), 1);
    ASSERT_DOUBLE_EQ(rect.right(), 4);
    ASSERT_DOUBLE_EQ(rect.top(), 6);
    ASSERT_DOUBLE_EQ(rect.bottom(), 2);

    ASSERT_DOUBLE_EQ(rect.topLeft().x, 1);
    ASSERT_DOUBLE_EQ(rect.topLeft().y, 6);
    ASSERT_DOUBLE_EQ(rect.topRight().x, 4);
    ASSERT_DOUBLE_EQ(rect.topRight().y, 6);
    ASSERT_DOUBLE_EQ(rect.bottomLeft().x, 1);
    ASSERT_DOUBLE_EQ(rect.bottomLeft().y, 2);
    ASSERT_DOUBLE_EQ(rect.bottomRight().x, 4);
    ASSERT_DOUBLE_EQ(rect.bottomRight().y, 2);

    ASSERT_DOUBLE_EQ(rect.topCenter().x, 2.5);
    ASSERT_DOUBLE_EQ(rect.topCenter().y, 6);
    ASSERT_DOUBLE_EQ(rect.bottomCenter().x, 2.5);
    ASSERT_DOUBLE_EQ(rect.bottomCenter().y, 2);
    ASSERT_DOUBLE_EQ(rect.leftCenter().x, 1);
    ASSERT_DOUBLE_EQ(rect.leftCenter().y, 4);
    ASSERT_DOUBLE_EQ(rect.rightCenter().x, 4);
    ASSERT_DOUBLE_EQ(rect.rightCenter().y, 4);
    ASSERT_DOUBLE_EQ(rect.center().x, 2.5);
    ASSERT_DOUBLE_EQ(rect.center().y, 4);
}

TEST(Rectangle, Extent) // NOLINT
{
    Rectangle a{{1, 2}, {4, 3}};

    ASSERT_DOUBLE_EQ(a.extent().x, 3);
    ASSERT_DOUBLE_EQ(a.extent().y, 1);
}

TEST(Rectangle, Conjunction) // NOLINT
{
    Rectangle a{{}, 4, 3};
    Rectangle b{{2, 1}, 3, 3};

    ASSERT_DOUBLE_EQ(a.conjunction(b).bottom(), 1);
    ASSERT_DOUBLE_EQ(a.conjunction(b).left(), 2);
    ASSERT_DOUBLE_EQ(a.conjunction(b).top(), 3);
    ASSERT_DOUBLE_EQ(a.conjunction(b).right(), 4);
}

TEST(Rectangle, ConjunctionNonOverlapping) // NOLINT
{
    Rectangle a{{}, 4, 3};

    Rectangle above{{2, 3}, 3, 3};
    ASSERT_DOUBLE_EQ(a.conjunction(above).bottom(), Rectangle::zeroRectangle().bottom());
    ASSERT_DOUBLE_EQ(a.conjunction(above).left(), Rectangle::zeroRectangle().left());
    ASSERT_DOUBLE_EQ(a.conjunction(above).top(), Rectangle::zeroRectangle().top());
    ASSERT_DOUBLE_EQ(a.conjunction(above).right(), Rectangle::zeroRectangle().right());

    Rectangle below{{2, -3}, 3, 3};
    ASSERT_DOUBLE_EQ(a.conjunction(below).bottom(), Rectangle::zeroRectangle().bottom());
    ASSERT_DOUBLE_EQ(a.conjunction(below).left(), Rectangle::zeroRectangle().left());
    ASSERT_DOUBLE_EQ(a.conjunction(below).top(), Rectangle::zeroRectangle().top());
    ASSERT_DOUBLE_EQ(a.conjunction(below).right(), Rectangle::zeroRectangle().right());

    Rectangle right{{2, 3}, 4, 3};
    ASSERT_DOUBLE_EQ(a.conjunction(right).bottom(), Rectangle::zeroRectangle().bottom());
    ASSERT_DOUBLE_EQ(a.conjunction(right).left(), Rectangle::zeroRectangle().left());
    ASSERT_DOUBLE_EQ(a.conjunction(right).top(), Rectangle::zeroRectangle().top());
    ASSERT_DOUBLE_EQ(a.conjunction(right).right(), Rectangle::zeroRectangle().right());

    Rectangle left{{2, 3}, -3, 3};
    ASSERT_DOUBLE_EQ(a.conjunction(left).bottom(), Rectangle::zeroRectangle().bottom());
    ASSERT_DOUBLE_EQ(a.conjunction(left).left(), Rectangle::zeroRectangle().left());
    ASSERT_DOUBLE_EQ(a.conjunction(left).top(), Rectangle::zeroRectangle().top());
    ASSERT_DOUBLE_EQ(a.conjunction(left).right(), Rectangle::zeroRectangle().right());
}

TEST(Rectangle, ContainsTransformed) // NOLINT
{
    Rectangle rect{{}, 1, 1};
    Transform t;
    t.scale(0.5);

    ASSERT_FALSE(rect.containsTransformed(t, {1, 1}));
    ASSERT_TRUE(rect.containsTransformed(t, {0.5, 0.5}));
}
