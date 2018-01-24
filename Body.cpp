//
// Created by jim on 23.01.18.
//

#include <cmath>
#include <iostream>
#include "Body.h"

Body::Body(
        std::string name,
        double mass,
        double radius,
        double a,
        double e
)
        : mName{std::move(name)}
        , mMass{mass}
        , mRadius{radius}
        , mA{a}
        , mE{e}
{
    mB = mA * sqrt(1 - mE * mE);

    /*
     * Position orbiting body (determined by a) to the near focal point of this' trajectory:
     *
     * p = a - numerical_eccentricity
     *   = a - (e / a)
     *   = a ( 1 - e)
     */
    mPosition.x = a * (1 - e), 0;

}

const std::string &
Body::getName() const
{
    return mName;
}

double
Body::getMass() const
{
    return mMass;
}

double
Body::getRadius() const
{
    return mRadius;
}

double
Body::calculateV(
        double M
) const
{
    /*
     * Trajectory velocity:
     *
     * v = sqrt(G M(2/d - 1/a))
     */
    double d = length(mPosition);
    return sqrt(G * M * (2 / d - 1 / mA));
}

void
Body::step(
        double M,
        double dt
)
{
    // Calculate velocity in current position.
    // Calculate normalized velocity direction (perpendicular on position vector).
    // Rotate by 90°, using complex number multiplication:
    auto v_complex = complex{mPosition.x, mPosition.y} * complex{0, 1};
    vec v = glm::normalize(vec{v_complex.real(), v_complex.imag()}) * calculateV(M);

    // Advance position by straight line:
    mPosition += v * dt;

    /*
     * Map position back to ellipse:
     * https://math.stackexchange.com/questions/22064/calculating-a-point-that-lies-on-an-ellipse-given-an-angle
     *
     * x = ± (ab cos θ) / sqrt((b cos θ)² + (a cos θ)²)
     * y = ± (ab sin θ) / sqrt((b cos θ)² + (a cos θ)²)
     */
    double theta = atan(mPosition.y / mPosition.x);
    double denominator = sqrt(sq(mB * cos(theta)) + sq(mA * sin(theta))) / mA / mB;
    mPosition.x = copysign(cos(theta) / denominator, mPosition.x);
    mPosition.y = copysign(sin(theta) / denominator, mPosition.y);
}

const vec &
Body::getPosition() const
{
    return mPosition;
}
