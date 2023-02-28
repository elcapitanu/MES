cmake_minimum_required(VERSION 3.10)
project(MES)

set(MES main.cpp)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(MES ../main.cpp)