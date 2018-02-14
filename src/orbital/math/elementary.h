//
// Created by jim on 13.02.18.
//

#pragma once

#include "Radian.h"
#include <orbital/common/common.h>
#include <orbital/common/range.h>

/**
 * Compute the average over a given set of values.
 * @param value First value.
 * @param rest Rest of values.
 * @return Average.
 */
template<class T, class... Ts>
constexpr T
average(
        T const value,
        Ts const ...rest
)
{
    (void) value;
    std::array<T, sizeof...(rest) + 1> v{{value, rest...}};
    return std::accumulate(v.begin(), v.end(), T{0}) / v.size();
}

/**
 * Square a number: \f$ x^2 \f$
 * @param x Number to square.
 * @return Result.
 */
constexpr Decimal
sq(
        Decimal const x
)
{
    return x * x;
}

/**
 * Calculate vector length: \f$ \left| v \right| \f$
 * @param v Vector.
 * @return Length.
 */
inline Decimal
length(
        vec const v
)
{
    return std::sqrt(v.x * v.x + v.y * v.y);
}

/**
 * Calculate vector distance: \f$ \left| v_1 - v_0 \right| \f$
 * @param v0 First vector.
 * @param v1 Second vector.
 * @return Distance.
 */
inline Decimal
distance(
        vec const v0,
        vec const v1
)
{
    return length(vec{v1.x - v0.x, v1.y - v0.y});
}

/**
 * Computes a counterclockwise-perpendicular 2D vector with the same length.
 */
inline vec
perpendicular(
        vec const v
)
{
    return {-v.y, v.x};
}

/**
 * Calculate the angle between the vector and the x axis: \f$ arctan2(v_y, v_x) \f$
 */
inline Radian
angle(
        vec const v
)
{
    return Radian::arctan2(v.y, v.x);
}

/**
 * Integrate a function over a given range: \f$ \int_{low}^{high} f(x) dx \f$
 * @attention If the resolution is greater than 1, it is required to be able to hold fractional values. As integer
 * types would truncate to 0, giving integer types in such a case will lead to 0 division.
 * @param f Function to integrate on.
 * @param args Arguments to pass to f, see std::apply().
 * @param low Lower integration bound.
 * @param high Upper integration bound.
 * @param resolution Resolution per x stepping, i.e. number of function invocations per x.
 * @return Area enclosed by graph and x-axis.
 */
template<class TFun, class... TArgs, class T, class Tx>
constexpr Tx
integral(
        Tx const low,
        Tx const high,
        T const resolution,
        TFun &&f,
        TArgs &&...args
)
{
    // Step points to negative x if high is smaller than low
    T const step = (low < high ? T{1} : T{-1}) / resolution;
    auto const steps = (high - low) / step;

    return reduce_range(Tx{}, steps, Tx{}, [&](
            Tx const sum,
            auto const i
    ) {
        return sum + Tx{std::apply(std::forward<TFun>(f),
                std::tuple{std::forward<TFun>(args)..., low + (i + Tx(0.5)) * step})} * step;
    });
}

/**
 * Computes the quadratic formula: \f$ 0 = ax^2 + bx + c \f$
 *
 * Midnight formula: \f$ x_{1,2} = \frac{ -b \pm \sqrt{b^2 - 4ac} }{2a} \f$
 *
 * @param a A
 * @param b B
 * @param c C
 * @return Count of solutions and an array of solutions in ascending order.
 */
template<class T>
DynamicArray<T, 2>
quadratic(
        T const a,
        T const b,
        T const c
)
{
    T const d = sq(b) - 4 * a * c;

    if (0 > d)
    {
        // No solutions:
        return {};
    }
    if (0 == d)
    {
        // One solution, discriminant does not play any role as it's 0 anyway:
        return {-b / (2 * a)};
    }

    // Two solutions:
    T const x1 = (-b + std::sqrt(d)) / (2 * a);
    T const x2 = (-b - std::sqrt(d)) / (2 * a);
    return {std::min(x1, x2), std::max(x1, x2)};
};
