//
// Created by jim on 26.01.18.
//

#include "Ellipse.h"
#include <iostream>
#include <fmt/printf.h>
#include <iterator>

Ellipse::Ellipse(
        Decimal a,
        Decimal e
)
{
    mA = a;
    mE = e;
    mB = a * std::sqrt(1 - sq(e));   // b = a √( 1 - e² )
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
        // √( a² sin²x + b² cos²x )
        return std::sqrt(sqA * sq(std::sin(x)) + sqB * sq(std::cos(x)));
    }, ts, te, resolution);
}

vec
Ellipse::pointAngle(
        Decimal radians
) const
{
    /*
     * Point from given angle θ:
     *
     * (
     *  ab / √( b² + a² tan² θ )
     *  ab tan θ / √( b² + a² tan² θ )
     * )
     *
     * Negate for angles: 0.5 π < θ ≦ 1.5 π
     *
     */
    // √( b² + a² tan² θ )
    Decimal denominator = std::sqrt(sq(mB) + sq(mA) * sq(std::tan(radians)));
    vec p{mA * mB / denominator, mA * mB * std::tan(radians) / denominator};
    if (0.5_pi < radians && 1.5_pi >= radians)
    {
        p = -p;
    }
    return p;
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

    /*
     * Actually, an ellipse can be defined through a set of points, to which the following is valid:
     *     2a = |p - f0| + |p - f1|
     * Where f0 and f1 are the two focal points.
     * Therefore, any points whose accumulated distance is equal or less to 2a is considered inside the ellipse body.
     */
    return 2 * mA >= distance(fociPoints()[0], p) + distance(fociPoints()[1], p);
}

Decimal
Ellipse::tAtX(Decimal x) const
{
    /*
     * x = a cos t
     * t = acos (x/a)
     */
    return std::acos(x / mA);
}

Decimal
Ellipse::tAtY(Decimal y) const
{
    /*
     * y = b sin t
     * t = asin (y/b)
     */
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

// TODO: Clip points *must* increase with index position
// TODO: How to specify no-clip/all-clip

std::vector<std::pair<Decimal, Decimal>>
Ellipse::clip(
        const Rectangle &rect
) const
{
    std::vector<std::pair<Decimal, Decimal>> result;

    Rectangle bounds = boundingRect();
    Rectangle clipping = bounds.conjunction(rect);

    if (clipping.extent() == vec{})
    {
        // Rect lies outside of ellipse
        return {};
    }

    Rectangle topRight = clipping.conjunction({{}, mA, mB});
    Rectangle topLeft = clipping.conjunction({{}, -mA, mB});
    Rectangle bottomRight = clipping.conjunction({{}, mA, -mB});
    Rectangle bottomLeft = clipping.conjunction({{}, -mA, -mB});

    /*fmt::print("Ellipse:   {}\n", *this);
    fmt::print("Clipping:  {}\n", clipping);
    fmt::print("Top-Right: {}\n", topRight);
    fmt::print("Top-Left:  {}\n", topLeft);
    fmt::print("Bot-Right: {}\n", bottomRight);
    fmt::print("Bot-Left:  {}\n", bottomLeft);*/

    auto insertPair = [&](
            Decimal d0,
            Decimal d1
    ) {
        //if (d0 < d1)
        //if(true)
        {
            //fmt::print("Inserting pair:  {}π  ->  {}π\n", d0 / PI, d1 / PI);
            result.emplace_back(d0, d1);
        }
        //else
        {
            //fmt::print("Ignoring pair:  {}π  ->  {}π\n", d0 / PI, d1 / PI);
        }
    };

    if (topRight.extent() != vec() && !contains(topRight.topRight()))
    {
        insertPair(tAtX(topRight.right()), tAtY(topRight.top()));
    }

    if (topLeft.extent() != vec() && !contains(topLeft.topLeft()))
    {
        insertPair(tAtY(topLeft.top()), tAtX(topLeft.left()));
    }

    if (bottomLeft.extent() != vec() && !contains(bottomLeft.bottomLeft()))
    {
        insertPair(2_pi - std::abs(tAtX(bottomLeft.left())), 2_pi - std::abs(tAtY(bottomLeft.bottom())));
    }

    if (bottomRight.extent() != vec() && !contains(bottomRight.bottomRight()))
    {
        insertPair(2_pi - std::abs(tAtY(bottomRight.bottom())), 2_pi - std::abs(tAtX(bottomRight.right())));
    }

    for (int i = 0; i < result.size(); i++)
    {
        fmt::print("result[{}]:   {}π  ->  {}π\n", i, result[i].first / 1_pi, result[i].second / 1_pi);
    }

    return result;
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
