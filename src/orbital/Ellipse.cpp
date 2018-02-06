//
// Created by jim on 26.01.18.
//

#include "Ellipse.h"
#include <iterator>
#include <numeric>

Ellipse::Ellipse(
        Decimal a,
        Decimal e
)
{
    mA = a;
    mE = e;
    mB = a * std::sqrt(1 - sq(e));
    mFoci = a * e;
}

Decimal
Ellipse::a() const
{
    return mA;
}

Decimal
Ellipse::b() const
{
    return mB;
}

Decimal
Ellipse::e() const
{
    return mE;
}

std::array<Decimal, 2>
Ellipse::foci() const
{
    return {-mFoci, mFoci};
}

std::array<vec, 2>
Ellipse::fociPoints() const
{
    return {{{-mFoci, 0}, {mFoci, 0}}};
}

vec
Ellipse::point(
        Decimal t
) const
{
    return {mA * std::cos(t), mB * std::sin(t)};
}

Decimal
Ellipse::arcLength(
        Decimal ts,
        Decimal te,
        Decimal resolution
) const
{
    Decimal sqA = sq(mA);
    Decimal sqB = sq(mB);
    return integral([&](Decimal x) {
        return std::sqrt(sqA * sq(std::sin(x)) + sqB * sq(std::cos(x)));
    }, ts, te, resolution);
}

vec
Ellipse::pointAngle(
        Decimal theta
) const
{
    Decimal denominator = std::sqrt(sq(mB * std::cos(theta)) + sq(mA * std::sin(theta))) / mA / mB;
    return {std::cos(theta) / denominator, std::sin(theta) / denominator};
}

bool
Ellipse::contains(
        const vec &p
) const
{
    if (p.x == 0 && p.y == 0)
    {
        // The center is guaranteed to be contained:
        return true;
    }
    if (p.y == 0 && p.x <= mA && p.x >= -mA)
    {
        // p lies on the x-axis covered be the ellipse:
        return true;
    }
    if (p.x == 0 && p.y <= mB && p.y >= -mB)
    {
        // p lies on the y-axis covered by the ellipse:
        return true;
    }

    return 2 * mA >= distance(fociPoints()[0], p) + distance(fociPoints()[1], p);
}

Decimal
Ellipse::tAtX(Decimal x) const
{
    return std::acos(x / mA);
}

Decimal
Ellipse::tAtY(Decimal y) const
{
    return std::asin(y / mB);
}

bool
Ellipse::contains(
        const Rectangle &rect
) const
{
    return contains(rect.bottomLeft()) && contains(rect.bottomRight()) && contains(rect.topLeft()) &&
            contains(rect.topRight());
}

DynamicArray<std::pair<Decimal, Decimal>, 4>
Ellipse::clip(
        const Rectangle &rect,
        const Transform &transform
) const
{
    DynamicArray<std::pair<Decimal, Decimal>, 4> result;
    DynamicArray<Decimal, 8> intersectionPoints;

    // TODO: outsource into own function:
    auto pointToT = [&](vec p) {
        Decimal const t = tAtX(p.x);
        return p.y >= 0 ? t : 2_pi - t;
    };

    auto appendIntersectionPoints = [&](DynamicArray<vec, 2> points) {
        fmt::print("Try to append {} new intersection points\n", points.size());
        for (auto const &point : points)
        {
            fmt::print("Append intersection point {} mapping to t={}\n", point, pointToT(point));
            intersectionPoints.emplace_back(pointToT(point));
        }
    };

    // Append intersections from line: bottom left - top left
    {
        vec const p = transform.apply(rect.bottomLeft());
        vec const d = transform.apply(rect.topLeft() - rect.bottomLeft());
        fmt::print("Rect line: {} + λ{}\n", p, d);
        appendIntersectionPoints(
                intersectPoints({transform.apply(rect.bottomLeft()), transform.apply(rect.topLeft())}, true));
    }

    // Append intersections from line: bottom left - bottom right
    {
        vec const p = transform.apply(rect.bottomLeft());
        vec const d = transform.apply(rect.bottomRight() - rect.bottomLeft());
        fmt::print("Rect line: {} + λ{}\n", p, d);
        appendIntersectionPoints(
                intersectPoints({transform.apply(rect.bottomLeft()), transform.apply(rect.bottomRight())}, true));
    }

    // Append intersections from line: top right - top left
    appendIntersectionPoints(
            intersectPoints({transform.apply(rect.topRight()), transform.apply(rect.topLeft())}, true));

    // Append intersections from line: top right - bottom right
    appendIntersectionPoints(
            intersectPoints({transform.apply(rect.topRight()), transform.apply(rect.bottomRight())}, true));

    // Sort intersection t-parameters:
    std::sort(intersectionPoints.begin(), intersectionPoints.end());

    fmt::print("Intersection points ({}): ", intersectionPoints.size());
    for (auto const &i : intersectionPoints)
    {
        fmt::print("{}", i);
    }
    fmt::print("\n");

    // No intersection points
    // -> Check any point for containment
    // -> false => Complete rect-angle lies outside, therefore the ellipse is visible and nothing is clipped away:
    if (intersectionPoints.size() < 2)
    {
        if (!contains(transform.apply(rect.bottomLeft())))
        {
            fmt::print("Complete ellipse is visible - nothing is clipped\n");
            result.emplace_back(0, 2_pi);
        }
        else
        {
            fmt::print("Complete ellipse is invisible - everything is clipped away\n");
        }
        return result;
    }

    // Check whether first section lies within the transformed rect:
    Decimal t = std::abs(intersectionPoints[1] - intersectionPoints[0]) / 2.0;
    vec p = point(t);
    if (rect.containsTransformed(transform, p))
    {
        // Lies within:
        for(auto iter = intersectionPoints.begin(); iter != intersectionPoints.end(); iter += 2)
        {
            result.emplace_back(*iter, *(iter + 1));
        }
    }
    else
    {

        for(auto iter = intersectionPoints.begin() + 1; iter != intersectionPoints.end(); iter += 2)
        {
            result.emplace_back(*iter, *(iter + 1));
        }
        result.emplace_back(intersectionPoints.back(), 2_pi + intersectionPoints.front());
    }
}

std::ostream &
operator<<(
        std::ostream &os,
        const Ellipse &ellipse
)
{
    os << "a: " << ellipse.mA << " b: " << ellipse.mB << " e: " << ellipse.mE;
    return os;
}

Rectangle
Ellipse::boundingRect() const
{
    return {{-mA, -mB}, {mA, mB}};
}

DynamicArray<vec, 2>
Ellipse::intersectPoints(
        Line line,
        bool clipToLine
) const
{

    Decimal const d0 = line.d().x;
    Decimal const d1 = line.d().y;
    Decimal const p0 = line.p().x;
    Decimal const p1 = line.p().y;

    Decimal const a2 = sq(mA);
    Decimal const b2 = sq(mB);

    Decimal const A = b2 * sq(d0) + a2 * sq(d1);
    Decimal const B = 2 * (b2 * p0 * d0 + a2 * p1 * d1);
    Decimal const C = b2 * sq(p0) + a2 * sq(p1) - a2 * b2;

    auto const lambdas = quadratic(A, B, C);

    DynamicArray<vec, 2> points;

    for(auto const lambda : lambdas)
    {
        vec const intersection = line.point(lambda);
        if(!clipToLine || line.containsByBounds(intersection))
        {
            // Store intersection only if either not clipped to line bounds or the point does lie within bounds:
            points.push_back(intersection);
        }
    }

    return points;
}

Ellipse
Ellipse::fromAB(
        Decimal a,
        Decimal b
)
{
    return Ellipse{a, sqrt(1 - sq(b / a))};
}
