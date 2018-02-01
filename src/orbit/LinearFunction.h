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

    /**
     * Construct a linear function from a line, which is denoted by a start point and direction vector:
     * \f$ \vec{x} = \vec{p} + \lambda \vec{d} \f$
     *
     * @attention Do not construct linear functions from lines, which are perpendicular on the x-axis, so
     *            that:
     *            \f$
     *                \vec{d} \neq
     *                \lambda
     *                \begin{pmatrix}
     *                    0 \\ 1
     *                \end{pmatrix}
     *            \f$
     * @param p Start point of line.
     * @param d Direction vector of line.
     */
    LinearFunction(
            const vec &p,
            const vec &d
    );

    /**
     * Maps x value to y value: \f$ f(x) = mx + t \f$
     * @param x Value to map.
     * @return Mapped y value.
     */
    Decimal
    operator()(
            Decimal x
    ) const;

    /**
     * @return Gradient of function.
     */
    Decimal
    m() const;

    /**
     * @return Intercept of function: \f$ f(0) \f$
     */
    Decimal
    t() const;

private:

    Decimal mM;   ///< Gradient
    Decimal mT;   ///< Intercept

};
