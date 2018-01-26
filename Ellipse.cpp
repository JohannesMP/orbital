//
// Created by jim on 26.01.18.
//

#include "Ellipse.h"

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
Ellipse::point(double t) const
{
    return {
            mA * cos(t),
            mB * sin(t)
    };
}

double
Ellipse::arcLength(
        double ts,
        double te,
        double resolution
)
{
    double sqA = sq(mA);
    double sqB = sq(mB);
    return integral(
            [&](double x) {
                // sqrt( a² sin²x + b² cos²x )
                return sqrt(sqA * sq(sin(x)) + sqB * sq(cos(x)));
            }, ts, te, resolution
    );
}
