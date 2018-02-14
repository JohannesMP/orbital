//
// Created by jim on 26.01.18.
//

#include "Line.h"
#include "Radian.h"
#include "Rectangle.h"
#include "Transform.h"
#include "elementary.h"
#include <orbital/common/common.h>

#pragma once

/**
 * Immutable ellipse, provides math.
 */
template<class T>
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
            T const a,
            T const e
    )
        : mA{a}
        , mE{e}
        , mB{a * std::sqrt(1 - sq(e))}
        , mFoci{a * e}
    {
    }

    /**
     * Construct an ellipse based on both semi-axis, instead of major semi-axis and eccentricity.
     * @param a Major semi-axis.
     * @param b Minor semi-axis.
     * @return Constructed ellipse with automatically computed eccentricity.
     */
    static Ellipse
    fromAB(
            T const a,
            T const b
    )
    {
        return Ellipse{a, sqrt(1 - sq(b / a))};
    }

    /**
     * @return Major semi-axis.
     */
    T
    a() const
    {
        return mA;
    }

    /**
     * Return minor semi-axis, which is computed like that:
     * \f$
     * b = a \sqrt{1 - e^2}
     * \f$
     * @return Minor semi-axis.
     */
    T
    b() const
    {
        return mB;
    }

    /**
     * @return Numeric eccentricity.
     */
    T
    e() const
    {
        return mE;
    }

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
    tvec<T>
    point(
            Radian<T> const t
    ) const
    {
        return {mA * t.cos(), mB * t.sin()};
    }

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
    tvec<T>
    pointAngle(
            Radian<T> const theta
    ) const
    {
        T denominator = std::sqrt(sq(mB * theta.cos()) + sq(mA * theta.sin())) / mA / mB;
        return {theta.cos() / denominator, theta.sin() / denominator};
    }

    /**
     * Check whether a point is contained by the ellipse covered area.
     * \f$
     *    \left| p - f_0 \right| + \left| p - f_1 \right|
     *    \leq 2a
     * \f$
     * @param vec Point to check.
     * @return True if inside.
     */
    bool
    contains(
            tvec<T> const &vec
    ) const
    {
        return (vec.x == 0 && vec.y == 0) || (vec.y == 0 && vec.x <= mA && vec.x >= -mA) || (vec.x == 0 && vec.y <= mB && vec.y >= -mB) ||
                (2 * mA >= vectorDistance(focalPoints()[0], vec) + vectorDistance(focalPoints()[1], vec));
    }

    /**
     * Checks whether a rectangle is completely inside the ellipse.
     * @param rect Rectangle to check.
     * @return True if completely inside ellipse.
     */
    bool
    contains(
            Rectangle<Decimal> const &rect
    ) const
    {
        return contains(rect.bottomLeft()) && contains(rect.bottomRight()) && contains(rect.topLeft()) &&
                contains(rect.topRight());
    }

    /**
     * Clips this ellipse to a given rectangle.
     * The calculated ellipse line segments, which are within the rectangle are returned as t-parameter pairs.
     *
     * How the algorithm works:
     *
     * 1) Simple store all intersection points between the ellipse and the 4 edge lines.
     *
     *    Edge case: If a line has 1 intersection, but both end points lie outside of the ellipse,
     *    the intersection is ignored, since it only touches the ellipse. TODO: outsource to intersectionPoints()
     *
     *    Edge case: If one line's endpoint lies on the ellipse, it is ignored as well.
     *    After that, 'points' should have an even number of elements.
     *
     * 2) Check if the first two elements denote a range covered be the Rectangle<Decimal>.
     *    If so, the elements are already in-order, so their can iteratively copied to the resulting ranges.
     *    Otherwise, the elements are in shifted-order, so the Rectangle covers the range denoted by the second and third,
     *    fourth and fifth, ... element and the range between the last and the first element. In this case 2π should be
     *    added to the first element, so it's greater in value than the last element.
     *
     * @param rect Rectangle to clip to.
     * @param transform Transform to apply to the rectangle.
     * @return T pair ranges, denoting ellipse sections lying within the transformed rectangle.
     */
    DynamicArray<std::pair<Radian<T>, Radian<T>>, 4>
    clip(
            Rectangle<T> const &rect,
            Transform<T> const &transform
    ) const
    {
        DynamicArray<Radian<T>, 8> points;
        DynamicArray<std::pair<Radian<T>, Radian<T>>, 4> ranges;

        // Store valid intersections of line, representing a transformed edge of the Rectangle<Decimal>:
        auto storeIntersections = [&](Line<T> const &line) {
            auto const intersections = intersectPoints(line, true);

            if (intersections.size() == 0)
            {
                return;
            }

            if (intersections.size() == 1 && !contains(line.point(0)) && !contains(line.point(1)))
            {
                return;
            }

            if (intersections.size() == 1 &&
                    ((intersections.front() == line.point(0)) || (intersections.front() == line.point(1))))
            {
                return;
            }

            for(auto const &i : intersections)
            {
                points.emplace_back(pointToT(i));
            }
        };

        // Append intersections from line: bottom left - top left
        storeIntersections(Line<T>{transform.apply(rect.bottomLeft()), transform.apply(rect.topLeft())});

        // Append intersections from line: bottom left - bottom right
        storeIntersections(Line<T>{transform.apply(rect.bottomLeft()), transform.apply(rect.bottomRight())});

        // Append intersections from line: top right - top left
        storeIntersections(Line<T>{transform.apply(rect.topRight()), transform.apply(rect.topLeft())});

        // Append intersections from line: top right - bottom right
        storeIntersections(Line<T>{transform.apply(rect.topRight()), transform.apply(rect.bottomRight())});

        std::sort(points.begin(), points.end());

        // No intersection ranges:
        if (points.empty())
        {
            if (rect.containsTransformed(transform.inverse(), {0, 0}) &&
                    rect.containsTransformed(transform.inverse(), {mA, 0}))
            {
                // Complete ellipse is visible, since Rectangle<Decimal> contains both, the coordinate origin and the ellipse's
                // right-most point:
                ranges.emplace_back(0, 2_pi);
            }
        }

        else
        {
            Radian<Decimal> const t = average(points[0], points[1]);
            vec const p = point(t);

            if(rect.containsTransformed(transform.inverse(), p))
            {
                // points are in-order, simple copy them:
                for(auto iter = points.begin(); iter != points.end(); iter += 2)
                {
                    ranges.emplace_back(*iter, *(iter + 1));
                }
            }

            else
            {
                // points are in shifted-order:
                for(auto iter = points.begin() + 1; iter != points.end() - 1; iter++)
                {
                    ranges.emplace_back(*iter, *(iter + 1));
                }
                ranges.emplace_back(points.back(), points.front() + 2_pi);
            }
        }

        return ranges;
    }

    /**
     * Compute intersection points for a given line:
     *
     * \f$
     *    E: \frac{x^2}{a^2} + \frac{y^2}{b^2} = 1 \\
     *    g: \vec{x} = \vec{p} + \lambda \vec{d}
     * \f$
     *
     * g inserted into E:
     *
     * \f$
     *    \frac{ (p_0 + \lambda d_0)^2 }{a^2} +\frac{ (p_1 + \lambda d_1)^2 }{b^2} = 1 \\
     *    (b^2 d_0^2 + a^2 d_1^2) \lambda^2
     *    + (2b^2 p_0 d_0 + 2a^2 p_1 d_1) \lambda
     *    + (b^2 p_0^2 + a^2 p_1^2 - a^2 b^2) = 0
     * \f$
     *
     * Than use the quadratic formula to get \f$ \lambda_0 \f$ and \f$ \lambda_1 \f$
     *
     * The intersection points are: \f$ g(\lambda_0) \f$ and \f$ g(\lambda_1) \f$
     *
     * @param line Line to intersect with ellipse.
     * @param clipToLine If true, only points within \f$ 0 \le \lambda \le 1 \f$ are returned.
     * @return Intersection points.
     */
    DynamicArray<tvec<T>, 2>
    intersectPoints(
            Line<T> const line,
            bool const clipToLine
    ) const
    {
        T const d0 = line.d().x;
        T const d1 = line.d().y;
        T const p0 = line.p().x;
        T const p1 = line.p().y;

        T const a2 = sq(mA);
        T const b2 = sq(mB);

        T const A = b2 * sq(d0) + a2 * sq(d1);
        T const B = 2 * (b2 * p0 * d0 + a2 * p1 * d1);
        T const C = b2 * sq(p0) + a2 * sq(p1) - a2 * b2;

        auto const lambdas = quadratic(A, B, C);

        DynamicArray<tvec<T>, 2> points;

        for (auto const lambda : lambdas)
        {
            auto const intersection = line.point(lambda);
            if (!clipToLine || line.containsByBounds(intersection))
            {
                // Store intersection only if either not clipped to line bounds or the point does lie within bounds:
                points.push_back(intersection);
            }
        }

        return points;
    }

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
    Radian<T>
    arcLength(
            Radian<T> const ts,
            Radian<T> const te,
            T const resolution
    ) const
    {
        T sqA = sq(mA);
        T sqB = sq(mB);
        return Radian<T>{integral(ts, te, resolution, [&](Radian<Decimal> const x) {
            return Radian<T>{std::sqrt(sqA * sq(x.sin()) + sqB * sq(x.cos()))}; // try to omit the Radian{} ctor
        })};
    }

    /**
     * @return Two foci as x-values: \f$ \pm ae \f$
     */
    std::array<T, 2>
    foci() const
    {
        return {-mFoci, mFoci};
    }

    /**
     * @return Two foci as vectors, whose y-coordinate is 0.
     */
    std::array<tvec<T>, 2>
    focalPoints() const
    {
        return {{{-mFoci, 0}, {mFoci, 0}}};
    }

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
    Radian<T>
    tAtX(
            T const x
    ) const
    {
        return Radian<T>::arccos(x / mA);
    }

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
    Radian<T>
    tAtY(
            T const y
    ) const
    {
        return Radian<T>::arcsin(y / mB);
    }

    /**
     * Computes a t-parameters for a given point.
     * @param vec Point whose t-parameter to compute.
     * @attention Returns only reasonable values if the given points lies on the ellipse.
     * @return T-Parameter.
     */
    Radian<T>
    pointToT(
            tvec<T> const vec
    ) const
    {
        auto const t = tAtX(vec.x);
        // Since t-from-x calculation can only return t's for positive y values, flip it over if y-value is negative:
        return vec.y >= 0 ? t : 2_pi - t;
    }

    /**
     * Projects a point to a point on the ellipse, i.e. with the same angle.
     * @attention Mapping \f$ \vec{0} \f$ will result in `nan`.
     * @param vec Point to project.
     * @return Projected point on ellipse.
     */
    tvec<T>
    projection(
            tvec<T> const vec
    ) const
    {
        return vec * ((mA * mB) / std::sqrt(sq(mA) * sq(vec.y) + sq(mB) * sq(vec.x)));
    }

    /**
     * @return Bounding rectangle.
     */
    Rectangle<T>
    boundingRect() const
    {
        return Rectangle<T>{{-mA, -mB}, {mA, mB}};
    }

    /**
     * Serialize ellipse to stream.
     */
    friend std::ostream &
    operator<<(
            std::ostream &os,
            Ellipse const &ellipse
    )
    {
        os << "a=" << ellipse.mA << " b=" << ellipse.mB << " e=" << ellipse.mE;
        return os;
    }

private:

    T const mA;
    T const mB;
    T const mE;
    T const mFoci;

};


