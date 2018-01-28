//
// Created by jim on 26.01.18.
//

#include <array>
#include <vector>
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
            long double a,
            long double e
    );

    /**
     * @return Major semi-axis.
     */
    long double
    a() const;

    /**
     * @return Minor semi-axis.
     */
    long double
    b() const;

    /**
     * @return Numeric eccentricity.
     */
    long double
    e() const;

    /**
     * Calculate position of a point on the ellipse using the parametric form.
     * @param t Parameter [0,2π]
     * @return Point on ellipse.
     */
    vec
    point(
            long double t
    ) const;

    /**
     * Calculate position of a point on the ellipse from a given angle.
     * @param radians Angle intersecting point
     * @return Point on ellipse.
     */
    vec
    pointAngle(
            long double radians
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

    std::vector<long double>
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
    long double
    arcLength(
            long double ts,
            long double te,
            long double resolution
    )  const;

    /**
     * @return Two foci as x-values.
     */
    std::array<long double, 2>
    foci() const;

    /**
     * @return Two foci as vectors, whose y-coordinate is 0.
     */
    std::array<vec, 2>
    fociPoints() const;

    /**
     * Calculate t at x.
     * @param x X value (-a <= x <= a)
     * @return
     */
    long double tAtX(
            long double x
    ) const;

    /**
     * Calculate t at y.
     * @param y Y value (-b <= x <= b)
     * @return
     */
    long double tAtY(
            long double y
    ) const;

private:

    long double mA;
    long double mB;
    long double mE;
    long double mFoci;

};


