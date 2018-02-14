//
// Created by jim on 14.02.18.
//

#pragma once

#include "catch/catch.hpp"

class Radian;

bool
operator==(
        Radian const &r,
        Approx const &approx
);

Approx
approx(
        Radian const &r
);
