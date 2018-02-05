//
// Created by jim on 27.01.18.
//

#include <gtest/gtest.h>
#include <orbital/Ellipse.h>

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

    // 1.75 π
    ASSERT_NEAR(ellipse.point(2_pi).x, 2, 0.01);
    ASSERT_NEAR(ellipse.point(2_pi).y, 0, 0.01);
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

TEST(Ellipse, PointFromParameter)
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

    // 2 π
    ASSERT_NEAR(ellipse.point(2_pi).x, 2, 0.01);
    ASSERT_NEAR(ellipse.point(2_pi).y, 0, 0.01);

}


TEST(Ellipse, PointFromAngle)
{
    Ellipse ellipse{2, 0.5};

    // 0 π
    ASSERT_NEAR(ellipse.pointAngle(0).x, 2, 0.01);
    ASSERT_NEAR(ellipse.pointAngle(0).y, 0, 0.01);

    // 0.25 π
    ASSERT_NEAR(ellipse.pointAngle(0.25_pi).x, 1.31, 0.01);
    ASSERT_NEAR(ellipse.pointAngle(0.25_pi).y, 1.31, 0.01);

    // 0.5 π
    ASSERT_NEAR(ellipse.pointAngle(0.5_pi).x, 0, 0.01);
    ASSERT_NEAR(ellipse.pointAngle(0.5_pi).y, 1.73, 0.01);

    // 0.75 π
    ASSERT_NEAR(ellipse.pointAngle(0.75_pi).x, -1.31, 0.01);
    ASSERT_NEAR(ellipse.pointAngle(0.75_pi).y, 1.31, 0.01);

    // 1 π
    ASSERT_NEAR(ellipse.pointAngle(1_pi).x, -2, 0.01);
    ASSERT_NEAR(ellipse.pointAngle(1_pi).y, 0, 0.01);

    // 1.25 π
    ASSERT_NEAR(ellipse.pointAngle(1.25_pi).x, -1.31, 0.01);
    ASSERT_NEAR(ellipse.pointAngle(1.25_pi).y, -1.31, 0.01);

    // 1.5 π
    ASSERT_NEAR(ellipse.pointAngle(1.5_pi).x, 0, 0.01);
    ASSERT_NEAR(ellipse.pointAngle(1.5_pi).y, -1.73, 0.01);

    // 1.75 π
    ASSERT_NEAR(ellipse.pointAngle(1.75_pi).x, 1.31, 0.01);
    ASSERT_NEAR(ellipse.pointAngle(1.75_pi).y, -1.31, 0.01);

    // 2 π
    ASSERT_NEAR(ellipse.pointAngle(2_pi).x, 2, 0.01);
    ASSERT_NEAR(ellipse.pointAngle(2_pi).y, 0, 0.01);

    // -0.25 π
    ASSERT_NEAR(ellipse.pointAngle(-0.25_pi).x, 1.31, 0.01);
    ASSERT_NEAR(ellipse.pointAngle(-0.25_pi).y, -1.31, 0.01);

    // -0.5 π
    ASSERT_NEAR(ellipse.pointAngle(-0.5_pi).x, 0, 0.01);
    ASSERT_NEAR(ellipse.pointAngle(-0.5_pi).y, -1.73, 0.01);

    // -0.75 π
    ASSERT_NEAR(ellipse.pointAngle(-0.75_pi).x, -1.31, 0.01);
    ASSERT_NEAR(ellipse.pointAngle(-0.75_pi).y, -1.31, 0.01);

    // -1 π
    ASSERT_NEAR(ellipse.pointAngle(-1_pi).x, -2, 0.01);
    ASSERT_NEAR(ellipse.pointAngle(-1_pi).y, 0, 0.01);

    // -1.25 π
    ASSERT_NEAR(ellipse.pointAngle(-1.25_pi).x, -1.31, 0.01);
    ASSERT_NEAR(ellipse.pointAngle(-1.25_pi).y, 1.31, 0.01);

    // -1.5 π
    ASSERT_NEAR(ellipse.pointAngle(-1.5_pi).x, 0, 0.01);
    ASSERT_NEAR(ellipse.pointAngle(-1.5_pi).y, 1.73, 0.01);

    // -1.75 π
    ASSERT_NEAR(ellipse.pointAngle(-1.75_pi).x, 1.31, 0.01);
    ASSERT_NEAR(ellipse.pointAngle(-1.75_pi).y, 1.31, 0.01);

    // -2 π
    ASSERT_NEAR(ellipse.pointAngle(-2_pi).x, 2, 0.01);
    ASSERT_NEAR(ellipse.pointAngle(-2_pi).y, 0, 0.01);

}

TEST(Ellipse, ArcLength)
{
    Ellipse ellipse{2, 0.5};

    ASSERT_NEAR(ellipse.arcLength(0, 0, 100), 0.0, 0.0001);
    ASSERT_NEAR(ellipse.arcLength(0, 0.25_pi, 1000), 1.4, 0.1);
    ASSERT_NEAR(ellipse.arcLength(0, 0.5_pi, 1000), 2.93, 0.01);
    ASSERT_NEAR(ellipse.arcLength(0, 0.75_pi, 1000), 4.47, 0.01);
    ASSERT_NEAR(ellipse.arcLength(0, 1_pi, 1000), 5.87, 0.01);
    ASSERT_NEAR(ellipse.arcLength(0, 1.25_pi, 1000), 7.27, 0.01);
    ASSERT_NEAR(ellipse.arcLength(0, 1.5_pi, 1000), 8.8, 0.01);
    ASSERT_NEAR(ellipse.arcLength(0, 1.75_pi, 1000), 10.34, 0.01);
    ASSERT_NEAR(ellipse.arcLength(0, 2_pi, 1000), 11.74, 0.01);

    ASSERT_NEAR(ellipse.arcLength(1_pi, 1_pi, 100), 0.0, 0.0001);
    ASSERT_NEAR(ellipse.arcLength(1_pi, 1.25_pi, 1000), 1.4, 0.1);
    ASSERT_NEAR(ellipse.arcLength(1_pi, 1.5_pi, 1000), 2.93, 0.01);
    ASSERT_NEAR(ellipse.arcLength(1_pi, 1.75_pi, 1000), 4.47, 0.01);
    ASSERT_NEAR(ellipse.arcLength(1_pi, 2_pi, 1000), 5.87, 0.01);
    ASSERT_NEAR(ellipse.arcLength(1_pi, 2.25_pi, 1000), 7.27, 0.01);
    ASSERT_NEAR(ellipse.arcLength(1_pi, 2.5_pi, 1000), 8.8, 0.01);
    ASSERT_NEAR(ellipse.arcLength(1_pi, 2.75_pi, 1000), 10.34, 0.01);
    ASSERT_NEAR(ellipse.arcLength(1_pi, 3_pi, 1000), 11.74, 0.01);
}

TEST(Ellipse, NegativeArcLength)
{
    Ellipse ellipse{2, 0.5};

    ASSERT_NEAR(ellipse.arcLength(0, -0, 100), 0.0, 0.0001);
    ASSERT_NEAR(ellipse.arcLength(0, -0.25_pi, 1000), -1.4, 0.1);
    ASSERT_NEAR(ellipse.arcLength(0, -0.5_pi, 1000), -2.93, 0.01);
    ASSERT_NEAR(ellipse.arcLength(0, -0.75_pi, 1000), -4.47, 0.01);
    ASSERT_NEAR(ellipse.arcLength(0, -1_pi, 1000), -5.87, 0.01);
    ASSERT_NEAR(ellipse.arcLength(0, -1.25_pi, 1000), -7.27, 0.01);
    ASSERT_NEAR(ellipse.arcLength(0, -1.5_pi, 1000), -8.8, 0.01);
    ASSERT_NEAR(ellipse.arcLength(0, -1.75_pi, 1000), -10.34, 0.01);
    ASSERT_NEAR(ellipse.arcLength(0, -2_pi, 1000), -11.74, 0.01);

    ASSERT_NEAR(ellipse.arcLength(-1_pi, -1_pi, 100), 0.0, 0.0001);
    ASSERT_NEAR(ellipse.arcLength(-1_pi, -1.25_pi, 1000), -1.4, 0.1);
    ASSERT_NEAR(ellipse.arcLength(-1_pi, -1.5_pi, 1000), -2.93, 0.01);
    ASSERT_NEAR(ellipse.arcLength(-1_pi, -1.75_pi, 1000), -4.47, 0.01);
    ASSERT_NEAR(ellipse.arcLength(-1_pi, -2_pi, 1000), -5.87, 0.01);
    ASSERT_NEAR(ellipse.arcLength(-1_pi, -2.25_pi, 1000), -7.27, 0.01);
    ASSERT_NEAR(ellipse.arcLength(-1_pi, -2.5_pi, 1000), -8.8, 0.01);
    ASSERT_NEAR(ellipse.arcLength(-1_pi, -2.75_pi, 1000), -10.34, 0.01);
    ASSERT_NEAR(ellipse.arcLength(-1_pi, -3_pi, 1000), -11.74, 0.01);
}

TEST(Ellipse, BoundingRect)
{
    Ellipse ellipse{2, 0.5};
    ASSERT_DOUBLE_EQ(ellipse.boundingRect().right(), ellipse.a());
    ASSERT_DOUBLE_EQ(ellipse.boundingRect().left(), -ellipse.a());
    ASSERT_DOUBLE_EQ(ellipse.boundingRect().top(), ellipse.b());
    ASSERT_DOUBLE_EQ(ellipse.boundingRect().bottom(), -ellipse.b());
}

TEST(Ellipse, Intersection)
{
    Ellipse ellipse = Ellipse::fromAB(2, 1);
    Line line = Line::fromDirection({2, 1}, {2, 1});

    unsigned count;
    std::array<vec, 2> points;
    std::tie(count, points) = ellipse.intersectPoints(line, false);

    ASSERT_EQ(count, 2);
    ASSERT_DOUBLE_EQ(points[0].x, -sqrt(2));
    ASSERT_DOUBLE_EQ(points[0].y, -sqrt(2) / 2);
    ASSERT_DOUBLE_EQ(points[1].x, sqrt(2));
    ASSERT_DOUBLE_EQ(points[1].y, sqrt(2) / 2);
}

TEST(Ellipse, IntersectionNone)
{
    Ellipse ellipse = Ellipse::fromAB(2, 1);
    Line line = Line::fromDirection({2, 1}, {2, 1});

    unsigned count;
    std::array<vec, 2> points;
    std::tie(count, points) = ellipse.intersectPoints(line, true);

    ASSERT_EQ(count, 0);
}

TEST(Ellipse, IntersectionPartial)
{
    Ellipse ellipse = Ellipse::fromAB(2, 1);
    Line line = Line::fromDirection(0.1 * vec{2, 1}, {2, 1});

    unsigned count;
    std::array<vec, 2> points;
    std::tie(count, points) = ellipse.intersectPoints(line, true);

    ASSERT_EQ(count, 1);
    ASSERT_DOUBLE_EQ(points[0].x, sqrt(2));
    ASSERT_DOUBLE_EQ(points[0].y, sqrt(2) / 2);
}

TEST(Ellipse, IntersectionPerpendicularXAxis)
{
    Ellipse ellipse{2, 0.5};

    unsigned count;
    std::array<vec, 2> points;
    std::tie(count, points) = ellipse.intersectPoints({{0, -2}, {0, 4}}, true);

    ASSERT_EQ(count, 2);
    ASSERT_NEAR(points[0].x, 0, 0.001);
    ASSERT_NEAR(points[0].y, -ellipse.b(), 0.001);
    ASSERT_NEAR(points[1].x, 0, 0.001);
    ASSERT_NEAR(points[1].y, ellipse.b(), 0.001);
}

TEST(Ellipse, IntersectionPerpendicularXAxisPartial)
{
    Ellipse ellipse{2, 0.5};
    Line line = Line::fromDirection({0, -2}, {0, 1});

    unsigned count;
    std::array<vec, 2> points;
    std::tie(count, points) = ellipse.intersectPoints(line, true);

    ASSERT_EQ(count, 1);
    ASSERT_NEAR(points[0].x, 0, 0.001);
    ASSERT_NEAR(points[0].y, -ellipse.b(), 0.001);
}

/*


TEST(Ellipse, RectangularClipNoOverlap)
{
    Ellipse ellipse{2, 0.5};
    Rectangle rect{{3, 1}, 4, 5};
    ASSERT_EQ(ellipse.clip(rect, {}).size(), 0);
}

TEST(Ellipse, RectangularClipFullOverlap)
{
    Ellipse ellipse{2, 0.5};
    Rectangle rect{{-2, -2}, {4, 4}};
    
    auto ts = ellipse.clip(rect, {});
    
    ASSERT_EQ(ts.size(), 1);

    ASSERT_DOUBLE_EQ(ts[0].first, 0_pi);
    ASSERT_DOUBLE_EQ(ts[0].second, 2_pi);
}

TEST(Ellipse, RectangularClipPartialOverlapNoFirstQuadrant)
{
    Ellipse ellipse{2, 0.5};
    Rectangle rect{{1, 1}, {4, 4}};

    std::cout << std::endl << std::endl;
    auto ts = ellipse.clip(rect, {});
    std::cout << std::endl << std::endl;

    ASSERT_EQ(ts.size(), 1);

    ASSERT_DOUBLE_EQ(ts[0].first, 1_pi - ellipse.tAtY(1));
    ASSERT_DOUBLE_EQ(ts[0].second, 2_pi - std::abs(ellipse.tAtX(1)));
}
TEST(Ellipse, RectangularClipPartialOverlapNoSecondQuadrant)
{
    Ellipse ellipse{2, 0.5};
    Rectangle rect{{-1, 1}, {4, -4}};

    auto ts = ellipse.clip(rect);

    ASSERT_EQ(ts.size(), 3);

    ASSERT_DOUBLE_EQ(ts[0].first, 0_pi);
    ASSERT_DOUBLE_EQ(ts[0].second, ellipse.tAtY(1));

    ASSERT_DOUBLE_EQ(ts[1].first, 2_pi - std::abs(ellipse.tAtX(-1)));
    ASSERT_DOUBLE_EQ(ts[1].second, 1.5_pi);

    ASSERT_DOUBLE_EQ(ts[2].first, 1.5_pi);
    ASSERT_DOUBLE_EQ(ts[2].second, 2_pi);
}

TEST(Ellipse, RectangularClipPartialOverlapNoThirdQuadrant)
{
    Ellipse ellipse{2, 0.5};
    Rectangle rect{{-1, -1}, {4, 4}};

    std::cout << std::endl << std::endl;
    auto ts = ellipse.clip(rect);
    std::cout << std::endl << std::endl;

    ASSERT_EQ(ts.size(), 3);

    ASSERT_DOUBLE_EQ(ts[0].first, 0_pi);
    ASSERT_DOUBLE_EQ(ts[0].second, 0.5_pi);

    ASSERT_DOUBLE_EQ(ts[1].first, 0.5_pi);
    ASSERT_DOUBLE_EQ(ts[1].second, ellipse.tAtX(-1));

    ASSERT_DOUBLE_EQ(ts[2].first, 2_pi - std::abs(ellipse.tAtY(-1)));
    ASSERT_DOUBLE_EQ(ts[2].second, 2_pi);
}*/
