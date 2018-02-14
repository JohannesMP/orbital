//
// Created by jim on 23.01.18.
//

#include "Body.h"
#include <orbital/math/elementary.h>

Body::Body(
        std::string_view const name,
        Decimal const mass,
        Decimal const radius,
        Decimal const a,
        Decimal const e
)
        : mName{name}
        , mMass{mass}
        , mRadius{radius}
        , mTrajectory{a != 0 ? a : zero(), e}
{
    // Position orbiting body (determined by a) to the near focal point of this' trajectory:
    mPosition = mTrajectory.focalPoints()[1];

    // Increasing x-axis value:
    // - aphelion
    // - far focal point
    // - trajectory-center
    // - focal point = system center = (0|0)
    // - perihelion
    mTrajectoryCenter = mTrajectory.focalPoints()[0];
}

std::string_view
Body::getName() const
{
    return mName;
}

Decimal
Body::getMass() const
{
    return mMass;
}

void
Body::step(
        Decimal const M,
        Decimal const dt
)
{
    // Move the trajectory to the coordinate center, since ellipse math would not give proper results:
    vec const p = mPosition - mTrajectoryCenter;

    // Trajectory velocity:
    //
    // v = √( G M (2/d - a⁻¹) )
    //
    // Velocity direction is perpendicular on position vector:
    vec const v = glm::normalize(perpendicular(p)) * std::sqrt(G() * M * (2 / length(mPosition) - 1 / mTrajectory.a()));

    // Advance position by straight line, than project back to ellipse:
    mPosition = mTrajectory.projection(p + v * dt) + mTrajectoryCenter;
}

vec const &
Body::getPosition() const
{
    return mPosition;
}

Ellipse<Decimal> const &
Body::getTrajectory() const
{
    return mTrajectory;
}
