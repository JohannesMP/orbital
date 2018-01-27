//
// Created by jim on 27.01.18.
//

#pragma once

#include <gtest/gtest.h>

inline void
assertDouble(
        double a,
        const std::string &b
)
{
    std::stringstream ss;
    ss << a;
    std::string number = ss.str().substr(0, b.length());
    ASSERT_EQ(number, b);
}
