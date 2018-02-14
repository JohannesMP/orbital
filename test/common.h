//
// Created by jim on 14.02.18.
//

#pragma once

#include "catch/catch.hpp"
#include <orbital/math/Radian.h>

template<class T>
bool
operator==(
        Radian<T> const &r,
        Approx const &approx
)
{
    return r.getRaw() == approx;
}

template<class T>
Approx
approx(
        Radian<T> const &r
)
{
    return Approx(r.getRaw());
}
