//
// Created by jim on 05.02.18.
//

#pragma once

#include <orbital/common/common.h>
#include <ostream>

class Line
{

public:

    explicit Line(
            vec p0,
            vec p1
    );

    static Line
    fromDirection(
            vec p,
            vec d
    );

    vec
    p() const;

    vec
    d() const;

    vec
    point(
            Decimal lambda
    ) const;

    bool
    containsByBounds(
            vec v
    ) const;

    inline std::ostream &
    operator<<(
            std::ostream &os
    )
    {
        os << mP << " + λ" << mD;
        return os;
    }

private:

    vec mP;
    vec mD;

};
