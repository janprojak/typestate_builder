#-------------------------------------------------------------------#
# cmake version

cmake_minimum_required(VERSION 3.22)

#-------------------------------------------------------------------#
# project flags config

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#-------------------------------------------------------------------#
# project config

project(typestate_builder)

#-------------------------------------------------------------------#
# project sources

set(SOURCES
    car.hpp
    car_builder.hpp
    main.cpp
    mandatory_values.hpp
)

#-------------------------------------------------------------------#
# project type

add_executable(${PROJECT_NAME} ${SOURCES})

#-------------------------------------------------------------------#
# include directories

target_include_directories(${PROJECT_NAME}
    PRIVATE .
)

#-------------------------------------------------------------------#