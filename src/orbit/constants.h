//
// Created by jim on 23.01.18.
//

#pragma once

#include <glm/glm.hpp>
#include <glm/detail/type_vec.hpp>
#include <complex>
#include <functional>
#include <sstream>

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
 * Roots           | √ ∛ ∜
 * Sets            | ℕ ℤ ℚ ℝ ℂ ∈ ∉ ∪ ∩
 * Numbers         | ⅈ ℯ ∞
 * Comparators     | < > ≦ ≧
 * Integral        | ∫
 * Operators       | ⋅ ± ⨯ ⊙
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

using Decimal = double;

using vec = glm::tvec2<Decimal>;

using vec3 = glm::tvec3<Decimal>;

using mat = glm::tmat3x3<Decimal>;

using complex = std::complex<Decimal>;

/**
 * Identity matrix.
 */
extern const mat IDENTITY_MATRIX;

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
 * Gravitational constant: \f$ [G] = \frac{kg \cdot m^3}{s^2} \f$
 */
constexpr Decimal G = 6.67408e-11_df;

/**
 * Factor to convert astronomic units to meters.
 */
constexpr Decimal AU = 1.49597870700e11_df;

/**
 * Pi
 */
constexpr Decimal PI = 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899_df;

/**
 * Literal suffix to multiply a number by π.
 */
constexpr Decimal
operator "" _pi(
        long double literal
)
{
    return static_cast<Decimal>(literal) * PI;
}

/**
 * Literal suffix to multiply a number by π.
 */
constexpr Decimal
operator "" _pi(
        unsigned long long literal
)
{
    return static_cast<Decimal>(literal) * PI;
}

/**
 * Smallest value, to use for 0 in cases 0 is forbidden
 */
constexpr Decimal ZERO = std::numeric_limits<Decimal>::epsilon();

/**
 * Seconds per minute.
 */
constexpr Decimal S_PER_MIN = 60_df;

/**
 * Seconds per hour.
 */
constexpr Decimal S_PER_HOUR = S_PER_MIN * 60_df;

/**
 * Seconds per 24-hours day.
 */
constexpr Decimal S_PER_DAY = S_PER_HOUR * 24_df;

/**
 * Seconds per month (using average day count of 30.436875).
 */
constexpr Decimal S_PER_MONTH = S_PER_DAY * 30.436875_df;

/**
 * Seconds per year (using average day count of 365.24219052).
 */
constexpr Decimal S_PER_YEAR = S_PER_DAY * 365.24219052_df;

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
        const vec &v
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
        const vec &v0,
        const vec &v1
)
{
    return length(vec{v1.x - v0.x, v1.y - v0.y});
}

/**
 * Calculate the angle between the vector and the x axis: \f$ arctan2(v_y, v_x) \f$
 */
constexpr Decimal
angle(
        const vec &v
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
Decimal
integral(
        std::function<Decimal(Decimal)> &&f,
        Decimal low,
        Decimal high,
        Decimal resolution
);

/**
 * Serialize a complex number: [real]+[imag]i
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
        const vec &v
);

/**
 * Serialize a matrix.
 */
std::ostream &
operator<<(
        std::ostream &os,
        const mat &m
);

template<class T>
std::string
toString(
        const T &t
)
{
    std::stringstream ss;
    ss << t;
    return ss.str();
}
