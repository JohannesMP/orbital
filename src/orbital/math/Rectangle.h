//
// Created by jim on 26.01.18.
//

#pragma once

#include "Transform.h"
#include "orbital/common/common.h"
#include <ostream>

class Rectangle
{

public:

    /**
     * A rectangle with no extent, sitting at position 0.
     */
    static Rectangle zeroRectangle();

    /**
     * Construct a rectangle from a point, width and height.
     * @param p Start point.
     * @param w Width, can be negative.
     * @param h Height, can be negative.
     */
    Rectangle(
            vec const &p,
            Decimal const w,
            Decimal const h
    );

    /**
     * Construct a rectangle spanning over two points.
     * @param p First point.
     * @param q Second point.
     */
    Rectangle(
            vec const &p,
            vec const &q
    );

    /**
     * Create a conjunction rectangle from this and another rectangle.
     * @param rhs Other rectangle.
     * @return Conjunction. If rectangles do not overlap, the conjunction is a zero rectangle.
     */
    Rectangle
    conjunction(
            Rectangle const &rhs
    ) const;

    /**
     * Checks whether a given point lies within the area covered by this transformed rectangle.
     * @param transform A transform to apply to this rectangle.
     * @param p Point to check. Transform is **not** applied to this point.
     * @return True if point lies within transformed rectangle.
     */
    bool
    containsTransformed(
            Transform const transform,
            vec const p
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

    bool
    contains(
            vec const v
    ) const;

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


