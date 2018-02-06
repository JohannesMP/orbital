
SET(ORBITAL_LIB orbital_lib)

SET(CMAKE_CXX_STANDARD 14)

ADD_SUBDIRECTORY(fmt)
INCLUDE_DIRECTORIES(fmt)

ADD_LIBRARY(${ORBITAL_LIB} orbital/System.cpp orbital/System.h orbital/constants.h orbital/constants.cpp orbital/Body.cpp orbital/Body.h orbital/Graphics.cpp orbital/Graphics.h orbital/Transform.cpp orbital/Transform.h orbital/Ellipse.cpp orbital/Ellipse.h orbital/Rectangle.cpp orbital/Rectangle.h orbital/Line.cpp orbital/Line.h orbital/DynamicArray.h)
TARGET_LINK_LIBRARIES(${ORBITAL_LIB} yaml-cpp fmt)
