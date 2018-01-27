//
// Created by jim on 27.01.18.
//

#include <Ellipse.h>
#include "common.h"

TEST(Ellipse, ProperConstruction)
{
    Ellipse ellipse{2, 0.5};

    ASSERT_EQ(ellipse.a(), 2);
    ASSERT_EQ(ellipse.e(), 0.5);
    ASSERT_NEAR(ellipse.b(), 1.73, 0.01);
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
    ASSERT_NEAR(ellipse.point(0).x, 2, 0.01);
    ASSERT_NEAR(ellipse.point(0).y, 0, 0.01);

    // 0.25 π
    ASSERT_NEAR(ellipse.point(0.25_pi).x, 1.41, 0.01);
    ASSERT_NEAR(ellipse.point(0.25_pi).y, 1.22, 0.01);

    // 0.5 π
    ASSERT_NEAR(ellipse.point(0.5_pi).x, 0, 0.01);
    ASSERT_NEAR(ellipse.point(0.5_pi).y, 1.73, 0.01);

    // 0.75 π
    ASSERT_NEAR(ellipse.point(0.75_pi).x, -1.41, 0.01);
    ASSERT_NEAR(ellipse.point(0.75_pi).y, 1.22, 0.01);

    // 1 π
    ASSERT_NEAR(ellipse.point(PI).x, -2, 0.01);
    ASSERT_NEAR(ellipse.point(PI).y, 0, 0.01);

    // 1.25 π
    ASSERT_NEAR(ellipse.point(1.25_pi).x, -1.41, 0.01);
    ASSERT_NEAR(ellipse.point(1.25_pi).y, -1.22, 0.01);

    // 1.5 π
    ASSERT_NEAR(ellipse.point(1.5_pi).x, 0, 0.01);
    ASSERT_NEAR(ellipse.point(1.5_pi).y, -1.73, 0.01);

    // 1.75 π
    ASSERT_NEAR(ellipse.point(1.75_pi).x, 1.41, 0.01);
    ASSERT_NEAR(ellipse.point(1.75_pi).y, -1.22, 0.01);
}

TEST(Ellipse, ParameterExtraction)
{
    Ellipse ellipse{2, 0.5};

    // 0 π
    ASSERT_NEAR(ellipse.tAtX(2), 0, 0.01);
    ASSERT_NEAR(ellipse.tAtY(0), 0, 0.01);

    // 0.25 π
    ASSERT_NEAR(ellipse.tAtX(1.41), 0.25_pi, 0.01);
    ASSERT_NEAR(ellipse.tAtY(1.22), 0.25_pi, 0.01);

    // 0.5 π
    ASSERT_NEAR(ellipse.tAtX(0), 0.5_pi, 0.01);
    ASSERT_NEAR(ellipse.tAtY(1.732), 0.5_pi, 0.01);

    // 0.75 π
    ASSERT_NEAR(ellipse.tAtX(-1.41), 0.75_pi, 0.01);

    // 1 π
    ASSERT_NEAR(ellipse.tAtX(-2), 1_pi, 0.01);

    // 1.5 π
    ASSERT_NEAR(ellipse.tAtY(-1.732), -0.5_pi, 0.01);

    // 1.75 π
    ASSERT_NEAR(ellipse.tAtY(-1.22), -0.25_pi, 0.01);
}

TEST(Ellipse, PointContainment)
{
    Ellipse ellipse{2, 0.5};

    ASSERT_TRUE(ellipse.contains(vec(0, 0)));
    ASSERT_TRUE(ellipse.contains(vec(2, 0)));
    ASSERT_TRUE(ellipse.contains(vec(-2, 0)));
    ASSERT_TRUE(ellipse.contains(vec(0, 0.5)));
    ASSERT_TRUE(ellipse.contains(vec(0, -0.5)));

    ASSERT_TRUE(ellipse.contains(vec(1, 1)));
    ASSERT_TRUE(ellipse.contains(vec(-1, 1)));
    ASSERT_TRUE(ellipse.contains(vec(1, -1)));
    ASSERT_TRUE(ellipse.contains(vec(-1, -1)));

    ASSERT_FALSE(ellipse.contains(vec(1.5, 1.5)));
    ASSERT_FALSE(ellipse.contains(vec(-1.5, 1.5)));
    ASSERT_FALSE(ellipse.contains(vec(1.5, -1.5)));
    ASSERT_FALSE(ellipse.contains(vec(-1.5, -1.5)));
}

TEST(Ellipse, AngleFromParameter)
{
    Ellipse ellipse{2, 0.5};

    // 0 π
    ASSERT_NEAR(ellipse.point(0).x, 2, 0.01);
    ASSERT_NEAR(ellipse.point(0).y, 0, 0.01);

    // 0.25 π
    ASSERT_NEAR(ellipse.point(0.25_pi).x, 1.41, 0.01);
    ASSERT_NEAR(ellipse.point(0.25_pi).y, 1.22, 0.01);

    // 0.5 π
    ASSERT_NEAR(ellipse.point(0.5_pi).x, 0, 0.01);
    ASSERT_NEAR(ellipse.point(0.5_pi).y, 1.73, 0.01);

    // 0.75 π
    ASSERT_NEAR(ellipse.point(0.75_pi).x, -1.41, 0.01);
    ASSERT_NEAR(ellipse.point(0.75_pi).y, 1.22, 0.01);

    // 1 π
    ASSERT_NEAR(ellipse.point(1_pi).x, -2, 0.01);
    ASSERT_NEAR(ellipse.point(1_pi).y, 0, 0.01);

    // 1.25 π
    ASSERT_NEAR(ellipse.point(1.25_pi).x, -1.41, 0.01);
    ASSERT_NEAR(ellipse.point(1.25_pi).y, -1.22, 0.01);

    // 1.5 π
    ASSERT_NEAR(ellipse.point(1.5_pi).x, 0, 0.01);
    ASSERT_NEAR(ellipse.point(1.5_pi).y, -1.73, 0.01);

    // 1.75 π
    ASSERT_NEAR(ellipse.point(1.75_pi).x, 1.41, 0.01);
    ASSERT_NEAR(ellipse.point(1.75_pi).y, -1.22, 0.01);

}
