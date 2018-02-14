
SET(ORBITAL_TEST orbital_test)

ADD_EXECUTABLE(${ORBITAL_TEST}
        main.cpp
        math.cpp
        dynamic_array.cpp
        ellipse.cpp
        integral.cpp
        rectangle.cpp
        transform.cpp common.h common.cpp)

TARGET_LINK_LIBRARIES(${ORBITAL_TEST} orbital_lib pthread)

TARGET_COMPILE_OPTIONS(${ORBITAL_TEST} PUBLIC)

INCLUDE_DIRECTORIES(../src)
