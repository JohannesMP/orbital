//
// Created by jim on 23.01.18.
//

#include "constants.h"
#include <glm/gtc/type_ptr.hpp>

const double G = 6.6738e-11;
const double AU = 1.496e11;
const double PI = 3.141592653589793;
const double ZERO = std::numeric_limits<double>::epsilon();
const double S_PER_MIN = 60;
const double S_PER_HOUR = S_PER_MIN * 60;
const double S_PER_DAY = S_PER_HOUR * 24;
const double S_PER_MONTH = S_PER_DAY * 30;
const double S_PER_YEAR = S_PER_DAY * 365.256;

double sq(
        double v
)
{
    return v * v;
}

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

std::ostream &
operator<<(
        std::ostream &os,
        const glm::mat3 &m
)
{
    for(int col = 0; col < 3; col++)
    {
        for(int row = 0; row < 2; row++)
        {
            os << m[col][row]  << " , ";
        }
        os << m[col][2] << std::endl;
    }
    return os;
}

double
length(
        const vec &v
)
{
    return sqrt(v.x * v.x + v.y * v.y);
}

double
integral(
        std::function<double(double)> &&f,
        double low,
        double high,
        double resolution
)
{
    double step = 1 / resolution;
    auto steps = static_cast<int>((high - low) / step);
    double sum = 0.0;                    // Area size accumulation
    double x = low;                      // x starts at the lower bound

    for(int i = 0; i < steps; i++)
    {
        sum += f(x + step * 0.5) * step;
        x += step;
    }

    return sum;
}
