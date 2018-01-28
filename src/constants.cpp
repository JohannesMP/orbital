//
// Created by jim on 23.01.18.
//

#include "constants.h"
#include <glm/gtc/type_ptr.hpp>

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

long double
integral(
        std::function<long double(long double)> &&f,
        long double low,
        long double high,
        long double resolution
)
{
    bool reverse = false;
    if(low > high)
    {
        long double tmp = low;
        low = high;
        high = tmp;
        reverse = true;
    }

    long double step = 1 / resolution;
    auto steps = static_cast<int>((high - low) / step);
    long double sum = 0.0;                    // Area size accumulation
    long double x = low;                      // x starts at the lower bound

    for(int i = 0; i < steps; i++)
    {
        sum += f(x + step * 0.5) * step;
        x += step;
    }

    return !reverse ? sum : -sum;
}
