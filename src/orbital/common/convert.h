//
// Created by jim on 14.02.18.
//

#pragma once

#include "common.h"

/**
 * Used to convert a 2D vector into another named type 2D vector.
 * This function is intended to be used temporarily till complete project uses named types correctly and does not
 * need this converted anymore.
 * @tparam TTarget Target named type to convert to.
 * @param source Source vector to convert.
 * @return Vector with equal data, but with type equal to `TTarget`.
 */
template<class TTarget>
constexpr TTarget
convert(
        vec const &source
)
{
    return TTarget{source.x, source.y};
};
