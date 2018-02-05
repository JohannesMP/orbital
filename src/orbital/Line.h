//
// Created by jim on 05.02.18.
//

#pragma once

#include <ostream>
#include "constants.h"

class Line
{

public:

    Line(
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
    );

    bool
    containsByBounds(
            vec v
    );

    friend std::ostream &
    operator<<(
            std::ostream &os,
            const Line &line
    );

private:

    vec mP;
    vec mD;

};
