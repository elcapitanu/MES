cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(MES)
add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(lib)
target_include_directories(${PROJECT_NAME} PUBLIC lib)
target_link_directories(${PROJECT_NAME} PRIVATE lib)
target_link_libraries(${PROJECT_NAME} driver interface mes)