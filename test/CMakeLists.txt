
FIND_PACKAGE(GTest REQUIRED)

SET(ORBIT_TEST orbit_test)

SET(CMAKE_CXX_STANDARD 14)
ADD_EXECUTABLE(${ORBIT_TEST} rectangle.cpp ellipse.cpp common.h integral.cpp constants.cpp transform.cpp)
TARGET_LINK_LIBRARIES(${ORBIT_TEST} orbit_lib ${GTEST_LIBRARIES} gtest_main pthread)

INCLUDE_DIRECTORIES(../src)
