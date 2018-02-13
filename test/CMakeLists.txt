
FIND_PACKAGE(GTest REQUIRED)

SET(ORBITAL_TEST orbital_test)

ADD_EXECUTABLE(${ORBITAL_TEST} rectangle.cpp ellipse.cpp integral.cpp math.cpp transform.cpp dynamic_array.cpp)
TARGET_LINK_LIBRARIES(${ORBITAL_TEST} orbital_lib ${GTEST_LIBRARIES} gtest_main pthread)

INCLUDE_DIRECTORIES(../src)
