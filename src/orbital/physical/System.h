//
// Created by jim on 23.01.18.
//

#pragma once

#include "Body.h"
#include <functional>
#include <list>

/**
 * A system storing a state bound to time.
 */
class System
{

public:

    System(
            const Body &centralBody,
            Decimal dt
    );

    /**
     * Create a system based on a Yaml archive file.
     *
     * a [AU]
     * radius [km]
     * mass [kg]
     *
     * @param systemArchiveFile Archive to load.
     * @param systemName Name of system to load from archive.
     * @param dt Time step size.
     */
    System(
            const std::string_view &systemArchiveFile,
            const std::string_view &systemName,
            Decimal dt
    );

    Body &
    add(const Body &body);

    void
    stepSimulation();

    void
    foreach(
            std::function<void(Body &)> &&l
    );

    Body &
    find(
            const std::string_view &name
    );

private:

    Decimal mDt;                 ///< [s]    Amount of time between two steps
    std::list<Body> mBodies;
    Body mCentralBody;

};
