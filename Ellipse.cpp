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
Ellipse::point(double t) const
{
    return {mA * cos(t), mB * sin(t)};
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
    return integral([&](double x) {
        // sqrt( a² sin²x + b² cos²x )
        return sqrt(sqA * sq(sin(x)) + sqB * sq(cos(x)));
    }, ts, te, resolution);
}

vec
Ellipse::pointAngle(double radians)
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
Ellipse::contains(const vec &p)
{
    double angle = atan2(length(p), p.x);
    vec onEllipse = pointAngle(angle);

    std::cout << "angle: " << (angle / PI * 180) << "°    on-ellipse: " << onEllipse << std::endl;

    return p.x <= onEllipse.x && p.y <= onEllipse.y;
}

bool
Ellipse::contains(
        const vec &p,
        double w,
        double h
)
{
    //return contains(p) && contains({p.x + w, p.y}) && contains({p.x, p.y + h}) && contains({p.x + w, p.y + h});
    bool ll = contains(p);
    bool lr = contains({p.x + w, p.y});
    bool ur = contains({p.x, p.y + h});
    bool ul = contains({p.x + w, p.y + h});
    return ll && lr && ul && ur;
}
