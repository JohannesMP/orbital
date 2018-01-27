//
// Created by jim on 26.01.18.
//

#include "Rectangle.h"

Rectangle::Rectangle(
        const vec &p,
        double w,
        double h
)
        : Rectangle{p, {p.x + w, p.y + h}}
{
}

Rectangle::Rectangle(
        const vec &p,
        const vec &q
)
        : mBottomLeft{std::min(p.x, q.x), std::min(p.y, q.y)}
        , mW{std::abs(q.x - p.x)}
        , mH{std::abs(q.y - p.y)}
{
}

double
Rectangle::top() const
{
    return mBottomLeft.y + mH;
}

double
Rectangle::bottom() const
{
    return mBottomLeft.y;
}

double
Rectangle::left() const
{
    return mBottomLeft.x;
}

double
Rectangle::right() const
{
    return mBottomLeft.x + mW;
}

vec
Rectangle::bottomLeft() const
{
    return mBottomLeft;
}

vec
Rectangle::topLeft() const
{
    return {mBottomLeft.x, mBottomLeft.y + mH};
}

vec
Rectangle::bottomRight() const
{
    return {mBottomLeft.x + mW, mBottomLeft.y};
}

vec
Rectangle::topRight() const
{
    return {mBottomLeft.x + mW, mBottomLeft.y + mH};
}

vec
Rectangle::leftCenter() const
{
    return {mBottomLeft.x, mBottomLeft.y + mH / 2};
}

vec
Rectangle::rightCenter() const
{
    return {mBottomLeft.x + mW, mBottomLeft.y + mH / 2};
}

vec
Rectangle::topCenter() const
{
    return {mBottomLeft.x + mW / 2, mBottomLeft.y + mH};
}

vec
Rectangle::bottomCenter() const
{
    return {mBottomLeft.x + mW / 2, mBottomLeft.y};
}

vec
Rectangle::center() const
{
    return {mBottomLeft.x + mW / 2, mBottomLeft.y + mH / 2};
}
