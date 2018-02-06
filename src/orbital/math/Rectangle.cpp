//
// Created by jim on 26.01.18.
//

#include "Rectangle.h"

Rectangle::Rectangle(
        vec const &p,
        Decimal const w,
        Decimal const h
)
        : Rectangle{p, {p.x + w, p.y + h}}
{
}

Rectangle::Rectangle(
        vec const &p,
        vec const &q
)
        : mBottomLeft{std::min(p.x, q.x), std::min(p.y, q.y)}
        , mW{std::abs(q.x - p.x)}
        , mH{std::abs(q.y - p.y)}
{
}

Decimal
Rectangle::top() const
{
    return mBottomLeft.y + mH;
}

Decimal
Rectangle::bottom() const
{
    return mBottomLeft.y;
}

Decimal
Rectangle::left() const
{
    return mBottomLeft.x;
}

Decimal
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

std::ostream &
operator<<(
        std::ostream &os,
        const Rectangle &rectangle
)
{
    os << "rect{" << rectangle.mBottomLeft << "->" << rectangle.mW << 'x' << rectangle.mH << "}";
    return os;
}

Rectangle
Rectangle::conjunction(const Rectangle &rhs) const
{
    if (top() <= rhs.bottom())
    {
        // rhs lies above this rect
        return zeroRectangle();
    }
    if (bottom() >= rhs.top())
    {
        // rhs lies below this rect
        return zeroRectangle();
    }
    if (left() >= rhs.right())
    {
        // rhs lies right
        return zeroRectangle();
    }
    if (right() <= rhs.left())
    {
        // rhs lies left
        return zeroRectangle();
    }

    return {{std::max(left(), rhs.left()), std::max(bottom(), rhs.bottom())},
            {std::min(right(), rhs.right()), std::min(top(), rhs.top())}};
}

vec
Rectangle::extent() const
{
    return {right() - left(), top() - bottom()};
}

bool
Rectangle::contains(
        vec const v
) const
{
    return v.x >= left() && v.x <= right() && v.y <= top() && v.y >= bottom();
}

bool
Rectangle::containsTransformed(
        Transform const transform,
        vec const p
) const
{
    vec const a = transform.apply(bottomLeft());
    vec const s = a - transform.apply(topLeft());
    vec const t = transform.apply(bottomRight()) - a;

    Decimal theta = (p.x + s.x - a.x) / t.x;
    Decimal mu = (p.y - a.y) / (t.y * theta - s.y);
    Decimal lambda = (p.x + s.x * mu - a.x) / t.x;

    // Both, mu and lambda must be [0;1], otherwise they refer to a point outside the rect:
    return mu >= 0 && mu <= 1 && lambda >= 0 && lambda <= 1;
}

Rectangle
Rectangle::zeroRectangle()
{
    return Rectangle{{}, 0, 0};
}
