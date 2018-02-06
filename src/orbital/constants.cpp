//
// Created by jim on 23.01.18.
//

#include "constants.h"
#include <algorithm>

const mat IDENTITY_MATRIX{1};

DynamicArray<Decimal, 2>
quadratic(
        Decimal a,
        Decimal b,
        Decimal c
)
{
    Decimal const d = sq(b) - 4 * a * c;

    if(0 > d)
    {
        // No solutions:
        return {};
    }
    else if(0 == d)
    {
        // One solution, discriminant does not play any role as it's 0 anyway:
        return {-b / (2 * a)};
    }
    else {
        // Two solutions:
        Decimal const x1 = (-b + std::sqrt(d)) / (2 * a);
        Decimal const x2 = (-b - std::sqrt(d)) / (2 * a);
        return {
                std::min(x1, x2),
                std::max(x1, x2)
        };
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
        std::swap(low, high);
        reverse = true;
    }

    Decimal const step = 1 / resolution;
    auto const steps = static_cast<int>((high - low) / step);
    Decimal sum = 0.0;                    // Area size accumulation
    Decimal x = low;                      // x starts at the lower bound

    for (int i = 0; i < steps; i++)
    {
        sum += f(x + step * 0.5) * step;
        x += step;
    }

    return !reverse ? sum : -sum;
}