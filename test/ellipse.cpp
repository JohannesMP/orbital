//
// Created by jim on 27.01.18.
//

#include "catch/catch.hpp"
#include "common.h"
#include <orbital/math/Ellipse.h>
#include <orbital/math/elementary.h>

TEST_CASE("Ellipse", "[math]") // NOLINT
{
    Ellipse ellipse{2, 0.5};

    SECTION("proper construction")
    {
        CHECK(ellipse.a() == 2);
        CHECK(ellipse.e() == 0.5);
        CHECK(ellipse.b() == Approx(1.73).margin(0.01));
        CHECK(ellipse.foci()[0] == Approx(-1));
        CHECK(ellipse.foci()[1] == Approx(1));
        CHECK(ellipse.focalPoints()[0].x == Approx(-1));
        CHECK(ellipse.focalPoints()[0].y == Approx(0));
        CHECK(ellipse.focalPoints()[1].x == Approx(1));
        CHECK(ellipse.focalPoints()[1].y == Approx(0));
    }

    SECTION("parametric form")
    {
        // 0 π
        CHECK(ellipse.point(0_pi).x == Approx(2).margin(0.01));
        CHECK(ellipse.point(0_pi).y == Approx(0).margin(0.01));

        // 0.25 π
        CHECK(ellipse.point(0.25_pi).x == Approx(1.41).margin(0.01));
        CHECK(ellipse.point(0.25_pi).y == Approx(1.22).margin(0.01));

        // 0.5 π
        CHECK(ellipse.point(0.5_pi).x == Approx(0).margin(0.01));
        CHECK(ellipse.point(0.5_pi).y == Approx(1.73).margin(0.01));

        // 0.75 π
        CHECK(ellipse.point(0.75_pi).x == Approx(-1.41).margin(0.01));
        CHECK(ellipse.point(0.75_pi).y == Approx(1.22).margin(0.01));

        // 1 π
        CHECK(ellipse.point(1_pi).x == Approx(-2).margin(0.01));
        CHECK(ellipse.point(1_pi).y == Approx(0).margin(0.01));

        // 1.25 π
        CHECK(ellipse.point(1.25_pi).x == Approx(-1.41).margin(0.01));
        CHECK(ellipse.point(1.25_pi).y == Approx(-1.22).margin(0.01));

        // 1.5 π
        CHECK(ellipse.point(1.5_pi).x == Approx(0).margin(0.01));
        CHECK(ellipse.point(1.5_pi).y == Approx(-1.73).margin(0.01));

        // 1.75 π
        CHECK(ellipse.point(1.75_pi).x == Approx(1.41).margin(0.01));
        CHECK(ellipse.point(1.75_pi).y == Approx(-1.22).margin(0.01));

        // 1.75 π
        CHECK(ellipse.point(2_pi).x == Approx(2).margin(0.01));
        CHECK(ellipse.point(2_pi).y == Approx(0).margin(0.01));
    }

    SECTION("parameter extraction")
    {
        // 0 π
        CHECK(ellipse.tAtX(2) == Approx(0).margin(0.01));
        CHECK(ellipse.tAtY(0) == Approx(0).margin(0.01));

        // 0.25 π
        CHECK(ellipse.tAtX(1.41) == approx(0.25_pi).margin(0.01));
        CHECK(ellipse.tAtY(1.22) == approx(0.25_pi).margin(0.01));

        // 0.5 π
        CHECK(ellipse.tAtX(0) == approx(0.5_pi).margin(0.01));
        CHECK(ellipse.tAtY(1.732) == approx(0.5_pi).margin(0.01));

        // 0.75 π
        CHECK(ellipse.tAtX(-1.41) == approx(0.75_pi).margin(0.01));

        // 1 π
        CHECK(ellipse.tAtX(-2) == approx(1_pi).margin(0.01));

        // 1.5 π
        CHECK(ellipse.tAtY(-1.732) == approx(-0.5_pi).margin(0.01));

        // 1.75 π
        CHECK(ellipse.tAtY(-1.22) == approx(-0.25_pi).margin(0.01));
    }

    SECTION("point containment")
    {
        CHECK(ellipse.contains(vec(0, 0)));
        CHECK(ellipse.contains(vec(2, 0)));
        CHECK(ellipse.contains(vec(-2, 0)));
        CHECK(ellipse.contains(vec(0, 0.5)));
        CHECK(ellipse.contains(vec(0, -0.5)));

        CHECK(ellipse.contains(vec(1, 1)));
        CHECK(ellipse.contains(vec(-1, 1)));
        CHECK(ellipse.contains(vec(1, -1)));
        CHECK(ellipse.contains(vec(-1, -1)));

        CHECK_FALSE(ellipse.contains(vec(1.5, 1.5)));
        CHECK_FALSE(ellipse.contains(vec(-1.5, 1.5)));
        CHECK_FALSE(ellipse.contains(vec(1.5, -1.5)));
        CHECK_FALSE(ellipse.contains(vec(-1.5, -1.5)));
    }

    SECTION("point from parameter")
    {
        // 0 π
        CHECK(ellipse.point(0_pi).x == Approx(2).margin(0.01));
        CHECK(ellipse.point(0_pi).y == Approx(0).margin(0.01));

        // 0.25 π
        CHECK(ellipse.point(0.25_pi).x == Approx(1.41).margin(0.01));
        CHECK(ellipse.point(0.25_pi).y == Approx(1.22).margin(0.01));

        // 0.5 π
        CHECK(ellipse.point(0.5_pi).x == Approx(0).margin(0.01));
        CHECK(ellipse.point(0.5_pi).y == Approx(1.73).margin(0.01));

        // 0.75 π
        CHECK(ellipse.point(0.75_pi).x == Approx(-1.41).margin(0.01));
        CHECK(ellipse.point(0.75_pi).y == Approx(1.22).margin(0.01));

        // 1 π
        CHECK(ellipse.point(1_pi).x == Approx(-2).margin(0.01));
        CHECK(ellipse.point(1_pi).y == Approx(0).margin(0.01));

        // 1.25 π
        CHECK(ellipse.point(1.25_pi).x == Approx(-1.41).margin(0.01));
        CHECK(ellipse.point(1.25_pi).y == Approx(-1.22).margin(0.01));

        // 1.5 π
        CHECK(ellipse.point(1.5_pi).x == Approx(0).margin(0.01));
        CHECK(ellipse.point(1.5_pi).y == Approx(-1.73).margin(0.01));

        // 1.75 π
        CHECK(ellipse.point(1.75_pi).x == Approx(1.41).margin(0.01));
        CHECK(ellipse.point(1.75_pi).y == Approx(-1.22).margin(0.01));

        // 2 π
        CHECK(ellipse.point(2_pi).x == Approx(2).margin(0.01));
        CHECK(ellipse.point(2_pi).y == Approx(0).margin(0.01));

    }

    SECTION("point from angle")
    {
        // 0 π
        CHECK(ellipse.pointAngle(0_pi).x == Approx(2).margin(0.01));
        CHECK(ellipse.pointAngle(0_pi).y == Approx(0).margin(0.01));

        // 0.25 π
        CHECK(ellipse.pointAngle(0.25_pi).x == Approx(1.31).margin(0.01));
        CHECK(ellipse.pointAngle(0.25_pi).y == Approx(1.31).margin(0.01));

        // 0.5 π
        CHECK(ellipse.pointAngle(0.5_pi).x == Approx(0).margin(0.01));
        CHECK(ellipse.pointAngle(0.5_pi).y == Approx(1.73).margin(0.01));

        // 0.75 π
        CHECK(ellipse.pointAngle(0.75_pi).x == Approx(-1.31).margin(0.01));
        CHECK(ellipse.pointAngle(0.75_pi).y == Approx(1.31).margin(0.01));

        // 1 π
        CHECK(ellipse.pointAngle(1_pi).x == Approx(-2).margin(0.01));
        CHECK(ellipse.pointAngle(1_pi).y == Approx(0).margin(0.01));

        // 1.25 π
        CHECK(ellipse.pointAngle(1.25_pi).x == Approx(-1.31).margin(0.01));
        CHECK(ellipse.pointAngle(1.25_pi).y == Approx(-1.31).margin(0.01));

        // 1.5 π
        CHECK(ellipse.pointAngle(1.5_pi).x == Approx(0).margin(0.01));
        CHECK(ellipse.pointAngle(1.5_pi).y == Approx(-1.73).margin(0.01));

        // 1.75 π
        CHECK(ellipse.pointAngle(1.75_pi).x == Approx(1.31).margin(0.01));
        CHECK(ellipse.pointAngle(1.75_pi).y == Approx(-1.31).margin(0.01));

        // 2 π
        CHECK(ellipse.pointAngle(2_pi).x == Approx(2).margin(0.01));
        CHECK(ellipse.pointAngle(2_pi).y == Approx(0).margin(0.01));

        // -0.25 π
        CHECK(ellipse.pointAngle(-0.25_pi).x == Approx(1.31).margin(0.01));
        CHECK(ellipse.pointAngle(-0.25_pi).y == Approx(-1.31).margin(0.01));

        // -0.5 π
        CHECK(ellipse.pointAngle(-0.5_pi).x == Approx(0).margin(0.01));
        CHECK(ellipse.pointAngle(-0.5_pi).y == Approx(-1.73).margin(0.01));

        // -0.75 π
        CHECK(ellipse.pointAngle(-0.75_pi).x == Approx(-1.31).margin(0.01));
        CHECK(ellipse.pointAngle(-0.75_pi).y == Approx(-1.31).margin(0.01));

        // -1 π
        CHECK(ellipse.pointAngle(-1_pi).x == Approx(-2).margin(0.01));
        CHECK(ellipse.pointAngle(-1_pi).y == Approx(0).margin(0.01));

        // -1.25 π
        CHECK(ellipse.pointAngle(-1.25_pi).x == Approx(-1.31).margin(0.01));
        CHECK(ellipse.pointAngle(-1.25_pi).y == Approx(1.31).margin(0.01));

        // -1.5 π
        CHECK(ellipse.pointAngle(-1.5_pi).x == Approx(0).margin(0.01));
        CHECK(ellipse.pointAngle(-1.5_pi).y == Approx(1.73).margin(0.01));

        // -1.75 π
        CHECK(ellipse.pointAngle(-1.75_pi).x == Approx(1.31).margin(0.01));
        CHECK(ellipse.pointAngle(-1.75_pi).y == Approx(1.31).margin(0.01));

        // -2 π
        CHECK(ellipse.pointAngle(-2_pi).x == Approx(2).margin(0.01));
        CHECK(ellipse.pointAngle(-2_pi).y == Approx(0).margin(0.01));

    }

    SECTION("ArcLength")
    {
        CHECK(ellipse.arcLength(0_pi, 0_pi, 100_pi) == Approx(0.0).margin(0.0001));
        CHECK(ellipse.arcLength(0_pi, 0.25_pi, 1000_pi) == Approx(1.4).margin(0.1));
        CHECK(ellipse.arcLength(0_pi, 0.5_pi, 1000_pi) == Approx(2.93).margin(0.01));
        CHECK(ellipse.arcLength(0_pi, 0.75_pi, 1000_pi) == Approx(4.47).margin(0.01));
        CHECK(ellipse.arcLength(0_pi, 1_pi, 1000_pi) == Approx(5.87).margin(0.01));
        CHECK(ellipse.arcLength(0_pi, 1.25_pi, 1000_pi) == Approx(7.27).margin(0.01));
        CHECK(ellipse.arcLength(0_pi, 1.5_pi, 1000_pi) == Approx(8.8).margin(0.01));
        CHECK(ellipse.arcLength(0_pi, 1.75_pi, 1000_pi) == Approx(10.34).margin(0.01));
        CHECK(ellipse.arcLength(0_pi, 2_pi, 1000_pi) == Approx(11.74).margin(0.01));

        CHECK(ellipse.arcLength(1_pi, 1_pi, 100_pi) == Approx(0.0).margin(0.0001));
        CHECK(ellipse.arcLength(1_pi, 1.25_pi, 1000_pi) == Approx(1.4).margin(0.1));
        CHECK(ellipse.arcLength(1_pi, 1.5_pi, 1000_pi) == Approx(2.93).margin(0.01));
        CHECK(ellipse.arcLength(1_pi, 1.75_pi, 1000_pi) == Approx(4.47).margin(0.01));
        CHECK(ellipse.arcLength(1_pi, 2_pi, 1000_pi) == Approx(5.87).margin(0.01));
        CHECK(ellipse.arcLength(1_pi, 2.25_pi, 1000_pi) == Approx(7.27).margin(0.01));
        CHECK(ellipse.arcLength(1_pi, 2.5_pi, 1000_pi) == Approx(8.8).margin(0.01));
        CHECK(ellipse.arcLength(1_pi, 2.75_pi, 1000_pi) == Approx(10.34).margin(0.01));
        CHECK(ellipse.arcLength(1_pi, 3_pi, 1000_pi) == Approx(11.74).margin(0.01));
    }

    SECTION("negative arc length")
    {
        CHECK(ellipse.arcLength(0_pi, -0_pi, 100_pi) == Approx(-0.0).margin(0.0001));
        CHECK(ellipse.arcLength(0_pi, -0.25_pi, 1000_pi) == Approx(-1.4).margin(0.1));
        CHECK(ellipse.arcLength(0_pi, -0.5_pi, 1000_pi) == Approx(-2.93).margin(0.01));
        CHECK(ellipse.arcLength(0_pi, -0.75_pi, 1000_pi) == Approx(-4.47).margin(0.01));
        CHECK(ellipse.arcLength(0_pi, -1_pi, 1000_pi) == Approx(-5.87).margin(0.01));
        CHECK(ellipse.arcLength(0_pi, -1.25_pi, 1000_pi) == Approx(-7.27).margin(0.01));
        CHECK(ellipse.arcLength(0_pi, -1.5_pi, 1000_pi) == Approx(-8.8).margin(0.01));
        CHECK(ellipse.arcLength(0_pi, -1.75_pi, 1000_pi) == Approx(-10.34).margin(0.01));
        CHECK(ellipse.arcLength(0_pi, -2_pi, 1000_pi) == Approx(-11.74).margin(0.01));

        CHECK(ellipse.arcLength(-1_pi, -1_pi, 100_pi) == Approx(-0.0).margin(0.0001));
        CHECK(ellipse.arcLength(-1_pi, -1.25_pi, 1000_pi) == Approx(-1.4).margin(0.1));
        CHECK(ellipse.arcLength(-1_pi, -1.5_pi, 1000_pi) == Approx(-2.93).margin(0.01));
        CHECK(ellipse.arcLength(-1_pi, -1.75_pi, 1000_pi) == Approx(-4.47).margin(0.01));
        CHECK(ellipse.arcLength(-1_pi, -2_pi, 1000_pi) == Approx(-5.87).margin(0.01));
        CHECK(ellipse.arcLength(-1_pi, -2.25_pi, 1000_pi) == Approx(-7.27).margin(0.01));
        CHECK(ellipse.arcLength(-1_pi, -2.5_pi, 1000_pi) == Approx(-8.8).margin(0.01));
        CHECK(ellipse.arcLength(-1_pi, -2.75_pi, 1000_pi) == Approx(-10.34).margin(0.01));
        CHECK(ellipse.arcLength(-1_pi, -3_pi, 1000_pi) == Approx(-11.74).margin(0.01));
    }

    SECTION("bounding rect")
    {
        CHECK(ellipse.boundingRect().right() == Approx(ellipse.a()));
        CHECK(ellipse.boundingRect().left() == Approx(-ellipse.a()));
        CHECK(ellipse.boundingRect().top() == Approx(ellipse.b()));
        CHECK(ellipse.boundingRect().bottom() == Approx(-ellipse.b()));
    }

    SECTION("intersection")
    {
        Line line = Line::fromDirection({2, 1}, {2, 1});

        auto intersections = ellipse.intersectPoints(line, false);

        CHECK(intersections.size() == 2);
        CHECK(intersections[0].x == Approx(-1.73).margin(0.01));
        CHECK(intersections[0].y == Approx(-0.87).margin(0.01));
        CHECK(intersections[1].x == Approx(1.73).margin(0.01));
        CHECK(intersections[1].y == Approx(0.87).margin(0.01));
    }

    SECTION("no intersection")
    {
        Line line = Line::fromDirection({2, 1}, {2, 1});

        auto intersections = ellipse.intersectPoints(line, true);

        CHECK(intersections.size() == 0);
    }

    SECTION("partial intersection")
    {
        Line line = Line::fromDirection(0.1 * vec{2, 1}, {2, 1});

        auto intersections = ellipse.intersectPoints(line, true);

        CHECK(intersections.size() == 1);
        CHECK(intersections[0].x == Approx(1.73).margin(0.01));
        CHECK(intersections[0].y == Approx(0.87).margin(0.01));
    }

    SECTION("intersection with line, which is perpendicular on x-axis, i.e. gradient is infinite")
    {
        auto intersections = ellipse.intersectPoints(Line{{0, -2}, {0, 4}}, true);

        CHECK(intersections.size() == 2);
        CHECK(intersections[0].x == Approx(0).margin(0.001));
        CHECK(intersections[0].y == Approx(-ellipse.b()).margin(0.001));
        CHECK(intersections[1].x == Approx(0).margin(0.001));
        CHECK(intersections[1].y == Approx(ellipse.b()).margin(0.001));
    }

    SECTION("partial intersection with line, which is perpendicular on x-axis, i.e. gradient is infinite")
    {
        Line line = Line::fromDirection({0, -2}, {0, 1});

        auto intersections = ellipse.intersectPoints(line, true);

        CHECK(intersections.size() == 1);
        CHECK(intersections[0].x == Approx(0).margin(0.001));
        CHECK(intersections[0].y == Approx(-ellipse.b()).margin(0.001));
    }

    SECTION("projection of any point onto ellipse")
    {
        vec v{2, 1.5};

        CHECK(ellipse.projection(v).x == Approx(1.51).margin(0.01));
        CHECK(ellipse.projection(v).y == Approx(1.13).margin(0.01));
    }

    SECTION("projection equals mapping a point to an angle, from which the point on the ellipse is computed")
    {
        vec v{2, 1.5};

        CHECK(ellipse.pointAngle(angle(v)).x == Approx(ellipse.projection(v).x));
        CHECK(ellipse.pointAngle(angle(v)).y == Approx(ellipse.projection(v).y));
    }

    SECTION("projection of 0|0 onto ellipse is nan")
    {
        CHECK(std::isnan(ellipse.projection({0, 0}).x));
        CHECK(std::isnan(ellipse.projection({0, 0}).y));
    }

    SECTION("rectangular clip without any overlap")
    {
        Rectangle rect{{3, 1}, 4, 5};
        CHECK(ellipse.clip(rect, {}).size() == 0);
    }

    SECTION("rectangular clip with complete overlap")
    {
        Rectangle rect{{-2, -2}, {4, 4}};

        auto ts = ellipse.clip(rect, {});

        CHECK(ts.size() == 1);

        CHECK(ts[0].first == approx(0_pi));
        CHECK(ts[0].second == approx(2_pi));
    }

    SECTION("partial rectangular clip with no ellipse section in first quadrant")
    {
        Rectangle rect{{1, 1}, {4, 4}};

        auto ts = ellipse.clip(rect, {});

        CHECK(ts.size() == 1);

        CHECK(ts[0].first == approx(ellipse.tAtY(1)));
        CHECK(ts[0].second == approx(ellipse.tAtX(1)));
    }

    SECTION("partial rectangular clip with no ellipse section in second quadrant")
    {
        Rectangle rect{{-1, 1}, {4, -4}};

        auto ts = ellipse.clip(rect, {});

        CHECK(ts.size() == 1);

        CHECK(ts[0].first == approx(2_pi - ellipse.tAtX(-1)));
        CHECK(ts[0].second == approx(2_pi + ellipse.tAtY(1)));
    }

    SECTION("partial rectangular clip with no ellipse section in third quadrant")
    {
        Rectangle rect{{-1, -1}, {4, 4}};

        auto ts = ellipse.clip(rect, {});

        CHECK(ts.size() == 1);

        CHECK(ts[0].first == approx(2_pi + ellipse.tAtY(-1)));
        CHECK(ts[0].second == approx(2_pi + ellipse.tAtX(-1)));
    }

    SECTION("partial rectangular clip with one contiguous section in first and fourth quadrant")
    {
        Rectangle rect{{1, -2}, 2, 4};

        auto ts = ellipse.clip(rect, {});

        CHECK(ts.size() == 1);

        CHECK(ts[0].first == approx(2_pi - ellipse.tAtX(1)));
        CHECK(ts[0].second == approx(2_pi + ellipse.tAtX(1)));
    }

    /*
    SECTION("rectangular clip with transformed rectangle")
    {
        Rectangle rect{{-sqrt(8) / 2, -sqrt(8) / 2}, {sqrt(8), sqrt(8)}};
        Transform transform;
        transform.rotate(0.25_pi);

        fmt::print("bottom-left: {}\n", transform.apply(rect.bottomLeft()));

        //auto ts = ellipse.clip(rect, {});
        //fmt::print("ts: {}\n", ts);

        //CHECK(ts.size() == 2);

        //CHECK(ts[0].first == Approx(2_pi + ellipse.tAtY(-1)));
        //CHECK(ts[0].second == Approx(2_pi + ellipse.tAtX(-1)));
    }
     */

}
