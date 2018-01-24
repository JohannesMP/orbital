//
// Created by jim on 23.01.18.
//

#include "System.h"
#include <yaml-cpp/yaml.h>
#include <iostream>

System::System(
        const Body &centralBody,
        double dt
)
        : mCentralBody{centralBody}
        , mDt{dt}
{
}

System::System(
        const std::string &systemArchiveFile,
        const std::string &systemName,
        double dt
)
    : mDt{dt}
{
    auto data = YAML::LoadFile(systemArchiveFile)[systemName];

    auto deserialize = [](YAML::Node node) {
        return Body{
                node["name"].as<std::string>(),
                node["mass"].as<double>() * 1000.0,
                node["radius"].as<double>() * 1000.0,
                node["a"].as<double>() * AU,
                node["e"].as<double>()
        };
    };

    mCentralBody = deserialize(data["central-body"]);
    for(int i = 0; i < data["bodies"].size(); i++)
    {
        mBodies.emplace_back(deserialize(data["bodies"][i]));
    }
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
