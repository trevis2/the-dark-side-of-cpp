# stop if cmake version below 3.5
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(sampleProject)
set(CMAKE_CXX_COMPILER g++)

# detect operating system and host processor
message(STATUS "Compiling on a ${CMAKE_SYSTEM_NAME} system")
message(STATUS "Host processor is ${CMAKE_HOST_SYSTEM_PROCESSOR}")

############################################################
# Create an executable
############################################################

# Add an executable with the above sources
add_executable(sampleProject 
    src/main.cpp
)