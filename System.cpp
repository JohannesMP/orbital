//
// Created by jim on 23.01.18.
//

#include "System.h"
#include <algorithm>

System::System(
        const Body &centralBody,
        double dt
)
        : mCentralBody{centralBody}
        , mDt{dt}
{
}

void
System::stepSimulation()
{
    for(Body &body : mBodies)
    {
        body.step(mCentralBody.getMass(), mDt);
    }
}

Body &
System::addBody(const Body &body)
{
    mBodies.emplace_back(body);
    return mBodies.back();
}

void
System::foreach(std::function<void(Body &)> &&l)
{
    l(mCentralBody);
    for(auto &body : mBodies)
    {
        l(body);
    }
}
