CMAKE_MINIMUM_REQUIRED(VERSION 3.9)
PROJECT(orbit)

SET(CMAKE_CXX_STANDARD 14)

ADD_EXECUTABLE(orbit main.cpp System.cpp System.h constants.h constants.cpp Body.cpp Body.h Graphics.cpp Graphics.h)
TARGET_LINK_LIBRARIES(orbit yaml-cpp)

# Copy planets file:
ADD_CUSTOM_COMMAND(
        OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/planets.yml"
        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/planets.yml" "${CMAKE_CURRENT_BINARY_DIR}/planets.yml"
        DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/planets.yml"
)
ADD_CUSTOM_TARGET(planets DEPENDS planets.yml)
ADD_DEPENDENCIES(orbit planets)
