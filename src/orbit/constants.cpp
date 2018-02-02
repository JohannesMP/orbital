//
// Created by jim on 23.01.18.
//

#include "constants.h"
#include <glm/gtc/type_ptr.hpp>

const mat IDENTITY_MATRIX{1};

std::pair<unsigned, std::array<Decimal, 2>>
quadratic(
        Decimal a,
        Decimal b,
        Decimal c
)
{
    Decimal d = sq(b) - 4 * a * c;

    if(0 > d)
    {
        // No solutions:
        return {0, {}};
    }
    else if(0 == d)
    {
        // One solution, discriminant does not play any role as it's 0 anyway:
        return {1, {
                -b / (2 * a)
        }};
    }
    else {
        // Two solutions:
        Decimal x1 = (-b + std::sqrt(d)) / (2 * a);
        Decimal x2 = (-b - std::sqrt(d)) / (2 * a);
        return {2, {
                std::min(x1, x2),
                std::max(x1, x2)
        }};
    }
};

std::ostream &
operator<<(
        std::ostream &os,
        const complex &c
)
{
    os << c.real() << '+' << c.imag() << "ⅈ";
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
        const mat &m
)
{
    for (int col = 0; col < 3; col++)
    {
        for (int row = 0; row < 2; row++)
        {
            os << m[col][row] << " , ";
        }
        os << m[col][2] << std::endl;
    }
    return os;
}

Decimal
integral(
        std::function<Decimal(Decimal)> &&f,
        Decimal low,
        Decimal high,
        Decimal resolution
)
{
    bool reverse = false;
    if (low > high)
    {
        Decimal tmp = low;
        low = high;
        high = tmp;
        reverse = true;
    }

    Decimal step = 1 / resolution;
    auto steps = static_cast<int>((high - low) / step);
    Decimal sum = 0.0;                    // Area size accumulation
    Decimal x = low;                      // x starts at the lower bound

    for (int i = 0; i < steps; i++)
    {
        sum += f(x + step * 0.5) * step;
        x += step;
    }

    return !reverse ? sum : -sum;
}
