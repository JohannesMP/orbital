//
// Created by jim on 26.01.18.
//

#pragma once

#include "Transform.h"
#include "orbital/common/common.h"

template<class T>
class Rectangle
{

public:

    /**
     * Construct a rectangle from a point, width and height.
     * @param p Start point.
     * @param w Width, can be negative.
     * @param h Height, can be negative.
     */
    Rectangle(
            tvec<T> const p,
            T const w,
            T const h
    )
            : Rectangle{p, {p.x + w, p.y + h}}
    {
    }

    /**
     * Construct a rectangle spanning over two points.
     * @param p First point.
     * @param q Second point.
     */
    explicit Rectangle(
            tvec<T> const p,
            tvec<T> const q
    )
            : mBottomLeft{std::min(p.x, q.x), std::min(p.y, q.y)}
            , mW{std::abs(q.x - p.x)}
            , mH{std::abs(q.y - p.y)}
    {
    }

    /**
     * A rectangle with no extent, sitting at position 0.
     */
    static Rectangle zeroRectangle()
    {
        return Rectangle{{}, 0, 0};
    }


    /**
     * Create a conjunction rectangle from this and another rectangle.
     * @param rhs Other rectangle.
     * @return Conjunction. If rectangles do not overlap, the conjunction is a zero rectangle.
     */
    Rectangle
    conjunction(
            const Rectangle rhs
    ) const
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

        return Rectangle{{std::max(left(), rhs.left()), std::max(bottom(), rhs.bottom())},
                {std::min(right(), rhs.right()), std::min(top(), rhs.top())}};
    }

    /**
     * Checks whether a given point lies within the area covered by this transformed rectangle.
     * @param transform A transform to apply to this rectangle.
     * @param p Point to check. Transform is **not** applied to this point.
     * @return True if point lies within transformed rectangle.
     */
    bool
    containsTransformed(
            Transform<T> const transform,
            vec const p
    ) const
    {
        vec const a = transform.apply(bottomLeft());
        vec const s = a - transform.apply(topLeft());
        vec const t = transform.apply(bottomRight()) - a;

        T theta = (p.x + s.x - a.x) / t.x;
        T mu = (p.y - a.y) / (t.y * theta - s.y);
        T lambda = (p.x + s.x * mu - a.x) / t.x;

        // Both, mu and lambda must be [0;1], otherwise they refer to a point outside the rect:
        return mu >= 0 && mu <= 1 && lambda >= 0 && lambda <= 1;
    }

    vec
    extent() const
    {
        return {right() - left(), top() - bottom()};
    }

    T
    top() const
    {
        return mBottomLeft.y + mH;
    }

    T
    bottom() const
    {
        return mBottomLeft.y;
    }

    T
    left() const
    {
        return mBottomLeft.x;
    }

    T
    right() const
    {
        return mBottomLeft.x + mW;
    }

    vec
    bottomLeft() const
    {
        return mBottomLeft;
    }

    vec
    topLeft() const
    {
        return {mBottomLeft.x, mBottomLeft.y + mH};
    }

    vec
    bottomRight() const
    {
        return {mBottomLeft.x + mW, mBottomLeft.y};
    }

    vec
    topRight() const
    {
        return {mBottomLeft.x + mW, mBottomLeft.y + mH};
    }

    vec
    leftCenter() const
    {
        return {mBottomLeft.x, mBottomLeft.y + mH / 2};
    }

    vec
    rightCenter() const
    {
        return {mBottomLeft.x + mW, mBottomLeft.y + mH / 2};
    }

    vec
    topCenter() const
    {
        return {mBottomLeft.x + mW / 2, mBottomLeft.y + mH};
    }

    vec
    bottomCenter() const
    {
        return {mBottomLeft.x + mW / 2, mBottomLeft.y};
    }

    vec
    center() const
    {
        return {mBottomLeft.x + mW / 2, mBottomLeft.y + mH / 2};
    }

    bool
    contains(
            vec const v
    ) const
    {
        return v.x >= left() && v.x <= right() && v.y <= top() && v.y >= bottom();
    }

    friend std::ostream &
    operator<<(
            std::ostream &os,
            Rectangle const &rectangle
    )
    {
        os << "rect{" << rectangle.mBottomLeft << "->" << rectangle.mW << 'x' << rectangle.mH << "}";
        return os;
    }

private:

    tvec<T> const mBottomLeft;
    T const mW;
    T const mH;

};


