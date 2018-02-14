//
// Created by jim on 05.02.18.
//

#pragma once

#include "Rectangle.h"
#include <orbital/common/common.h>

template<class T>
class Line
{

public:

    Line(
            tvec<T> const p0,
            tvec<T> const p1
    )
            : mP{p0}
            , mD{p1 - p0}
    {
    }

    static Line
    fromDirection(
            tvec<T> const p,
            tvec<T> const d
    )
    {
        return Line{p, p + d};
    }

    constexpr vec
    p() const
    {
        return mP;
    }

    constexpr vec
    d() const
    {
        return mD;
    }

    tvec<T>
    point(
            T const lambda
    ) const
    {
        return mP + lambda * mD;
    }

    bool
    containsByBounds(
            tvec<T> const v
    ) const
    {
        Rectangle bounds{mP, mP + mD};
        return bounds.contains(v);
    }

    std::ostream &
    operator<<(
            std::ostream &os
    )
    {
        os << mP << " + λ" << mD;
        return os;
    }

private:

    tvec<T> const mP;
    tvec<T> const mD;

};
