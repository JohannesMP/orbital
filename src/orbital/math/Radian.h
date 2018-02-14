//
// Created by jim on 13.02.18.
//

#pragma once

#include <orbital/common/common.h>

template<class T>
class Radian
{

public:

    constexpr Radian()
            : Radian{0}
    {
    }

    constexpr explicit Radian(
            T const &radians
    )
            : mRadians{radians}
    {
    }

    /**
     * Serialize a radian value.
     * Prints this value divided by π.
     */
    std::ostream &
    operator<<(
            std::ostream &os
    )
    {
        os << (mRadians / boost::math::constants::pi<Decimal>()) << "π";
        return os;
    }

    constexpr bool operator<(
            Radian<T> const &rhs
    ) const
    {
        return mRadians < rhs.mRadians;
    }

    constexpr bool
    operator>(
            Radian<T> const &rhs
    ) const
    {
        return rhs > *this;
    }

    constexpr bool
    operator==(
            Radian<T> const &rhs
    ) const
    {
        return !(*this < rhs) && !(rhs < *this);
    }

    constexpr bool
    operator<=(
            Radian<T> const &rhs
    ) const
    {
        return (*this < rhs) || (*this == rhs);
    }

    constexpr bool
    operator>=(
            Radian const &rhs
    ) const
    {
        return (*this > rhs) || (*this == rhs);
    }

    constexpr Radian<T>
    operator-() const
    {
        return Radian<T>{-mRadians};
    }

    constexpr Radian<T>
    operator+(
            Radian<T> const &rhs
    ) const
    {
        return Radian<T>{mRadians + rhs.mRadians};
    }

    constexpr Radian<T>
    operator-(
            Radian<T> const &rhs
    ) const
    {
        return Radian<T>{mRadians - rhs.mRadians};
    }

    constexpr Radian
    operator*(
            T const &rhs
    ) const
    {
        return Radian{mRadians * rhs};
    }

    constexpr Radian
    operator/(
            T const &rhs
    ) const
    {
        return Radian{mRadians / rhs};
    }

    T
    sin() const
    {
        return std::sin(mRadians);
    }

    T
    cos() const
    {
        return std::cos(mRadians);
    }

    T
    tan() const
    {
        return std::tan(mRadians);
    }

    static Radian
    arcsin(
            T const x)
    {
        return Radian{std::asin(x)};
    }

    static Radian
    arccos(
            T const x)
    {
        return Radian{std::acos(x)};
    }

    static Radian
    arctan(
            T const x)
    {
        return Radian{std::atan(x)};
    }

    static Radian
    arctan2(
            T const y,
            T const x
    )
    {
        return Radian{std::atan2(y, x)};
    }

    constexpr T
    getRaw() const
    {
        return mRadians;
    }

private:

    /**
     * Actual value.
     */
    T mRadians;

};

/**
 * Literal suffix to multiply a number by π.
 */
constexpr Radian<Decimal>
operator "" _pi(
        long double literal
)
{
    return Radian<Decimal>{static_cast<Decimal>(literal)} * boost::math::constants::pi<Decimal>();
}

/**
 * Literal suffix to multiply a number by π.
 */
constexpr Radian<Decimal>
operator "" _pi(
        unsigned long long literal // NOLINT
)
{
    return Radian<Decimal>{static_cast<Decimal>(literal)} * boost::math::constants::pi<Decimal>();
}
