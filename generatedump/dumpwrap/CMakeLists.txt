cmake_minimum_required(VERSION 2.6)
project(dumpwrap)
set(CMAKE_CXX_FLAGS -std=gnu++11)
add_library(dumpwrap dumpwrapper.cpp)