cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Iinclude -std=c++20 -Wall")

project(MES)
add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(lib)
target_include_directories(${PROJECT_NAME} PUBLIC lib)
target_link_directories(${PROJECT_NAME} PRIVATE lib)
target_link_libraries(${PROJECT_NAME} mes my_time interface inputs tcp opc-ua Threads::Threads)
#target_link_libraries(${PROJECT_NAME} mes my_time interface inputs tcp opc-ua Threads::Threads PostgreSQL::PostgreSQL)

add_subdirectory(lib/threads)
target_include_directories(${PROJECT_NAME} PUBLIC lib/threads)
target_link_directories(${PROJECT_NAME} PRIVATE lib/threads)
set(THREADS_PREFER_PTHREAD_FLAG ON)
	find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} mthread)

#find_package(PostgreSQL REQUIRED)

find_package(open62541)
target_link_libraries(${PROJECT_NAME} open62541)