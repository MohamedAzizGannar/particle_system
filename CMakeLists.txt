cmake_minimum_required(VERSION 3.15)
project(particle_system)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find SDL2
find_package(SDL2 REQUIRED)

# Find SDL2_ttf - use modern target approach
find_package(SDL2_ttf REQUIRED)

# Include directories
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/include)

# Recursively find all source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Create executable
add_executable(particle_system ${SOURCES})

# Link libraries - use modern targets
target_link_libraries(particle_system 
    ${SDL2_LIBRARIES}
    SDL2_ttf::SDL2_ttf
)

# Link math library on Linux
if(UNIX AND NOT APPLE)
    target_link_libraries(particle_system m)
endif()

# Debug output
message(STATUS "SDL2_INCLUDE_DIRS: ${SDL2_INCLUDE_DIRS}")
message(STATUS "SDL2_LIBRARIES: ${SDL2_LIBRARIES}")
