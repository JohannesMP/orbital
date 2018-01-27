
SET(ORBIT_LIB orbit_lib)

ADD_SUBDIRECTORY(fmt)
INCLUDE_DIRECTORIES(fmt)

ADD_LIBRARY(${ORBIT_LIB} System.cpp System.h constants.h constants.cpp Body.cpp Body.h Graphics.cpp Graphics.h Transform.cpp Transform.h Ellipse.cpp Ellipse.h Rectangle.cpp Rectangle.h)
TARGET_LINK_LIBRARIES(${ORBIT_LIB} yaml-cpp fmt)
