//
// Created by jim on 05.02.18.
//

#include "catch/catch.hpp"
#include <orbital/common/DynamicArray.h>
#include <orbital/common/common.h>

TEST_CASE("DynamicArray", "[common]") // NOLINT
{

    DynamicArray<int, 5> array;
    auto const &constantArray = array;

    CHECK(array.size() == 0);
    CHECK(array.capacity() == 5);

    SECTION("appending does change size but not capacity")
    {
        array.push_back(26);

        CHECK(array.size() == 1);
        CHECK(array.capacity() == 5);
    }

    SECTION("exceeding capacity throws exception")
    {
        for (auto i = array.size(); i < array.capacity(); i++)
        {
            array.push_back({});
        }

        CHECK_THROWS(array.push_back({}));

        CHECK(array.size() == 5);
        CHECK(array.capacity() == 5);
    }

    SECTION("iterating")
    {
        CHECK(array.push_back(3) == 3);

        CHECK(*array.begin() == 3);
        CHECK(*constantArray.begin() == 3);

        CHECK(std::distance(array.begin(), array.end()) == 1);
        CHECK(std::distance(constantArray.begin(), constantArray.end()) == 1);
    }

    SECTION("front and back getter")
    {
        array.push_back(3);

        CHECK(array.front() == 3);
        CHECK(constantArray.front() == 3);
        CHECK(array.back() == 3);
        CHECK(constantArray.back() == 3);

        array.push_back(5);

        CHECK(array.front() == 3);
        CHECK(constantArray.front() == 3);
        CHECK(array.back() == 5);
        CHECK(constantArray.back() == 5);
    }

}

