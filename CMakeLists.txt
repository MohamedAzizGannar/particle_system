cmake_minimum_required(VERSION 3.15)
project(particle_system)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON ) 

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

file(GLOB SOURCES "src/*.cpp")

add_executable(particle_system ${SOURCES})

target_link_libraries(particle_system ${SDL2_LIBRARIES})

