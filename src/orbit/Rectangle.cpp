//
// Created by jim on 26.01.18.
//

#include "Rectangle.h"

const Rectangle Rectangle::ZERO_RECTANGLE{{0, 0}, 0, 0};

Rectangle::Rectangle(
        const vec &p,
        Decimal w,
        Decimal h
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
    os << "rect{" << rectangle.mBottomLeft << " -> " << rectangle.mW << 'x' << rectangle.mH << "}";
    return os;
}

Rectangle
Rectangle::conjunction(const Rectangle &rhs) const
{
    if(top() <= rhs.bottom()) {
        // rhs lies above this rect
        return ZERO_RECTANGLE;
    }
    if(bottom() >= rhs.top()) {
        // rhs lies below this rect
        return ZERO_RECTANGLE;
    }
    if(left() >= rhs.right()) {
        // rhs lies right
        return ZERO_RECTANGLE;
    }
    if(right() <= rhs.left()) {
        // rhs lies left
        return ZERO_RECTANGLE;
    }

    return {
            {
                    std::max(left(), rhs.left()),
                    std::max(bottom(), rhs.bottom())
            },
            {
                    std::min(right(), rhs.right()),
                    std::min(top(), rhs.top())
            }
    };
}
