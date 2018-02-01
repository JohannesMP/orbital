//
// Created by jim on 31.01.18.
//

#pragma once

#include "constants.h"

class LinearFunction
{

public:

    LinearFunction(
            Decimal m,
            Decimal t
    );

    LinearFunction(
            const vec &p,
            const vec &d
    );

    Decimal
    m() const;

    Decimal
    t() const;

    Decimal
    operator()(
            Decimal x
    ) const;

private:

    Decimal mM;   ///< Gradient
    Decimal mT;   ///< Intercept

};
