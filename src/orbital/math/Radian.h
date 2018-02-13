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

    constexpr Radian
    operator*(
            Radian const &rhs
    ) const
    {
        return Radian{mRadians * rhs.mRadians};
    }

    constexpr Radian
    operator/(
            Radian const &rhs
    ) const
    {
        return Radian{mRadians / rhs.mRadians};
    }

    Decimal
    sin() const;

    Decimal
    cos() const;

    Decimal
    tan() const;

    static Radian
    arcsin(Decimal const x);

    static Radian
    arccos(Decimal const x);

    static Radian
    arctan(Decimal const x);

    // TODO: [[deprecated]]
    Decimal
    getRaw()
    {
        return mRadians;
    }

    static Radian
    arctan2(
            Decimal const y,
            Decimal const x
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
    return Radian{static_cast<Decimal>(literal)} * Radian{boost::math::constants::pi<Decimal>()};
}

/**
 * Literal suffix to multiply a number by π.
 */
constexpr Radian
operator "" _pi(
        unsigned long long literal
)
{
    return Radian{static_cast<Decimal>(literal)} * Radian{boost::math::constants::pi<Decimal>()};
}
