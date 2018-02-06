//
// Created by jim on 23.01.18.
//

#include "System.h"
#include <yaml-cpp/yaml.h>

System::System(
        const Body &centralBody,
        Decimal dt
)
        : mCentralBody{centralBody}
        , mDt{dt}
{
}

System::System(
        const std::string_view &systemArchiveFile,
        const std::string_view &systemName,
        Decimal dt
)
        : mDt{dt}
{
    auto data = YAML::LoadFile(systemArchiveFile.data())[systemName.data()];

    auto deserialize = [](YAML::Node node) {
        return Body{node["name"].as<std::string>(), node["mass"].as<Decimal>() * 1000.0_df,
                node["radius"].as<Decimal>() * 1000.0_df, au(node["a"].as<Decimal>()), node["e"].as<Decimal>()};
    };

    mCentralBody = deserialize(data["central-body"]);
    for (int i = 0; i < data["bodies"].size(); i++)
    {
        add(deserialize(data["bodies"][i]));
    }
}


void
System::stepSimulation()
{
    for (Body &body : mBodies)
    {
        body.step(mCentralBody.getMass(), mDt);
    }
}

Body &
System::add(const Body &body)
{
    mBodies.emplace_back(body);
    return mBodies.back();
}

void
System::foreach(std::function<void(Body &)> &&l)
{
    l(mCentralBody);
    for (auto &body : mBodies)
    {
        l(body);
    }
}

Body &
System::find(
        const std::string_view &name
)
{
    if (name == mCentralBody.getName())
    {
        return mCentralBody;
    }

    auto iter = std::find_if(mBodies.begin(), mBodies.end(), [&name](Body &body) {
        return body.getName() == name;
    });

    if (mBodies.end() == iter)
    {
        throw std::runtime_error("No such body in system");
    }

    return *iter;
}
