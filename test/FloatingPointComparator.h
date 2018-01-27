//
// Created by jim on 27.01.18.
//

#pragma once

#include <string>
#include <ostream>

class FloatingPointComparator
{

public:

    FloatingPointComparator(
            const std::string &str
    );

    const std::string &
    str() const;

    friend std::ostream &
    operator<<(
            std::ostream &os,
            const FloatingPointComparator &comparator
    );

private:

    std::string mStr;

};

bool
operator==(
        double num,
        const FloatingPointComparator &c
);

FloatingPointComparator
operator ""_c(
        const char *s,
        std::size_t
);
