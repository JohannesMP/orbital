//
// Created by jim on 13.02.18.
//

#pragma once

#include <orbital/common/common.h>
#include <ostream>

class Radian
{

public:

    constexpr Radian()
            : Radian{0}
    {
    }

    constexpr explicit Radian(
            Decimal const &radians
    )
            : mRadians{radians}
    {
    }

    /**
     * Serialize a radian value.
     */
    friend std::ostream &
    operator<<(
            std::ostream &os,
            Radian const &radian
    );

    friend std::istream &
    operator>>(
            std::istream &os,
            Radian &radian
    );

    constexpr bool operator<(
            Radian const &rhs
    ) const
    {
        return mRadians < rhs.mRadians;
    }

    constexpr bool
    operator>(
            Radian const &rhs
    ) const
    {
        return rhs > *this;
    }

    constexpr bool
    operator==(
            Radian const &rhs
    ) const
    {
        return !(*this < rhs) && !(rhs < *this);
    }

    constexpr bool
    operator<=(
            Radian const &rhs
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

    constexpr Radian
    operator-() const
    {
        return Radian{-mRadians};
    }

    constexpr Radian
    operator+(
            Radian const &rhs
    ) const
    {
        return Radian{mRadians + rhs.mRadians};
    }

    constexpr Radian
    operator-(
            Radian const &rhs
    ) const
    {
        return Radian{mRadians - rhs.mRadians};
    }

    template<class T>
    constexpr Radian
    operator*(
            T const &rhs
    ) const
    {
        return Radian{mRadians * rhs};
    }

    template<class T>
    constexpr Radian
    operator/(
            T const &rhs
    ) const
    {
        return Radian{mRadians / rhs};
    }

    Decimal
    sin() const;

    Decimal
    cos() const;

    Decimal
    tan() const;

    static Radian
    arcsin(Decimal x);

    static Radian
    arccos(Decimal x);

    static Radian
    arctan(Decimal x);

    constexpr Decimal
    getRaw() const
    {
        return mRadians;
    }

    static Radian
    arctan2(
            Decimal y,
            Decimal x
    );

private:

    /**
     * Actual value.
     */
    Decimal mRadians;

};

/**
 * Literal suffix to multiply a number by π.
 */
constexpr Radian
operator "" _pi(
        long double literal
)
{
    return Radian{static_cast<Decimal>(literal)} * boost::math::constants::pi<Decimal>();
}

/**
 * Literal suffix to multiply a number by π.
 */
constexpr Radian
operator "" _pi(
        unsigned long long literal // NOLINT
)
{
    return Radian{static_cast<Decimal>(literal)} * boost::math::constants::pi<Decimal>();
}
