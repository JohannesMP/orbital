//
// Created by jim on 05.02.18.
//

#pragma once

#include "constants.h"
#include <ostream>

class Line
{

public:

    explicit Line(
            vec const p0,
            vec const p1
    );

    static Line
    fromDirection(
            vec const p,
            vec const d
    );

    vec
    p() const;

    vec
    d() const;

    vec
    point(
            Decimal const lambda
    ) const;

    bool
    containsByBounds(
            vec const v
    ) const;

    friend std::ostream &
    operator<<(
            std::ostream &os,
            Line const &line
    );

private:

    vec mP;
    vec mD;

};
