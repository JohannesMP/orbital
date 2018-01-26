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
     * Y = b sin t
     *
     * y > 0 && y < Y    => inside (with positive y value)
     * y < 0 && y > Y    => inside (with negative y value)
     */
    double t = tAtX(p.x);

    // Flip result of t if y is negative, so the ellipse point is mapped to the lower half of the ellipse body:
    t = copysign(t, p.y);

    double Y = mB * sin(t);
    return (p.y > 0 && p.y < Y) || (p.y < 0 && p.y > Y);
}

double
Ellipse::tAtX(double x) const
{
    /*
     * x = a cos t
     * t = acos (x/a)
     */
    return acos(x / mA);
}

double
Ellipse::tAtY(double y) const
{
    /*
     * y = b sin t
     * t = asin (y/b)
     */
    return asin(y / mB);
}

bool
Ellipse::contains(
        const Rectangle &rect
) const
{
    return contains(rect.bottomLeft()) && contains(rect.bottomRight()) && contains(rect.topLeft()) &&
            contains(rect.topRight());
}

std::vector<double>
Ellipse::clip(
        const Rectangle &rect
) const
{
    /*
     * - Split ellipse into 4 quarters (because within each quarter, all x and y are unique)
     * - Resolve the x-y-t equation system for each of them
     *
     * top < b => 2 clip-points
     * bottom > -b => 2 clip-points
     */

    std::vector<double> result;
    double left = rect.left();
    double right = rect.right();
    double top = rect.top();
    double bottom = rect.bottom();

    /*bool bl = contains(rect.bottomLeft());
    bool br = contains(rect.bottomRight());
    bool tl = contains(rect.topLeft());
    bool tr = contains(rect.topRight());
    bool l = contains(rect.leftCenter());
    bool r = contains(rect.rightCenter());
    bool t = contains(rect.topCenter());
    bool b = contains(rect.bottomCenter());*/



    auto clipQuarter = [&](
            double ts,
            double te
    ) {
    };

    clipQuarter(0, 0.5 * PI);

    return {};
}
