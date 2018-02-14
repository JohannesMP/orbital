//
// Created by jim on 14.02.18.
//

#include "common.h"

#include <orbital/math/Radian.h>

bool
operator==(
        Radian const &r,
        Approx const &approx
)
{
    return r.getRaw() == approx;
}

Approx
approx(
        Radian const &r
)
{
    return Approx(r.getRaw());
}
