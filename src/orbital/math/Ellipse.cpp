//
// Created by jim on 26.01.18.
//

#include "Ellipse.h"
#include "elementary.h"

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
Ellipse::focalPoints() const
{
    return {{{-mFoci, 0}, {mFoci, 0}}};
}

vec
Ellipse::point(
        Radian t
) const
{
    return {mA * t.cos(), mB * t.sin()};
}

Radian
Ellipse::arcLength(
        Radian const ts,
        Radian const te,
        Decimal const resolution
) const
{
    Decimal sqA = sq(mA);
    Decimal sqB = sq(mB);
    return Radian{integral(ts, te, resolution, [&](Radian const x) {
        return Radian{std::sqrt(sqA * sq(x.sin()) + sqB * sq(x.cos()))};
    })};
}

vec
Ellipse::pointAngle(
        Radian theta
) const
{
    Decimal denominator = std::sqrt(sq(mB * theta.cos()) + sq(mA * theta.sin())) / mA / mB;
    return {theta.cos() / denominator, theta.sin() / denominator};
}

bool
Ellipse::contains(
        const vec &p
) const
{
    return (p.x == 0 && p.y == 0) || (p.y == 0 && p.x <= mA && p.x >= -mA) || (p.x == 0 && p.y <= mB && p.y >= -mB) ||
            (2 * mA >= distance(focalPoints()[0], p) + distance(focalPoints()[1], p));
}

Radian
Ellipse::tAtX(Decimal x) const
{
    return Radian::arccos(x / mA);
}

Radian
Ellipse::tAtY(Decimal y) const
{
    return Radian::arcsin(y / mB);
}

bool
Ellipse::contains(
        const Rectangle &rect
) const
{
    return contains(rect.bottomLeft()) && contains(rect.bottomRight()) && contains(rect.topLeft()) &&
            contains(rect.topRight());
}

Radian
Ellipse::pointToT(const vec v) const
{
    Radian const t = tAtX(v.x);
    // Since t-from-x calculation can only return t's for positive y values, flip it over if y-value is negative:
    return v.y >= 0 ? t : 2_pi - t;
}

/*
 * How the algorithm works:
 * 1) Simple store all intersection points between the ellipse and the 4 edge lines.
 *      Edge case: If a line has 1 intersection, but both end points lie outside of the ellipse,
 *      the intersection is ignored, since it only touches the ellipse. TODO: outsource to intersectionPoints()
 *      Edge case: If one line's endpoint lies on the ellipse, it is ignored as well.
 *    After that, 'points' should have an even number of elements.
 * 2) Check if the first two elements denote a range covered be the rectangle.
 *    If so, the elements are already in-order, so their can iteratively copied to the resulting ranges.
 *    Otherwise, the elements are in shifted-order, so the rectangle covers the range denoted by the second and third,
 *    fourth and fifth, ... element and the range between the last and the first element. In this case 2π should be
 *    added to the first element, so it's greater in value than the last element.
 */
DynamicArray<std::pair<Radian, Radian>, 4>
Ellipse::clip(
        const Rectangle &rect,
        const Transform &transform
) const
{
    DynamicArray<Radian, 8> points;
    DynamicArray<std::pair<Radian, Radian>, 4> ranges;

    // Store valid intersections of line, representing a transformed edge of the rectangle:
    auto storeIntersections = [&](Line<Decimal> const &line) {
        auto const intersections = intersectPoints(line, true);

        if (intersections.size() == 0)
        {
            return;
        }

        if (intersections.size() == 1 && !contains(line.point(0)) && !contains(line.point(1)))
        {
            return;
        }

        if (intersections.size() == 1 &&
                ((intersections.front() == line.point(0)) || (intersections.front() == line.point(1))))
        {
            return;
        }

        for(auto const &i : intersections)
        {
            points.emplace_back(pointToT(i));
        }
    };

    // Append intersections from line: bottom left - top left
    storeIntersections(Line{transform.apply(rect.bottomLeft()), transform.apply(rect.topLeft())});

    // Append intersections from line: bottom left - bottom right
    storeIntersections(Line{transform.apply(rect.bottomLeft()), transform.apply(rect.bottomRight())});

    // Append intersections from line: top right - top left
    storeIntersections(Line{transform.apply(rect.topRight()), transform.apply(rect.topLeft())});

    // Append intersections from line: top right - bottom right
    storeIntersections(Line{transform.apply(rect.topRight()), transform.apply(rect.bottomRight())});

    std::sort(points.begin(), points.end());

    // No intersection ranges:
    if (points.empty())
    {
        if (rect.containsTransformed(transform.inverse(), {0, 0}) &&
                rect.containsTransformed(transform.inverse(), {mA, 0}))
        {
            // Complete ellipse is visible, since rectangle contains both, the coordinate origin and the ellipse's
            // right-most point:
            ranges.emplace_back(0, 2_pi);
        }
    }

    else
    {
        Radian const t = average(points[0], points[1]);
        vec const p = point(t);

        if(rect.containsTransformed(transform.inverse(), p))
        {
            // points are in-order, simple copy them:
            for(auto iter = points.begin(); iter != points.end(); iter += 2)
            {
                ranges.emplace_back(*iter, *(iter + 1));
            }
        }

        else
        {
            // points are in shifted-order:
            for(auto iter = points.begin() + 1; iter != points.end() - 1; iter++)
            {
                ranges.emplace_back(*iter, *(iter + 1));
            }
            ranges.emplace_back(points.back(), points.front() + 2_pi);
        }
    }

    return ranges;
}

std::ostream &
operator<<(
        std::ostream &os,
        const Ellipse &ellipse
)
{
    os << "a=" << ellipse.mA << " b=" << ellipse.mB << " e=" << ellipse.mE;
    return os;
}

Rectangle
Ellipse::boundingRect() const
{
    return Rectangle{{-mA, -mB}, {mA, mB}};
}

DynamicArray<vec, 2>
Ellipse::intersectPoints(
        Line<Decimal> const line,
        bool const clipToLine
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

    for (auto const lambda : lambdas)
    {
        vec const intersection = line.point(lambda);
        if (!clipToLine || line.containsByBounds(intersection))
        {
            // Store intersection only if either not clipped to line bounds or the point does lie within bounds:
            points.push_back(intersection);
        }
    }

    return points;
}

Ellipse
Ellipse::fromAB(
        const Decimal a,
        const Decimal b
)
{
    return Ellipse{a, sqrt(1 - sq(b / a))};
}

vec
Ellipse::projection(vec const v) const
{
    return v * ((mA * mB) / std::sqrt(sq(mA) * sq(v.y) + sq(mB) * sq(v.x)));
}
