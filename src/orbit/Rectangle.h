//
// Created by jim on 26.01.18.
//

#pragma once

#include "constants.h"

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

private:

    vec mBottomLeft;
    Decimal mW;
    Decimal mH;

};


