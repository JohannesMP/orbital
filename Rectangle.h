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
            const vec &upperRight
    );

    vec
    lowerLeft() const;

    vec
    upperLeft() const;

    vec
    lowerRight() const;

    vec
    upperRight() const;

private:

    vec mLowerLeft;
    double mW;
    double mH;

};


