//
// Created by jim on 26.01.18.
//

#include <array>
#include "constants.h"
#include "Rectangle.h"

#pragma once

/**
 * Immutable ellipse, provides math.
 */
class Ellipse
{

public:

    Ellipse() = default;

    /**
     * Construct an ellipse.
     * @param a Major semi-axis.
     * @param e Numeric eccentricity.
     */
    Ellipse(
            double a,
            double e
    );

    /**
     * @return Major semi-axis.
     */
    double
    a() const;

    /**
     * @return Minor semi-axis.
     */
    double
    b() const;

    /**
     * @return Numeric eccentricity.
     */
    double
    e() const;

    /**
     * Calculate position of a point on the ellipse using the parametric form.
     * @param t Parameter [0,2π]
     * @return Major semi-axis.
     */
    vec
    point(
            double t
    ) const;

    vec
    pointAngle(
            double radians
    ) const;

    /**
     * Check whether a point is contained by the ellipse covered area.
     * @param p Point to check.
     * @return True if inside.
     */
    bool
    contains(
            const vec &p
    ) const;

    /**
     * Checks whether a rectangle is completely inside the ellipse.
     * @param p Lower-left point of rectangle.
     * @param w Rectangle width, can be negative.
     * @param h Rectangle height, can be negative.
     * @return True if completely inside ellipse.
     */
    bool
    contains(
            const Rectangle &rect
    ) const;

    std::pair<double, double>
    clip(
            const Rectangle &rect
    ) const;

    /**
     * Calculate the length of an arc slice within `ts` and `te`.
     * @param ts Start parameter of arc.
     * @param te End parameter of arc.
     * @param resolution The higher the resolution, the more accurate the result.
     * @return Arc length.
     */
    double
    arcLength(
            double ts,
            double te,
            double resolution
    )  const;

    /**
     * @return Two foci as x-values.
     */
    std::array<double, 2>
    foci() const;

    /**
     * @return Two foci as vectors, whose y-coordinate is 0.
     */
    std::array<vec, 2>
    fociPoints() const;

private:

    double mA;
    double mB;
    double mE;
    double mFoci;

    double tAtX(
            double x
    ) const;

};


