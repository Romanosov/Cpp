cmake_minimum_required(VERSION 2.8.4)
project(Settings)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES settings.cpp)
add_executable(Settings ${SOURCE_FILES})

add_library(settings SHARED ${SOURCES} settings.cpp)