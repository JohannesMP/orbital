//
// Created by jim on 27.01.18.
//

#include "common.h"
#include <Rectangle.h>

TEST(Rectangle, ProperConstructionWithPositiveExtent)
{
    Rectangle rect{{1, 2}, 3, 4};

    ASSERT_DOUBLE_EQ(rect.left(), 1);
    ASSERT_DOUBLE_EQ(rect.right(), 4);
    ASSERT_DOUBLE_EQ(rect.top(), 6);
    ASSERT_DOUBLE_EQ(rect.bottom(), 2);

    ASSERT_DOUBLE_EQ(rect.topLeft().x, 6);
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
}

TEST(Rectangle, ProperConstructionWithNegativeExtent)
{
    Rectangle rect{{4, 6}, -3, -4};

    ASSERT_DOUBLE_EQ(rect.left(), 1);
    ASSERT_DOUBLE_EQ(rect.right(), 4);
    ASSERT_DOUBLE_EQ(rect.top(), 6);
    ASSERT_DOUBLE_EQ(rect.bottom(), 2);

    ASSERT_DOUBLE_EQ(rect.topLeft().x, 6);
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
}

TEST(Rectangle, ProperConstructionFromTwoPoints)
{
    Rectangle rect{{1, 2}, {4, 6}};

    ASSERT_DOUBLE_EQ(rect.left(), 1);
    ASSERT_DOUBLE_EQ(rect.right(), 4);
    ASSERT_DOUBLE_EQ(rect.top(), 6);
    ASSERT_DOUBLE_EQ(rect.bottom(), 2);

    ASSERT_DOUBLE_EQ(rect.topLeft().x, 6);
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
}

TEST(Rectangle, ProperConstructionFromTwoPointsFlipped)
{
    Rectangle rect{{4, 6}, {1, 2}};

    ASSERT_DOUBLE_EQ(rect.left(), 1);
    ASSERT_DOUBLE_EQ(rect.right(), 4);
    ASSERT_DOUBLE_EQ(rect.top(), 6);
    ASSERT_DOUBLE_EQ(rect.bottom(), 2);

    ASSERT_DOUBLE_EQ(rect.topLeft().x, 6);
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
}
