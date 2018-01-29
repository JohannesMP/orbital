//
// Created by jim on 26.01.18.
//

#include <array>
#include <vector>
#include <ostream>
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
            Decimal a,
            Decimal e
    );

    /**
     * @return Major semi-axis.
     */
    Decimal
    a() const;

    /**
     * @return Minor semi-axis.
     */
    Decimal
    b() const;

    /**
     * @return Numeric eccentricity.
     */
    Decimal
    e() const;

    /**
     * Calculate position of a point on the ellipse using the parametric form.
     * @param t Parameter [0,2π]
     * @return Point on ellipse.
     */
    vec
    point(
            Decimal t
    ) const;

    /**
     * Calculate position of a point on the ellipse from a given angle.
     * @param radians Angle intersecting point
     * @return Point on ellipse.
     */
    vec
    pointAngle(
            Decimal radians
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

    std::vector<Decimal>
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
    Decimal
    arcLength(
            Decimal ts,
            Decimal te,
            Decimal resolution
    ) const;

    /**
     * @return Two foci as x-values.
     */
    std::array<Decimal, 2>
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
    Decimal
    tAtX(
            Decimal x
    ) const;

    /**
     * Calculate t at y.
     * @param y Y value (-b <= x <= b)
     * @return
     */
    Decimal
    tAtY(
            Decimal y
    ) const;

    /**
     * @return Bounding rectangle.
     */
    Rectangle
    boundingRect() const;

    /**
     * Serialize ellipse to stream.
     */
    friend std::ostream &
    operator<<(
            std::ostream &os,
            const Ellipse &ellipse
    );

private:

    Decimal mA;
    Decimal mB;
    Decimal mE;
    Decimal mFoci;

};


