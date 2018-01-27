//
// Created by jim on 27.01.18.
//

#include <Ellipse.h>
#include "common.h"
#include "FloatingPointComparator.h"

TEST(Ellipse, ProperConstruction)
{
    Ellipse ellipse{2, 0.5};

    ASSERT_EQ(ellipse.a(), 2);
    ASSERT_EQ(ellipse.e(), 0.5);
    ASSERT_EQ(ellipse.b(), "1.73"_c);
    ASSERT_DOUBLE_EQ(ellipse.foci()[0], -1);
    ASSERT_DOUBLE_EQ(ellipse.foci()[1], 1);
    ASSERT_DOUBLE_EQ(ellipse.fociPoints()[0].x, -1);
    ASSERT_DOUBLE_EQ(ellipse.fociPoints()[0].y, 0);
    ASSERT_DOUBLE_EQ(ellipse.fociPoints()[1].x, 1);
    ASSERT_DOUBLE_EQ(ellipse.fociPoints()[1].y, 0);
}

TEST(Ellipse, ParametricForm)
{
    Ellipse ellipse{2, 0.5};

    // 0 π
    ASSERT_EQ(ellipse.point(0).x, "2"_c);
    ASSERT_EQ(ellipse.point(0).y, "0"_c);

    // 0.25 π
    ASSERT_EQ(ellipse.point(0.25 * PI).x, "1.41"_c);
    ASSERT_EQ(ellipse.point(0.25 * PI).y, "1.22"_c);

    // 0.5 π
    ASSERT_EQ(ellipse.point(0.5 * PI).x, "0"_c);
    ASSERT_EQ(ellipse.point(0.5 * PI).y, "1.73"_c);

    // 0.75 π
    ASSERT_EQ(ellipse.point(0.75 * PI).x, "-1.41"_c);
    ASSERT_EQ(ellipse.point(0.75 * PI).y, "1.22"_c);

    // 1 π
    ASSERT_EQ(ellipse.point(PI).x, "-2"_c);
    ASSERT_EQ(ellipse.point(PI).y, "0"_c);

    // 1.25 π
    ASSERT_EQ(ellipse.point(1.25 * PI).x, "-1.41"_c);
    ASSERT_EQ(ellipse.point(1.25 * PI).y, "-1.22"_c);

    // 1.5 π
    ASSERT_EQ(ellipse.point(1.5 * PI).x, "0"_c);
    ASSERT_EQ(ellipse.point(1.5 * PI).y, "-1.73"_c);

    // 1.75 π
    ASSERT_EQ(ellipse.point(1.75 * PI).x, "1.41"_c);
    ASSERT_EQ(ellipse.point(1.75 * PI).y, "-1.22"_c);
}

TEST(Ellipse, PointContainment)
{
    Ellipse ellipse{2, 0.5};

    //ASSERT_TRUE(ellipse.contains(vec(0, 0)));
}
