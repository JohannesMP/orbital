//
// Created by jim on 23.01.18.
//

#include "common.h"

std::ostream &
operator<<(
        std::ostream &os,
        complex const &c
)
{
    os << c.real() << '+' << c.imag() << "ⅈ";
    return os;
}

namespace glm {

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

} // namespace glm
