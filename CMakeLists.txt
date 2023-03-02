cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(MES)
add_executable(${PROJECT_NAME} main.cpp)



# Custom library
#add_library(mylib STATIC ../files.cpp)
#target_include_directories(${PROJECT_NAME} PUBLIC mylib)



# External library with cmake files
#find_package(EXT_LIB [Version] REQUIRED graphics network)
#target_include_directories(hello PUBLIC ${EXT_LIB_INCLUDE_DIR})
#target_link_libraries(hello PUBLIC ${EXT_LIB_LIBRARIES} ${EXT_LIB_DEPENDENCIES})



# for external lib
#target_include_directories(${PROJECT_NAME} PUBLIC ${EXT_LIB_NAME})
#target_include_directories(${PROJECT_NAME} PUBLIC ${EXT_LIB_NAME} ${EXT_LIB_NAME_DEPENDENCIES})


# for external lib manually
#find_library(VARLIB libname) // default libs
#target_link_libraries(${PROJECT_NAME} PUBLIC $(VARLIB))


#find_library(VARLIB libname) // custom path libs
#target_link_libraries(${PROJECT_NAME} PUBLIC $(VARLIB))

#set(MY_LIB_INCLUDE ~/path)
#target_include_directories(${PROJECT_NAME} PUBLIC ${MY_LIB_INCLUDE})