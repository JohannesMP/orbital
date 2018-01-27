//
// Created by jim on 27.01.18.
//

#include <sstream>
#include <cmath>
#include "FloatingPointComparator.h"

FloatingPointComparator::FloatingPointComparator(
        const std::string &str
)
        : mStr{str}
{
}

const std::string &
FloatingPointComparator::str() const
{
    return mStr;
}

std::ostream &
operator<<(
        std::ostream &os,
        const FloatingPointComparator &comparator
)
{
    os << '"' << comparator.mStr << "...\"";
    return os;
}

bool
operator==(
        double num,
        const FloatingPointComparator &c
)
{
    std::stringstream ss;
    ss << std::fixed << num;

    // Avoid negative zero:
    double back;
    ss >> back;
    if(std::signbit(back) && back == 0.0)
    {
        ss.str("0.0");
    }

    std::string s = ss.str();

    return 0 == s.compare(0, c.str().length(), c.str());
}


FloatingPointComparator
operator ""_c(
        const char *s,
        std::size_t
)
{
    return FloatingPointComparator{s};
}
