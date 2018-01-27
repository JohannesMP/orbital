//
// Created by jim on 23.01.18.
//

#include "constants.h"
#include <glm/gtc/type_ptr.hpp>

const double ZERO = std::numeric_limits<double>::epsilon();

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
integral(
        std::function<double(double)> &&f,
        double low,
        double high,
        double resolution
)
{
    bool reverse = false;
    if(low > high)
    {
        double tmp = low;
        low = high;
        high = tmp;
        reverse = true;
    }

    double step = 1 / resolution;
    auto steps = static_cast<int>((high - low) / step);
    double sum = 0.0;                    // Area size accumulation
    double x = low;                      // x starts at the lower bound

    for(int i = 0; i < steps; i++)
    {
        sum += f(x + step * 0.5) * step;
        x += step;
    }

    return !reverse ? sum : -sum;
}
