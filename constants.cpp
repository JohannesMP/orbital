//
// Created by jim on 23.01.18.
//

#include "constants.h"

const double G = 6.6738e-11;
const double AU = 1.496e11;
const double PI = 3.141592653589793;
const double ZERO = std::numeric_limits<double>::epsilon();
const double S_PER_MIN = 60;
const double S_PER_HOUR = S_PER_MIN * 60;
const double S_PER_DAY = S_PER_HOUR * 24;
const double S_PER_MONTH = S_PER_DAY * 30;
const double S_PER_YEAR = S_PER_DAY * 365.256;

std::ostream &
operator<<(
        std::ostream &os,
        const complex &c
)
{
    os << c.real() << '+' << c.imag() << 'i';
    return os;
}

std::ostream &
operator<<(
        std::ostream &os,
        const vec &v
)
{
    os << '(' << v.x << '|' << v.y << ')';
    return os;
}

double
length(
        const vec &v
)
{
    return sqrt(v.x * v.x + v.y * v.y);
}
