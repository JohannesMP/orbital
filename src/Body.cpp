//
// Created by jim on 23.01.18.
//

#include <cmath>
#include <iostream>
#include "Body.h"

Body::Body(
        std::string name,
        long double mass,
        long double radius,
        long double a,
        long double e
)
        : mName{std::move(name)}
        , mMass{mass}
        , mRadius{radius}
        , mTrajectory{a != 0 ? a : ZERO, e}
{
    /*
     * Position orbiting body (determined by a) to the near focal point of this' trajectory:
     *
     * p = a - numerical_eccentricity
     *   = a - (e / a)
     *   = a ( 1 - e)
     */
    mPosition.x = mTrajectory.foci()[1];

    /*
     * Increasing x-axis value:
     * - aphelion
     * - far focal point
     * - trajectory-center
     * - focal point = system center = (0|0)
     * - perihelion
     */
    mTrajectoryCenter.x = -mTrajectory.e() * mTrajectory.a();
}

const std::string &
Body::getName() const
{
    return mName;
}

long double
Body::getMass() const
{
    return mMass;
}

long double
Body::getRadius() const
{
    return mRadius;
}

long double
Body::calculateV(
        long double M
) const
{
    /*
     * Trajectory velocity:
     *
     * v = √( G M (2/d - a⁻¹) )
     */
    long double d = length(mPosition);
    return std::sqrt(G * M * (2 / d - 1 / mTrajectory.a()));
}

void
Body::step(
        long double M,
        long double dt
)
{
    vec p = mPosition - mTrajectoryCenter;

    // Calculate velocity in current position.
    // Calculate normalized velocity direction (perpendicular on position vector).
    // Rotate by 90°, using complex number multiplication:
    auto v_complex = complex{p.x, p.y} * complex{0, 1};
    vec v = glm::normalize(vec{v_complex.real(), v_complex.imag()}) * calculateV(M);

    // Advance position by straight line:
    p += v * dt;

    /*
     * Map position back to ellipse: TODO: use Ellipse methods
     * https://math.stackexchange.com/questions/22064/calculating-a-point-that-lies-on-an-ellipse-given-an-angle
     *
     * x = ± (ab cos θ) / √((b cos θ)² + (a cos θ)²)
     * y = ± (ab sin θ) / √((b cos θ)² + (a cos θ)²)
     */
    long double theta = std::atan(p.y / p.x); // TODO: use atan2 ?
    long double denominator = std::sqrt(sq(mTrajectory.b() * std::cos(theta)) + sq(mTrajectory.a() * std::sin(theta))) / mTrajectory.a() /
            mTrajectory.b();
    mPosition.x = std::copysign(std::cos(theta) / denominator, p.x) + mTrajectoryCenter.x;
    mPosition.y = std::copysign(std::sin(theta) / denominator, p.y) + mTrajectoryCenter.y;
}

const vec &
Body::getPosition() const
{
    return mPosition;
}

const Ellipse &
Body::getTrajectory() const
{
    return mTrajectory;
}
