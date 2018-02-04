//
// Created by jim on 26.01.18.
//

#include "Ellipse.h"
#include <iterator>
#include <numeric>
#include "LinearFunction.h"

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

std::vector<std::pair<Decimal, Decimal>>
Ellipse::clip(
        const Rectangle &rect,
        const Transform &transform
) const
{
    std::vector<std::pair<Decimal, Decimal>> result;
    result.reserve(4); // At most 4 lines are added to the list, since the ellipse is divided into 4 quarters

    std::vector<Decimal> intersectionPoints;

    // TODO: outsource into own function:
    auto pointToT = [&](vec p) {
        Decimal t = tAtX(p.x);
        if (p.y < 0)
        {
            // Flip t over:
            t = 2_pi - t;
        }
        return t;
    };

    auto appendIntersectionPoints = [&](std::pair<unsigned, std::array<vec, 2>> points) {
        fmt::print("Try to append {} new intersection points\n", points.first);
        for (unsigned i = 0; i < points.first; i++)
        {
            fmt::print("Append intersection point {} mapping to t={}\n", points.second[i], pointToT(points.second[i]));
            intersectionPoints.emplace_back(pointToT(points.second[i]));
        }
    };

    // Append intersections from line: bottom left - top left
    {
        vec p = transform.apply(rect.bottomLeft());
        vec d = transform.apply(rect.topLeft() - rect.bottomLeft());
        fmt::print("Rect line: {} + λ{}\n", p, d);
        appendIntersectionPoints(intersectPoints(transform.apply(rect.bottomLeft()),
                transform.apply(rect.topLeft() - rect.bottomLeft())));
    }

    // Append intersections from line: bottom left - bottom right
    {
        vec p = transform.apply(rect.bottomLeft());
        vec d = transform.apply(rect.bottomRight() - rect.bottomLeft());
        fmt::print("Rect line: {} + λ{}\n", p, d);
        appendIntersectionPoints(intersectPoints(transform.apply(rect.bottomLeft()),
                transform.apply(rect.bottomRight() - rect.bottomLeft())));
    }

    // Append intersections from line: top right - top left
    appendIntersectionPoints(
            intersectPoints(transform.apply(rect.topRight()), transform.apply(rect.topLeft() - rect.topRight())));

    // Append intersections from line: top right - bottom right
    appendIntersectionPoints(
            intersectPoints(transform.apply(rect.topRight()), transform.apply(rect.bottomRight() - rect.topRight())));

    // Sort intersection t-parameters:
    std::sort(intersectionPoints.begin(), intersectionPoints.end());

    fmt::print("Intersection points ({}): ", intersectionPoints.size());
    for (auto &i : intersectionPoints)
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
        for (unsigned i = 0; i < intersectionPoints.size(); i += 2)
        {
            result.emplace_back(intersectionPoints[i], intersectionPoints[i + 1]);
        }
    }
    else
    {
        for (unsigned i = 1; i < intersectionPoints.size(); i += 2)
        {
            result.emplace_back(intersectionPoints[i], intersectionPoints[i + 1]);
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

std::pair<unsigned, std::array<vec, 2>>
Ellipse::intersectPoints(
        const vec &p,
        const vec &d
) const
{
    std::array<vec, 2> points;

    Rectangle lineBounds{p, p + d};

    if (d.x != 0)
    {
        LinearFunction f{p, d};

        unsigned intersectionCount;
        std::array<Decimal, 2> solutions;
        std::tie(intersectionCount, solutions) = quadratic(mB + mA * sq(f.m()), 2 * mA * f.m() * f.t(),
                mA * (sq(f.t()) - mB));

        unsigned pI = 0;
        for (unsigned i = 0; i < intersectionCount; i++)
        {
            vec v{solutions[i], f(solutions[i])};
            if (lineBounds.contains(v))
            {
                points[pI++] = v;
            }
        }

        return {pI, points};
    }

    else
    {
        if (p.x < -mA || p.x > mA)
        {
            // No solution:
            return {0, {}};
        }

        if (p.x == -mA || p.x == mA)
        {
            // One solution, left most or right most point:
            return {1, {vec{p.x, 0}}};
        }

        // Compute the point on the upper ellipse half using t-parameter:
        vec intersectionPosY = point(tAtX(p.x));
        vec intersectionNegY = point(2_pi - tAtX(p.x));

        // Check if intersections are covered by given line and return them:
        unsigned pI = 0;
        if (p.y <= intersectionNegY.y && (p.y + d.y) >= intersectionNegY.y)
        {
            points[pI++] = intersectionNegY;
        }
        if (p.y <= intersectionPosY.y && (p.y + d.y) >= intersectionPosY.y)
        {
            points[pI++] = intersectionPosY;
        }
        return {pI, points};
    }
}
