//
// Created by jim on 23.01.18.
//

#pragma once

#include <complex>
#include <functional>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string_view>
#include <memory>
#include <chrono>
#include <numeric>
#include <array>
#include <ostream>
#include <vector>

#include <boost/math/constants/constants.hpp>

#include <glm/glm.hpp>
#include <glm/detail/type_vec.hpp>

#include "fmt/printf.h"

#include "DynamicArray.h"

/**
 * \file common.h Provides general constants and math functions.
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
using namespace std::chrono_literals; // NOLINT

using namespace std::literals::string_view_literals; // NOLINT;

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
 * Smallest value, to use for 0 in cases 0 is forbidden
 */
constexpr Decimal
zero()
{
    return std::numeric_limits<Decimal>::epsilon();
}

/**
 * Serialize a complex number: [real]+[imag]ⅈ
 */
std::ostream &
operator<<(
        std::ostream &os,
        const complex &c
);

namespace glm {

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

} // namespace glm

namespace std { // NOLINT

/**
 * Serialize a pair:
 */
template<class T, class U>
std::ostream &
operator<<(
        std::ostream &os,
        std::pair<T, U> const &p
)
{
    os << "[ " << p.first << ", " << p.second << " ]";
    return os;
}

}
