//
// Created by jim on 26.01.18.
//

#pragma once

#include <ostream>
#include "constants.h"

class Rectangle
{

public:

    /**
     * A rectangle with no extent, sitting at position 0.
     */
    static const Rectangle ZERO_RECTANGLE;

    /**
     * Construct a rectangle from a point, width and height.
     * @param p Start point.
     * @param w Width, can be negative.
     * @param h Height, can be negative.
     */
    Rectangle(
            const vec &p,
            Decimal w,
            Decimal h
    );

    /**
     * Construct a rectangle spanning over two points.
     * @param p First point.
     * @param q Second point.
     */
    Rectangle(
            const vec &p,
            const vec &q
    );

    /**
     * Create a conjunction rectangle from this and another rectangle.
     * @param rhs Other rectangle.
     * @return Conjunction. If rectangles do not overlap, the conjunction is a zero rectangle.
     */
    Rectangle
    conjunction(
            const Rectangle &rhs
    ) const;

    vec
    extent() const;

    Decimal
    top() const;

    Decimal
    bottom() const;

    Decimal
    left() const;

    Decimal
    right() const;

    vec
    bottomLeft() const;

    vec
    topLeft() const;

    vec
    bottomRight() const;

    vec
    topRight() const;

    vec
    leftCenter() const;

    vec
    rightCenter() const;

    vec
    topCenter() const;

    vec
    bottomCenter() const;

    vec
    center() const;

    friend std::ostream &
    operator<<(
            std::ostream &os,
            const Rectangle &rectangle
    );

private:

    vec mBottomLeft;
    Decimal mW;
    Decimal mH;

};


