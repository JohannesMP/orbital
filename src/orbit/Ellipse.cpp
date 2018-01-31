//
// Created by jim on 26.01.18.
//

#include "Ellipse.h"
#include <iostream>
#include <fmt/printf.h>
#include <iterator>
#include "constants.h"

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
        Decimal theta
) const
{
    // Point from given angle θ:
    //
    // x = ± (ab cos θ) / √((b cos θ)² + (a cos θ)²)
    // y = ± (ab sin θ) / √((b cos θ)² + (a cos θ)²)

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

    // Actually, an ellipse can be defined through a set of points, to which the following is valid:
    //     2a = |p - f0| + |p - f1|
    // Where f0 and f1 are the two focal points.
    // Therefore, any points whose accumulated distance is equal or less to 2a is considered inside the ellipse body.
    return 2 * mA >= distance(fociPoints()[0], p) + distance(fociPoints()[1], p);
}

Decimal
Ellipse::tAtX(Decimal x) const
{
    // x = a cos t
    // t = acos (x/a)
    return std::acos(x / mA);
}

Decimal
Ellipse::tAtY(Decimal y) const
{
    // y = b sin t
    // t = asin (y/b)
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
        const Rectangle &rect
) const
{
    std::vector<std::pair<Decimal, Decimal>> result;
    result.reserve(4); // At most 4 lines are added to the list, since the ellipse is divided into 4 quarters

    // Calculate the 4 quarter rectangles, which are always clipped to the ellipse bounds,
    // to avoid invalid x-y values passed to t queries:

    vec topRight;
    topRight.x = std::min(mA, rect.right());
    topRight.y = std::min(mB, rect.top());

    vec topLeft;
    topLeft.x = std::max(-mA, rect.left());
    topLeft.y = std::min(mB, rect.top());

    vec bottomRight;
    bottomRight.x = std::min(mA, rect.right());
    bottomRight.y = std::max(-mB, rect.bottom());

    vec bottomLeft;
    bottomLeft.x = std::max(-mA, rect.left());
    bottomLeft.y = std::max(-mB, rect.bottom());

    std::clog << std::endl;


    if (!contains(topRight))
    {
        // Top right quarter:
        std::clog << "top-right: " << topRight << std::endl;
        result.emplace_back(tAtX(topRight.x), tAtY(topRight.y));
    }

    if (!contains(topLeft))
    {
        // Top left quarter:
        std::clog << "top-left:  " << topLeft << std::endl;
        result.emplace_back(1_pi - tAtY(topLeft.y), tAtX(topLeft.x));
    }

    if (!contains(bottomLeft))
    {
        // Bottom left quarter, ensure that t stays positive be inverting its direction:
        std::clog << "bot-right: " << bottomRight << std::endl;
        result.emplace_back(2_pi - std::abs(tAtX(bottomLeft.x)), 2_pi - std::abs(tAtY(bottomLeft.y)));
    }

    if (!contains(bottomRight))
    {
        // Bottom left quarter, ensure that t stays positive be inverting its direction:
        std::clog << "bot-left:  " << bottomLeft << std::endl;
        result.emplace_back(2_pi - std::abs(tAtY(bottomRight.y)), 2_pi - std::abs(tAtX(bottomRight.x)));
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
