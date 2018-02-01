
SET(ORBIT_LIB orbit_lib)

ADD_SUBDIRECTORY(fmt)
INCLUDE_DIRECTORIES(fmt)

ADD_LIBRARY(${ORBIT_LIB} orbit/System.cpp orbit/System.h orbit/constants.h orbit/constants.cpp orbit/Body.cpp orbit/Body.h orbit/Graphics.cpp orbit/Graphics.h orbit/Transform.cpp orbit/Transform.h orbit/Ellipse.cpp orbit/Ellipse.h orbit/Rectangle.cpp orbit/Rectangle.h orbit/LinearFunction.cpp orbit/LinearFunction.h)
TARGET_LINK_LIBRARIES(${ORBIT_LIB} yaml-cpp fmt)
