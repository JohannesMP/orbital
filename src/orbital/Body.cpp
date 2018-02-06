//
// Created by jim on 23.01.18.
//

#include <cmath>
#include <iostream>
#include "Body.h"

Body::Body(
        std::string name,
        Decimal mass,
        Decimal radius,
        Decimal a,
        Decimal e
)
        : mName{std::move(name)}
        , mMass{mass}
        , mRadius{radius}
        , mTrajectory{a != 0 ? a : ZERO, e}
{
    // Position orbiting body (determined by a) to the near focal point of this' trajectory:
    mPosition.x = mTrajectory.foci()[1];

    // Increasing x-axis value:
    // - aphelion
    // - far focal point
    // - trajectory-center
    // - focal point = system center = (0|0)
    // - perihelion
    mTrajectoryCenter.x = -mTrajectory.e() * mTrajectory.a();
}

const std::string &
Body::getName() const
{
    return mName;
}

Decimal
Body::getMass() const
{
    return mMass;
}

Decimal
Body::getRadius() const
{
    return mRadius;
}

void
Body::step(
        Decimal M,
        Decimal dt
)
{
    vec p = mPosition - mTrajectoryCenter;

    // Trajectory velocity:
    //
    // v = √( G M (2/d - a⁻¹) )
    Decimal vValue = std::sqrt(G * M * (2 / length(mPosition) - 1 / mTrajectory.a()));

    // Calculate velocity in current position.
    // Calculate normalized velocity direction (perpendicular on position vector).
    // Rotate by 90°, using complex number multiplication:
    auto v_complex = complex{p.x, p.y} * complex{0, 1};
    vec v = glm::normalize(vec{v_complex.real(), v_complex.imag()}) * vValue;

    // Advance position by straight line:
    p += v * dt;

    //
    // Map position back to ellipse:
    // https://math.stackexchange.com/questions/22064/calculating-a-point-that-lies-on-an-ellipse-given-an-angle
    //
    // x = ± (ab cos θ) / √((b cos θ)² + (a cos θ)²)
    // y = ± (ab sin θ) / √((b cos θ)² + (a cos θ)²)
    //
    mPosition = mTrajectory.pointAngle(angle(p)) + mTrajectoryCenter;
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