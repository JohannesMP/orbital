CMAKE_MINIMUM_REQUIRED(VERSION 3.9)
PROJECT(orbit)

SET(CMAKE_CXX_STANDARD 14)

# Copy planets file:
ADD_CUSTOM_COMMAND(
        OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/planets.yml"
        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/planets.yml" "${CMAKE_CURRENT_BINARY_DIR}/planets.yml"
        DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/planets.yml"
)
ADD_CUSTOM_TARGET(planets DEPENDS planets.yml)

# Build src:
ADD_SUBDIRECTORY(src)

# Build main executable:
SET(ORBIT_MAIN orbit_main)
ADD_EXECUTABLE(${ORBIT_MAIN} main.cpp)
TARGET_LINK_LIBRARIES(${ORBIT_MAIN} orbit_lib)
ADD_DEPENDENCIES(${ORBIT_MAIN} planets)

# Build tests:
ADD_SUBDIRECTORY(test)
