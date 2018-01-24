//
// Created by jim on 23.01.18.
//

#pragma once

#include <memory>
#include <glm/glm.hpp>
#include "constants.h"

class Body
{

public:

    /**
     * Create a new body.
     * @param mass Planet mass
     * @param radius Planet radius
     * @param a Major semi axis (a > 0)
     * @param e Elliptic eccentricity (0 <= e < 1)
     */
    Body(
            std::string name,
            double mass,
            double radius,
            double a,
            double e
    );

    const std::string &
    getName() const;

    double
    getMass() const;

    double
    getRadius() const;

    const vec &
    getPosition() const;

    /**
     * Calculate the length of the velocity vector,
     * which implicitly is perpendicular on the vector (position - centerPosition).
     * The center position is assumed to be (0|0).
     *
     * @param M Center mass
     * @return
     */
    double
    calculateV(
            double M
    ) const;

    void
    step(
            double M,
            double dt
    );

private:

    std::string mName;
    double mMass;               ///< [kg]   Planet mass (m > 0)
    double mRadius;             ///< [m]    Planet radius (r > 0)
    double mA;                  ///< [m]    Major semi-axis (a > 0)
    double mB;                  ///< [m]    Minor semi-axis (b > 0)
    double mE;                  ///< []     Eccentricity (0 <= e < 1)
    vec mPosition;              ///< [m]    Position of body mass center

};
