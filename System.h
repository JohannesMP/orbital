//
// Created by jim on 23.01.18.
//

#pragma once

#include <list>
#include <functional>
#include "Body.h"

/**
 * A system storing a state bound to time.
 */
class System
{

public:

    System(
            const Body &centralBody,
            double dt
    );

    Body &
    addBody(const Body &body);

    void
    stepSimulation();

    void
    foreach(
            std::function<void(Body &)> &&l
    );

private:

    double mDt;                 ///< [s]    Amount of time between two steps
    std::list<Body> mBodies;
    Body mCentralBody;

};
