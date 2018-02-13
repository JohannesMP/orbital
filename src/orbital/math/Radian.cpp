//
// Created by jim on 13.02.18.
//

#include "Radian.h"

std::ostream &
operator<<(
        std::ostream &os,
        Radian const &radian
)
{
    os << (radian.mRadians / (1_pi).mRadians) << "π";
    return os;
}

std::istream &
operator>>(
        std::istream &os,
        Radian &radian
)
{
    os >> radian.mRadians;
    os.ignore("π"sv.length());
    return os;
}

Decimal
Radian::sin() const
{
    return std::sin(mRadians);
}

Decimal
Radian::cos() const
{
    return std::cos(mRadians);
}

Decimal
Radian::tan() const
{
    return std::tan(mRadians);
}

Radian
Radian::arcsin(Decimal const x)
{
    return Radian{std::asin(x)};
}

Radian
Radian::arccos(Decimal const x)
{
    return Radian{std::acos(x)};
}

Radian
Radian::arctan(Decimal const x)
{
    return Radian{std::atan(x)};
}

Radian
Radian::arctan2(
        Decimal const y,
        Decimal const x
)
{
    return Radian{std::atan2(y, x)};
}
