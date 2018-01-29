//
// Created by jim on 27.01.18.
//

#include "common.h"
#include <orbit/Rectangle.h>

TEST(Rectangle, ProperConstructionWithPositiveExtent)
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

TEST(Rectangle, ProperConstructionWithNegativeExtent)
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

TEST(Rectangle, ProperConstructionFromTwoPoints)
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

TEST(Rectangle, ProperConstructionFromTwoPointsFlipped)
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

TEST(Rectangle, Conjunction)
{
    Rectangle a{{}, 4, 3};
    Rectangle b{{2, 1}, 3, 3};

    ASSERT_DOUBLE_EQ(a.conjunction(b).bottom(), 1);
    ASSERT_DOUBLE_EQ(a.conjunction(b).left(), 2);
    ASSERT_DOUBLE_EQ(a.conjunction(b).top(), 3);
    ASSERT_DOUBLE_EQ(a.conjunction(b).right(), 4);
}

TEST(Rectangle, ConjunctionNonOverlapping)
{
    Rectangle a{{}, 4, 3};

    Rectangle above{{2, 3}, 3, 3};
    ASSERT_DOUBLE_EQ(a.conjunction(above).bottom(), 0);
    ASSERT_DOUBLE_EQ(a.conjunction(above).left(), 0);
    ASSERT_DOUBLE_EQ(a.conjunction(above).top(), 0);
    ASSERT_DOUBLE_EQ(a.conjunction(above).right(), 0);

    Rectangle below{{2, -3}, 3, 3};
    ASSERT_DOUBLE_EQ(a.conjunction(below).bottom(), 0);
    ASSERT_DOUBLE_EQ(a.conjunction(below).left(), 0);
    ASSERT_DOUBLE_EQ(a.conjunction(below).top(), 0);
    ASSERT_DOUBLE_EQ(a.conjunction(below).right(), 0);

    Rectangle right{{2, 3}, 4, 3};
    ASSERT_DOUBLE_EQ(a.conjunction(right).bottom(), 0);
    ASSERT_DOUBLE_EQ(a.conjunction(right).left(), 0);
    ASSERT_DOUBLE_EQ(a.conjunction(right).top(), 0);
    ASSERT_DOUBLE_EQ(a.conjunction(right).right(), 0);

    Rectangle left{{2, 3}, -3, 3};
    ASSERT_DOUBLE_EQ(a.conjunction(left).bottom(), 0);
    ASSERT_DOUBLE_EQ(a.conjunction(left).left(), 0);
    ASSERT_DOUBLE_EQ(a.conjunction(left).top(), 0);
    ASSERT_DOUBLE_EQ(a.conjunction(left).right(), 0);
}
