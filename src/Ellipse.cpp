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
    mB = a * sqrt(1 - sq(e));   // b = a √( 1 - e² )
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
        // √( a² sin²x + b² cos²x )
        return sqrt(sqA * sq(sin(x)) + sqB * sq(cos(x)));
    }, ts, te, resolution);
}

vec
Ellipse::pointAngle(
        double radians
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
    double denominator = sqrt(sq(mB) + sq(mA) * sq(tan(radians)));
    vec p{mA * mB / denominator, mA * mB * tan(radians) / denominator};
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
    if(p.x == 0 && p.y == 0)
    {
        // The center is guaranteed to be contained:
        return true;
    }
    if(p.y == 0 && p.x <= mA && p.x >= -mA)
    {
        // p lies on the x-axis covered be the ellipse:
        return true;
    }
    if(p.x == 0 && p.y <= mB && p.y >= -mB)
    {
        // p lies on the y-axis covered by the ellipse:
        return true;
    }

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
    return (p.y >= 0 && p.y <= Y) || (p.y <= 0 && p.y >= Y);
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

// TODO: Clip points *must* increase with index position
// TODO: How to specify no-clip/all-clip
std::vector<double>
Ellipse::clip(
        const Rectangle &rect
) const
{
    std::vector<double> result;

    double left = rect.left();
    double right = rect.right();
    double top = rect.top();
    double bottom = rect.bottom();

    if (top > mB && bottom < mB)
    {
        // Covers vertical slice:

        if (left < -mA && right > -mA)
        {
            // Clips left:
            result.emplace_back(tAtY(right));
            result.emplace_back(2_pi - tAtY(right));
        }

        else if (left > -mA && right < -mA)
        {
            // Clips middle:
            result.emplace_back(tAtY(right));
            result.emplace_back(tAtY(left));
            result.emplace_back(2_pi - tAtY(left));
            result.emplace_back(2_pi - tAtY(right));
        }

        else if (left < mA && right > mA)
        {
            // Clips right:
            result.emplace_back(2_pi - tAtY(left));
            result.emplace_back(2_pi + tAtY(left));
        }
    }

    else if (top < mB && bottom > -mB)
    {
        // Covers part in middle:

        if (left < -mA && right > mA && right < mA)
        {
            // Clips left:
            result.emplace_back(tAtX(top));
            result.emplace_back(tAtX(bottom));
        }

        else if (left > -mA && left < mA && right > mA)
        {
            // Clips right:
            result.emplace_back(tAtX(bottom));
            result.emplace_back(tAtX(2_pi + top));
        }
    }

    else if(left < -mA && right > mA)
    {
        // Covers horizontal slice:

        if(top > mB && bottom < mB && bottom > -mB)
        {
            // Clips top:
            double t = tAtY(bottom);
            result.emplace_back(t);
            result.emplace_back(1_pi - t);
        }

        else if(top < mB && top > -mB && bottom > -mB)
        {
            // Clips middle:
            result.emplace_back(1_pi - tAtX(top));
        }

    }

    return result;
}
