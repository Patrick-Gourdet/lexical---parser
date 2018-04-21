cmake_minimum_required(VERSION 3.9)
project(subc)

set(CMAKE_CXX_STANDARD 11)

add_executable(subc subc.cpp lexical.cpp lexical.h analyze.h)