//
// Created by jim on 05.02.18.
//

#include "Line.h"
#include "Rectangle.h"

Line::Line(
        vec p0,
        vec p1
)
    : mP{p0}
    , mD{p1 - p0}
{
}

vec
Line::p() const
{
    return mP;
}

vec
Line::d() const
{
    return mD;
}

vec
Line::point(Decimal lambda)
{
    return mP + lambda * mD;
}

bool
Line::containsByBounds(vec v)
{
    Rectangle bounds{mP, mP + mD};
    return bounds.contains(v);
}

std::ostream &
operator<<(
        std::ostream &os,
        const Line &line
)
{
    os << line.mP << " + λ" << line.mD;
    return os;
}

Line
Line::fromDirection(
        vec p,
        vec d
)
{
    return Line{p, p + d};
}
