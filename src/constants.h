//
// Created by jim on 23.01.18.
//

#pragma once

#include <glm/glm.hpp>
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
 * Planets:         ☉ ☿ ♀ ⊕ ♂ ♃ ♄ ⛢ ♆ ♇
 */

using vec = glm::dvec2;

using complex = std::complex<double>;

/**
 * Gravitational constant: [m³ kg s⁻²]
 */
constexpr double G = 6.6738e-11;

/**
 * Factor to convert astronomic units to meters.
 */
constexpr double AU = 1.496e11;

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
extern const double ZERO;

constexpr double S_PER_MIN = 60;
constexpr double S_PER_HOUR = S_PER_MIN * 60;
constexpr double S_PER_DAY = S_PER_HOUR * 24;
constexpr double S_PER_MONTH = S_PER_DAY * 30;
constexpr double S_PER_YEAR = S_PER_DAY * 365.256;

constexpr double
sq(
        double v
)
{
    return v * v;
}

constexpr double
length(
        const vec &v
)
{
    return sqrt(v.x * v.x + v.y * v.y);
}

constexpr double
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
double
integral(
        std::function<double(double)> &&f,
        double low,
        double high,
        double resolution
);
