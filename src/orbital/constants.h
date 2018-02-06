//
// Created by jim on 23.01.18.
//

#pragma once

#include <complex>
#include <functional>
#include <iostream>
#include <ostream>
#include <sstream>

#include <boost/math/constants/constants.hpp>

#include <glm/glm.hpp>
#include <glm/detail/type_vec.hpp>
#include <chrono>

#include "fmt/printf.h"

#include "DynamicArray.h"

/**
 * \file constants.h Provides general constants and math functions.
 *
 * ## Unicode characters:
 *
 * [Math related](http://xahlee.info/comp/unicode_math_operators.html):
 *
 * Charset         | Symbols
 * ----------------|---------------
 * Greek alphabet  | α β γ δ ε ζ η θ ι κ λ μ ν ξ ο π ρ ς τ υ φ χ ψ ω
 * Super-script    | ⁰ ¹ ² ³ ⁴ ⁵ ⁶ ⁷ ⁸ ⁹ ⁺ ⁻ ⁼ ⁽ ⁾ ⁿ ⁱ
 * Sub-script      | ₀ ₁ ₂ ₃ ₄ ₅ ₆ ₇ ₈ ₉ ₊ ₋ ₌ ₍ ₎ ₐ ₑ ₕ ᵢ ⱼ ₖ ₗ ₘ ₙ ₒ ₚ ᵣ ₛ ₜ ᵤ ᵥ ₓ ₔ
 * Sets            | ℕ ℤ ℚ ℝ ℂ ∈ ∉ ∪ ∩
 * Numbers         | ⅈ ℯ ∞
 * Comparators     | < > ≦ ≧
 * Integral        | ∫
 * Operators       | ⋅ ± ⨯ ⊙ √ ∛ ∜
 *
 * [Planets](https://en.wikipedia.org/wiki/List_of_gravitationally_rounded_objects_of_the_Solar_System):
 *
 * Celestial | Symbol
 * ----------|-------
 * Sun       | ☉
 * Mercury   | ☿
 * Venus     | ♀
 * Earth     | ⊕
 * Mars      | ♂
 * Jupiter   | ♃
 * Saturn    | ♄
 * Uranus    | ⛢
 * Neptune   | ♆
 * Pluto     | ♇
 * Ceres     | ⚳
 */

/**
 * Alias for floating point type.
 */
using Decimal = double;

/**
 * Alias for vector used in simulation.
 */
using vec = glm::tvec2<Decimal>;

/**
 * Alias for vector used for affine matrix transformation.
 */
using vec3 = glm::tvec3<Decimal>;

/**
 * Alias for matrices.
 */
using mat = glm::tmat3x3<Decimal>;

/**
 * Alias for complex numbers.
 */
using complex = std::complex<Decimal>;

// Import STL chrono literals:
using namespace std::chrono_literals;

/**
 * Literal suffix to properly use the Decimal type-alias in literals.
 */
constexpr Decimal
operator "" _df(
        long double literal
)
{
    return static_cast<Decimal>(literal);
}

/**
 * Literal suffix to properly use the Decimal type-alias in literals.
 */
constexpr Decimal
operator "" _df(
        unsigned long long literal
)
{
    return static_cast<Decimal>(literal);
}

/**
 * Identity matrix.
 */
inline mat
identityMatrix()
{
    return mat{1};
}

/**
 * Gravitational constant: \f$ [G] = \frac{kg \cdot m^3}{s^2} \f$
 */
constexpr Decimal
G()
{
    return 6.67408e-11_df;
}

/**
 * Factor to convert astronomic units to meters.
 */
constexpr Decimal
au(
        Decimal const meters = 1
)
{
    return meters * 1.49597870700e11_df;
}

/**
 * Literal suffix to multiply a number by π.
 */
constexpr Decimal
operator "" _pi(
        long double literal
)
{
    return static_cast<Decimal>(literal) * boost::math::constants::pi<Decimal>();
}

/**
 * Literal suffix to multiply a number by π.
 */
constexpr Decimal
operator "" _pi(
        unsigned long long literal
)
{
    return static_cast<Decimal>(literal) * boost::math::constants::pi<Decimal>();
}

/**
 * Smallest value, to use for 0 in cases 0 is forbidden
 */
constexpr Decimal
ZERO()
{
    return std::numeric_limits<Decimal>::epsilon();
}

/**
 * Square a number: \f$ x^2 \f$
 * @param x Number to square.
 * @return Result.
 */
constexpr Decimal
sq(
        Decimal x
)
{
    return x * x;
}

/**
 * Calculate vector length: \f$ \left| v \right| \f$
 * @param v Vector.
 * @return Length.
 */
constexpr Decimal
length(
        vec const &v
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
constexpr Decimal
distance(
        vec const &v0,
        vec const &v1
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
constexpr Decimal
angle(
        vec const &v
)
{
    return std::atan2(v.y, v.x);
}

/**
 * Integrate a function over a given range: \f$ \int_{low}^{high} f(x) dx \f$
 * @param f Function to integrate on.
 * @param low Lower integration bound.
 * @param high Upper integration bound.
 * @param resolution Resolution per x stepping, i.e. number of function invocations per x.
 * @return Area enclosed by graph and x-axis.
 */
template<class TFun>
Decimal
integral(
        TFun &&f,
        Decimal low,
        Decimal high,
        Decimal const resolution
)
{
    bool reverse = false;
    if (low > high)
    {
        std::swap(low, high);
        reverse = true;
    }

    Decimal const step = 1 / resolution;
    auto const steps = static_cast<int>((high - low) / step);
    Decimal sum = 0.0;                    // Area size accumulation
    Decimal x = low;                      // x starts at the lower bound

    for (int i = 0; i < steps; i++)
    {
        sum += std::forward<TFun>(f)(x + step * 0.5) * step;
        x += step;
    }

    return !reverse ? sum : -sum;
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
DynamicArray<Decimal, 2>
quadratic(
        Decimal const a,
        Decimal const b,
        Decimal const c
);

/**
 * Serialize a complex number: [real]+[imag]ⅈ
 */
std::ostream &
operator<<(
        std::ostream &os,
        const complex &c
);

/**
 * Serialize a vector.
 */
std::ostream &
operator<<(
        std::ostream &os,
        vec const &v
);

/**
 * Serialize a matrix.
 */
std::ostream &
operator<<(
        std::ostream &os,
        mat const &m
);
