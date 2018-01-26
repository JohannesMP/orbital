//
// Created by jim on 26.01.18.
//

#pragma once

#include "constants.h"

class Rectangle
{

public:

    Rectangle(
            const vec &lowerLeft,
            double w,
            double h
    );

    Rectangle(
            const vec &lowerLeft,
            const vec &topRight
    );

    double
    top() const;

    double
    bottom() const;

    double
    left() const;

    double
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
    double mW;
    double mH;

};


