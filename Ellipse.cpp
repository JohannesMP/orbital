//
// Created by jim on 26.01.18.
//

#include "Ellipse.h"
#include <iostream>

Ellipse::Ellipse(
        double a,
        double e
)
{
    mA = a;
    mE = e;
    mB = a * sqrt(1 - sq(e));   // b = a sqrt( 1 - e² )
    mFoci = a * e;
}

double
Ellipse::a() const
{
    return mA;
}

double
Ellipse::b() const
{
    return mB;
}

double
Ellipse::e() const
{
    return mE;
}

std::array<double, 2>
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
        double t
) const
{
    return {mA * cos(t), mB * sin(t)};
}

double
Ellipse::arcLength(
        double ts,
        double te,
        double resolution
) const
{
    double sqA = sq(mA);
    double sqB = sq(mB);
    return integral([&](double x) {
        // sqrt( a² sin²x + b² cos²x )
        return sqrt(sqA * sq(sin(x)) + sqB * sq(cos(x)));
    }, ts, te, resolution);
}

vec
Ellipse::pointAngle(
        double radians
) const
{
    // sqrt( b² + a² tan² θ )
    double denominator = sqrt(sq(mB) + sq(mA) * sq(tan(radians)));
    vec p{mA * mB / denominator, mA * mB * tan(radians) / denominator};
    if (0.5 * PI < radians && 1.5 * PI > radians)
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
    /*
     * Calculate t for given x, then check whether the given y is smaller/greater than the
     * calculated Y of t, depending whether y is positive or negative.
     *
     * x = a cos t
     * t = acos (x/a)
     *
     * Y = b sin t
     *
     * y > 0 && y < Y    => inside (with positive y value)
     * y < 0 && y > Y    => inside (with negative y value)
     */
    double t = acos(p.x / mA);

    // Flip result of t if y is negative, so the ellipse point is mapped to the lower half of the ellipse body:
    t = copysign(t, p.y);

    double Y = mB * sin(t);
    return (p.y > 0 && p.y < Y) || (p.y < 0 && p.y > Y);
}

bool
Ellipse::contains(
        const Rectangle &rect
) const
{
    return contains(rect.lowerLeft()) && contains(rect.lowerRight()) && contains(rect.upperLeft()) &&
            contains(rect.upperRight());
}

void
Ellipse::clip(
        const Rectangle &rect,
        double &ts,
        double &te
) const
{
    /*
     * - Split ellipse into 4 quarters
     * - Resolve the x-y-t equation system for each of them
     */

}
