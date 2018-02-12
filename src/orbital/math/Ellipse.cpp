//
// Created by jim on 26.01.18.
//

#include "Ellipse.h"

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
    return (p.x == 0 && p.y == 0) || (p.y == 0 && p.x <= mA && p.x >= -mA) || (p.x == 0 && p.y <= mB && p.y >= -mB) ||
            (2 * mA >= distance(focalPoints()[0], p) + distance(focalPoints()[1], p));
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

Decimal
Ellipse::pointToT(const vec v) const
{
    Decimal const t = tAtX(v.x);
    // Since t-from-x calculation can only return t's for positive y values, flip it over if y-value is negative:
    return v.y >= 0 ? t : 2_pi - t;
}

DynamicArray<std::pair<Decimal, Decimal>, 4>
Ellipse::clip(
        const Rectangle &rect,
        const Transform &transform
) const
{
    //DynamicArray<Decimal, 8> points;
    DynamicArray<std::pair<Decimal, Decimal>, 4> ranges;

    auto appendIntersectionPoints = [&](DynamicArray<vec, 2> const intersections) {
        if(intersections.size() < 2) {
            // Intersections only touching the ellipse are ignored:
            return;
        }

        // Store the range:

        Decimal const t0 = pointToT(intersections.front());
        Decimal const t1 = pointToT(intersections.back());

        // Rectangle contains either the range [t0, t1] or the *other* side:
        Decimal const t2 = average(t0, t1);

        if(rect.containsTransformed(transform.inverse(), point(t2)))
        {
            // Rectangle covers range [t0, t1]:
            ranges.emplace_back(t0, t1);
        }

        else
        {
            // Rectangle covers other side, i.e.: [t0, t1 + 2π]
            // The ... t1 + 2π ... is needed so the range flips over the other side of the ellipse:
            ranges.emplace_back(t0, t1 + 2_pi);
        }
    };

    // Append intersections from line: bottom left - top left
    appendIntersectionPoints(
            intersectPoints(Line{transform.apply(rect.bottomLeft()), transform.apply(rect.topLeft())}, true));

    // Append intersections from line: bottom left - bottom right
    appendIntersectionPoints(
            intersectPoints(Line{transform.apply(rect.bottomLeft()), transform.apply(rect.bottomRight())}, true));

    // Append intersections from line: top right - top left
    appendIntersectionPoints(
            intersectPoints(Line{transform.apply(rect.topRight()), transform.apply(rect.topLeft())}, true));

    // Append intersections from line: top right - bottom right
    appendIntersectionPoints(
            intersectPoints(Line{transform.apply(rect.topRight()), transform.apply(rect.bottomRight())}, true));

    fmt::print("Intersection ranges: ({}): {}\n", ranges.size(), ranges);

    // No intersection ranges:
    if (ranges.empty())
    {
        if (rect.containsTransformed(transform.inverse(), {0, 0}) &&
                rect.containsTransformed(transform.inverse(), {mA, 0}))
        {
            // Complete ellipse is visible, since rectangle contains both, the coordinate origin and the ellipse's
            // right-most point:
            ranges.emplace_back(0, 2_pi);
        }
        return ranges;
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
    return {{-mA, -mB}, {mA, mB}};
}

DynamicArray<vec, 2>
Ellipse::intersectPoints(
        Line const line,
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
