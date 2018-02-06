//
// Created by jim on 23.01.18.
//

#include "constants.h"

DynamicArray<Decimal, 2>
quadratic(
        Decimal const a,
        Decimal const b,
        Decimal const c
)
{
    Decimal const d = sq(b) - 4 * a * c;

    if (0 > d)
    {
        // No solutions:
        return {};
    }
    else if (0 == d)
    {
        // One solution, discriminant does not play any role as it's 0 anyway:
        return {-b / (2 * a)};
    }
    else
    {
        // Two solutions:
        Decimal const x1 = (-b + std::sqrt(d)) / (2 * a);
        Decimal const x2 = (-b - std::sqrt(d)) / (2 * a);
        return {std::min(x1, x2), std::max(x1, x2)};
    }
};

std::ostream &
operator<<(
        std::ostream &os,
        complex const &c
)
{
    os << c.real() << '+' << c.imag() << "ⅈ";
    return os;
}

std::ostream &
operator<<(
        std::ostream &os,
        vec const &v
)
{
    os << '(' << v.x << '|' << v.y << ')';
    return os;
}

std::ostream &
operator<<(
        std::ostream &os,
        mat const &m
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
