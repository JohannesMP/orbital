//
// Created by jim on 23.01.18.
//

#pragma once

#include <glm/glm.hpp>
#include <complex>
#include <functional>

using vec = glm::dvec2;

using complex = std::complex<double>;

/**
 * Gravitational constant: [m^3 kg / s^2]
 */
constexpr double G = 6.6738e-11;

/**
 * Factor to convert astronomic units to meters.
 */
constexpr double AU = 1.496e11;

/**
 * Pi
 */
constexpr double PI = 3.141592653589793;

/**
 * Literal suffix to multiply a number by PI.
 */
constexpr long double
operator ""_pi(
        long double v
)
{
    return PI * v;
}

/**
 * Literal suffix to multiply a number by PI.
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
