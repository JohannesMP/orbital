CMAKE_MINIMUM_REQUIRED(VERSION 3.9)
PROJECT(orbit)

SET(CMAKE_CXX_STANDARD 14)

ADD_EXECUTABLE(orbit main.cpp System.cpp System.h constants.h constants.cpp Body.cpp Body.h Graphics.cpp Graphics.h)