
SET(ORBITAL_LIB orbital_lib)

ADD_SUBDIRECTORY(fmt)
INCLUDE_DIRECTORIES(fmt .)

ADD_LIBRARY(${ORBITAL_LIB}
        orbital/physical/System.cpp
        orbital/physical/System.h
        orbital/common/common.h
        orbital/common/common.cpp
        orbital/physical/Body.cpp
        orbital/physical/Body.h
        orbital/graphics/Graphics.cpp
        orbital/graphics/Graphics.h
        orbital/math/Transform.cpp
        orbital/math/Transform.h
        orbital/math/Ellipse.cpp
        orbital/math/Ellipse.h
        orbital/math/Rectangle.cpp
        orbital/math/Rectangle.h
        orbital/math/Line.cpp
        orbital/math/Line.h
        orbital/common/DynamicArray.h)

TARGET_LINK_LIBRARIES(${ORBITAL_LIB} yaml-cpp fmt)
