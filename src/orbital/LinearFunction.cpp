//
// Created by jim on 31.01.18.
//

#include "LinearFunction.h"

LinearFunction::LinearFunction(
        Decimal m,
        Decimal t
)
    : mM{m}
    , mT{t}
{
}

LinearFunction::LinearFunction(
        const vec &p,
        const vec &d
)
    : mM{d.y / d.x}
    , mT{p.y - mM * p.x}
{
}

Decimal
LinearFunction::m() const
{
    return mM;
}

Decimal
LinearFunction::t() const
{
    return mT;
}

Decimal
LinearFunction::operator()(Decimal x) const
{
    return mM * x + mT;
}
