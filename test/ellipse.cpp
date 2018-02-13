//
// Created by jim on 27.01.18.
//

#include <gtest/gtest.h>
#include <orbital/math/Ellipse.h>

TEST(Ellipse, ProperConstruction) // NOLINT
{
    Ellipse ellipse{2, 0.5};

    ASSERT_EQ(ellipse.a(), 2);
    ASSERT_EQ(ellipse.e(), 0.5);
    ASSERT_NEAR(ellipse.b(), 1.73, 0.01);
    ASSERT_DOUBLE_EQ(ellipse.foci()[0], -1);
    ASSERT_DOUBLE_EQ(ellipse.foci()[1], 1);
    ASSERT_DOUBLE_EQ(ellipse.focalPoints()[0].x, -1);
    ASSERT_DOUBLE_EQ(ellipse.focalPoints()[0].y, 0);
    ASSERT_DOUBLE_EQ(ellipse.focalPoints()[1].x, 1);
    ASSERT_DOUBLE_EQ(ellipse.focalPoints()[1].y, 0);
}

TEST(Ellipse, ParametricForm) // NOLINT
{
    Ellipse ellipse{2, 0.5};

    // 0 π
    ASSERT_NEAR(ellipse.point(0_pi).x, 2, 0.01);
    ASSERT_NEAR(ellipse.point(0_pi).y, 0, 0.01);

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

TEST(Ellipse, ParameterExtraction) // NOLINT
{
    Ellipse ellipse{2, 0.5};

    // 0 π
    ASSERT_NEAR(ellipse.tAtX(2), 0_pi, 0.01_pi);
    ASSERT_NEAR(ellipse.tAtY(0), 0_pi, 0.01_pi);

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

TEST(Ellipse, PointContainment) // NOLINT
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

TEST(Ellipse, PointFromParameter) // NOLINT
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


TEST(Ellipse, PointFromAngle) // NOLINT
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

TEST(Ellipse, ArcLength) // NOLINT
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

TEST(Ellipse, NegativeArcLength) // NOLINT
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

TEST(Ellipse, BoundingRect) // NOLINT
{
    Ellipse ellipse{2, 0.5};
    ASSERT_DOUBLE_EQ(ellipse.boundingRect().right(), ellipse.a());
    ASSERT_DOUBLE_EQ(ellipse.boundingRect().left(), -ellipse.a());
    ASSERT_DOUBLE_EQ(ellipse.boundingRect().top(), ellipse.b());
    ASSERT_DOUBLE_EQ(ellipse.boundingRect().bottom(), -ellipse.b());
}

TEST(Ellipse, Intersection) // NOLINT
{
    Ellipse ellipse = Ellipse::fromAB(2, 1);
    Line line = Line::fromDirection({2, 1}, {2, 1});

    auto intersections = ellipse.intersectPoints(line, false);

    ASSERT_EQ(intersections.size(), 2);
    ASSERT_DOUBLE_EQ(intersections[0].x, -sqrt(2));
    ASSERT_DOUBLE_EQ(intersections[0].y, -sqrt(2) / 2);
    ASSERT_DOUBLE_EQ(intersections[1].x, sqrt(2));
    ASSERT_DOUBLE_EQ(intersections[1].y, sqrt(2) / 2);
}

TEST(Ellipse, IntersectionNone) // NOLINT
{
    Ellipse ellipse = Ellipse::fromAB(2, 1);
    Line line = Line::fromDirection({2, 1}, {2, 1});

    auto intersections = ellipse.intersectPoints(line, true);

    ASSERT_EQ(intersections.size(), 0);
}

TEST(Ellipse, IntersectionPartial) // NOLINT
{
    Ellipse ellipse = Ellipse::fromAB(2, 1);
    Line line = Line::fromDirection(0.1 * vec{2, 1}, {2, 1});

    auto intersections = ellipse.intersectPoints(line, true);

    ASSERT_EQ(intersections.size(), 1);
    ASSERT_DOUBLE_EQ(intersections[0].x, sqrt(2));
    ASSERT_DOUBLE_EQ(intersections[0].y, sqrt(2) / 2);
}

TEST(Ellipse, IntersectionPerpendicularXAxis) // NOLINT
{
    Ellipse ellipse{2, 0.5};

    auto intersections = ellipse.intersectPoints(Line{{0, -2}, {0, 4}}, true);

    ASSERT_EQ(intersections.size(), 2);
    ASSERT_NEAR(intersections[0].x, 0, 0.001);
    ASSERT_NEAR(intersections[0].y, -ellipse.b(), 0.001);
    ASSERT_NEAR(intersections[1].x, 0, 0.001);
    ASSERT_NEAR(intersections[1].y, ellipse.b(), 0.001);
}

TEST(Ellipse, IntersectionPerpendicularXAxisPartial) // NOLINT
{
    Ellipse ellipse{2, 0.5};
    Line line = Line::fromDirection({0, -2}, {0, 1});

    auto intersections = ellipse.intersectPoints(line, true);

    ASSERT_EQ(intersections.size(), 1);
    ASSERT_NEAR(intersections[0].x, 0, 0.001);
    ASSERT_NEAR(intersections[0].y, -ellipse.b(), 0.001);
}

TEST(Ellipse, Projection) // NOLINT
{
    Ellipse ellipse = Ellipse::fromAB(2, 1);

    ASSERT_NEAR(ellipse.projection({2, 1.5}).x, 1.1, 0.1);
    ASSERT_NEAR(ellipse.projection({2, 1.5}).y, 0.83, 0.01);

    vec v{-3, -4};
    ASSERT_DOUBLE_EQ(ellipse.pointAngle(angle(v)).x, ellipse.projection(v).x);
    ASSERT_DOUBLE_EQ(ellipse.pointAngle(angle(v)).y, ellipse.projection(v).y);
}


TEST(Ellipse, RectangularClipNoOverlap) // NOLINT
{
    Ellipse ellipse{2, 0.5};
    Rectangle rect{{3, 1}, 4, 5};
    ASSERT_EQ(ellipse.clip(rect, {}).size(), 0);
}

TEST(Ellipse, RectangularClipFullOverlap) // NOLINT
{
    Ellipse ellipse{2, 0.5};
    Rectangle rect{{-2, -2}, {4, 4}};
    
    auto ts = ellipse.clip(rect, {});
    
    ASSERT_EQ(ts.size(), 1);

    ASSERT_DOUBLE_EQ(ts[0].first, 0_pi);
    ASSERT_DOUBLE_EQ(ts[0].second, 2_pi);
}

TEST(Ellipse, RectangularClipPartialOverlapFirstQuadrant) // NOLINT
{
    Ellipse ellipse{2, 0.5};
    Rectangle rect{{1, 1}, {4, 4}};

    auto ts = ellipse.clip(rect, {});

    ASSERT_EQ(ts.size(), 1);

    ASSERT_DOUBLE_EQ(ts[0].first, ellipse.tAtY(1));
    ASSERT_DOUBLE_EQ(ts[0].second, ellipse.tAtX(1));
}

TEST(Ellipse, RectangularClipPartialOverlapFirstAndFourthQuadrant) // NOLINT
{
    Ellipse ellipse{2, 0.5};
    Rectangle rect{{1, -2}, 2, 4};

    auto ts = ellipse.clip(rect, {});

    ASSERT_EQ(ts.size(), 1);

    ASSERT_DOUBLE_EQ(ts[0].first, 2_pi - ellipse.tAtX(1));
    ASSERT_DOUBLE_EQ(ts[0].second, 2_pi + ellipse.tAtX(1));
}

TEST(Ellipse, RectangularClipPartialOverlapNoSecondQuadrant) // NOLINT
{
    Ellipse ellipse{2, 0.5};
    Rectangle rect{{-1, 1}, {4, -4}};

    auto ts = ellipse.clip(rect, {});

    ASSERT_EQ(ts.size(), 1);

    ASSERT_DOUBLE_EQ(ts[0].first, 2_pi - ellipse.tAtX(-1));
    ASSERT_DOUBLE_EQ(ts[0].second, 2_pi + ellipse.tAtY(1));
}

TEST(Ellipse, RectangularClipPartialOverlapNoThirdQuadrant) // NOLINT
{
    Ellipse ellipse{2, 0.5};
    Rectangle rect{{-1, -1}, {4, 4}};

    auto ts = ellipse.clip(rect, {});

    ASSERT_EQ(ts.size(), 1);

    ASSERT_DOUBLE_EQ(ts[0].first, 2_pi + ellipse.tAtY(-1));
    ASSERT_DOUBLE_EQ(ts[0].second, 2_pi + ellipse.tAtX(-1));
}

TEST(Ellipse, RectangularClipPartialWithTransform) // NOLINT
{
    Ellipse ellipse{2, 0.5};
    Rectangle rect{{-sqrt(8) / 2, -sqrt(8) / 2}, {sqrt(8), sqrt(8)}};
    Transform transform;
    transform.rotate(0.25_pi);

    fmt::print("bottom-left: {}\n", transform.apply(rect.bottomLeft()));

    auto ts = ellipse.clip(rect, {});
    fmt::print("ts: {}\n", ts);

    ASSERT_EQ(ts.size(), 2);

    //ASSERT_DOUBLE_EQ(ts[0].first, 2_pi + ellipse.tAtY(-1));
    //ASSERT_DOUBLE_EQ(ts[0].second, 2_pi + ellipse.tAtX(-1));
}
