//
// Created by jim on 05.02.18.
//

#include "Line.h"
#include "Rectangle.h"

Line::Line(
        vec const p0,
        vec const p1
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
Line::point(Decimal const lambda) const
{
    return mP + lambda * mD;
}

bool
Line::containsByBounds(vec const v) const
{
    Rectangle bounds{mP, mP + mD};
    return bounds.contains(v);
}

Line
Line::fromDirection(
        vec const p,
        vec const d
)
{
    return Line{p, p + d};
}
