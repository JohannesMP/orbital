//
// Created by jim on 26.01.18.
//

#include <array>
#include <vector>
#include <ostream>
#include "constants.h"
#include "Rectangle.h"
#include "Transform.h"
#include "Line.h"

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
     * Construct an ellipse based on both semi-axis, instead of major semi-axis and eccentricity.
     * @param a Major semi-axis.
     * @param b Minor semi-axis.
     * @return Constructed ellipse with automatically computed eccentricity.
     */
    static Ellipse
    fromAB(
            const Decimal a,
            const Decimal b
    );

    /**
     * @return Major semi-axis.
     */
    Decimal
    a() const;

    /**
     * Return minor semi-axis, which is computed like that:
     * \f$
     * b = a \sqrt{1 - e^2}
     * \f$
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
     * \f$
     * \vec{v} =
     *     \begin{pmatrix}
     *         a \cdot cos(t) \\
     *         b \cdot sin(t)
     *     \end{pmatrix}
     * \f$
     * @param t Parameter.
     * @return Point on ellipse.
     */
    vec
    point(
            Decimal t
    ) const;

    /**
     * Calculate position of a point on the ellipse from a given angle.
     * \f$
     * \vec{v} =
     *     \begin{pmatrix}
     *         \pm \frac{ ab \cdot cos \theta }{ \sqrt{(b \cdot cos \theta)^2 + (a \cdot cos \theta)^2} } \\
     *         \pm \frac{ ab \cdot sin \theta }{ \sqrt{(b \cdot cos \theta)^2 + (a \cdot cos \theta)^2} }
     *     \end{pmatrix}
     * \f$
     * @param theta Angle intersecting point
     * @return Point on ellipse.
     */
    vec
    pointAngle(
            Decimal theta
    ) const;

    /**
     * Check whether a point is contained by the ellipse covered area.
     * \f$
     *    \left| p - f_0 \right| + \left| p - f_1 \right|
     *    \leq 2a
     * \f$
     * @param p Point to check.
     * @return True if inside.
     */
    bool
    contains(
            const vec &p
    ) const;

    /**
     * Checks whether a rectangle is completely inside the ellipse.
     * @param rect Rectangle to check.
     * @return True if completely inside ellipse.
     */
    bool
    contains(
            const Rectangle &rect
    ) const;

    /**
     * Clips this ellipse to a given rectangle.
     * The calculated ellipse line segments, which are within the rectangle are returned as t-parameter pairs.
     * @param rect Rectangle to clip to.
     * @return Line using t pairs. Empty of no overlap at all.
     */
    DynamicArray<std::pair<Decimal, Decimal>, 4>
    clip(
            const Rectangle &rect,
            const Transform &transform
    ) const;

    /**
     * Compute intersection points for a given line.
     *
     * @param p Start point of line.
     * @param d Direction vector of line.
     * @return Number of intersections followed by the actual intersection points.
     */
    DynamicArray<vec, 2>
    intersectPoints(
            Line const line,
            bool const clipToLine
    ) const;

    /**
     * Calculate the length of an arc slice within `ts` and `te`.
     * \f$
     * \int_{ts}^{te} \sqrt{ a^2 sin^2 x + b^2 cos^2 x } dx
     * \f$
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
     * @return Two foci as x-values: \f$ \pm ae \f$
     */
    std::array<Decimal, 2>
    foci() const;

    /**
     * @return Two foci as vectors, whose y-coordinate is 0.
     */
    std::array<vec, 2>
    fociPoints() const;

    /**
     * Calculate t parameter at a given x value.
     *
     * \f$
     *     t = arccos( \frac{x}{a} ) \\
     *     x \in \left[ -a , a \right]
     * \f$
     *
     * @attention The x value which must lie within the ellipse covered x-axis range,
     *            otherwise a math domain error occurs.
     * @param x X value
     * @return
     */
    Decimal
    tAtX(
            Decimal x
    ) const;

    /**
     * Calculate t parameter at a given y value.
     *
     * \f$
     *     t = arcsin( \frac{y}{b} ) \\
     *     y \in \left[ -b , b \right]
     * \f$
     *
     * @attention The y value which must lie within the ellipse covered y-axis range,
     *            otherwise a math domain error occurs.
     * @param y Y value
     * @return
     */
    Decimal
    tAtY(
            Decimal y
    ) const;

    /**
     * Computes a t-parameters for a given point.
     * @param v Point whose t-parameter to compute.
     * @attention Returns only reasonable values if the given points lies on the ellipse.
     * @return T-Parameter.
     */
    Decimal
    pointToT(
            vec const v
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


