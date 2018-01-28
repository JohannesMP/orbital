//
// Created by jim on 23.01.18.
//

#pragma once

#include <glm/glm.hpp>
#include <glm/detail/type_vec.hpp>
#include <complex>
#include <functional>

/*
 * http://xahlee.info/comp/unicode_math_operators.html
 *
 * Greek alphabet:  α β γ δ ε ζ η θ ι κ λ μ ν ξ ο π ρ ς τ υ φ χ ψ ω
 * Super-script:    ⁰ ¹ ² ³ ⁴ ⁵ ⁶ ⁷ ⁸ ⁹ ⁺ ⁻ ⁼ ⁽ ⁾ ⁿ ⁱ
 * Sub-script:      ₀ ₁ ₂ ₃ ₄ ₅ ₆ ₇ ₈ ₉ ₊ ₋ ₌ ₍ ₎ ₐ ₑ ₕ ᵢ ⱼ ₖ ₗ ₘ ₙ ₒ ₚ ᵣ ₛ ₜ ᵤ ᵥ ₓ ₔ
 * Roots:           √ ∛ ∜
 * Sets:            ℕ ℤ ℚ ℝ ℂ ∈ ∋ ∉ ∌ ∪ ∩
 * Imaginary:       ⅈ
 * Euler's number:  ℯ
 * Infinity:        ∞
 * Cross operator:  ⨯
 * Dot operator:    ⊙
 * Comparators:     < > ≦ ≧
 * Integral:        ∫
 *
 * https://en.wikipedia.org/wiki/List_of_gravitationally_rounded_objects_of_the_Solar_System
 *
 * Planets:         ☉ ☿ ♀ ⊕ ♂ ♃ ♄ ⛢ ♆ ♇
 */

using vec = glm::tvec2<long double>;

using complex = std::complex<long double>;

/**
 * Gravitational constant: [m³ kg s⁻²]
 */
constexpr long double G = 6.6738e-11;

/**
 * Factor to convert astronomic units to meters.
 */
constexpr long double AU = 1.496e11;

/**
 * Pi
 */
constexpr long double PI = 3.141592653589793;

/**
 * Literal suffix to multiply a number by π.
 */
constexpr long double
operator ""_pi(
        long double v
)
{
    return PI * v;
}

/**
 * Literal suffix to multiply a number by π.
 */
constexpr long double
operator ""_pi(
        unsigned long long v
)
{
    return PI * v;
}

/**
 * Smallest value, to use for 0 in cases 0 is forbidden
 */
constexpr long double ZERO = std::numeric_limits<double>::epsilon();

constexpr long double S_PER_MIN = 60;
constexpr long double S_PER_HOUR = S_PER_MIN * 60;
constexpr long double S_PER_DAY = S_PER_HOUR * 24;
constexpr long double S_PER_MONTH = S_PER_DAY * 30;
constexpr long double S_PER_YEAR = S_PER_DAY * 365.256;

constexpr long double
sq(
        long double v
)
{
    return v * v;
}

constexpr long double
length(
        const vec &v
)
{
    return std::sqrt(v.x * v.x + v.y * v.y);
}

constexpr long double
distance(
        const vec &v0,
        const vec &v1
)
{
    return length(vec{v1.x - v0.x, v1.y - v0.y});
}

/**
 * Serialize a complex number: [real]+[imag]i
 */
std::ostream &
operator<<(
        std::ostream &os,
        const complex &c
);

std::ostream &
operator<<(
        std::ostream &os,
        const vec &v
);

std::ostream &
operator<<(
        std::ostream &os,
        const glm::mat3 &m
);

/**
 * Integrate a function over a given range.
 * @param f Function to integrate on.
 * @param low Lower integration bound.
 * @param high Upper integration bound.
 * @param resolution Resolution per x stepping, i.e. number of function invocations per x.
 * @return Area of integral.
 */
long double
integral(
        std::function<long double(long double)> &&f,
        long double low,
        long double high,
        long double resolution
);
