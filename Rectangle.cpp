//
// Created by jim on 26.01.18.
//

#include "Rectangle.h"

Rectangle::Rectangle(
        const vec &lowerLeft,
        double w,
        double h
)
        : mLowerLeft{lowerLeft}
        , mW{w}
        , mH{h}
{
}

Rectangle::Rectangle(
        const vec &lowerLeft,
        const vec &upperRight
)
        : mLowerLeft{lowerLeft}
        , mW{upperRight.x - lowerLeft.x}
        , mH{upperRight.y - lowerLeft.y}
{
}

vec
Rectangle::lowerLeft() const
{
    return mLowerLeft;
}

vec
Rectangle::upperLeft() const
{
    return {
            mLowerLeft.x,
            mLowerLeft.y + mH
    };
}

vec
Rectangle::lowerRight() const
{
    return {
            mLowerLeft.x + mW,
            mLowerLeft.y
    };
}

vec
Rectangle::upperRight() const
{
    return {
            mLowerLeft.x + mW,
            mLowerLeft.y + mH
    };
}
