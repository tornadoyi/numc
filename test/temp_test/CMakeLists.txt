cmake_minimum_required (VERSION 2.6)

project (temp_test)

#SET(CMAKE_BUILD_TYPE "Release")

SET (CMAKE_C_COMPILER "/usr/bin/clang")
SET (CMAKE_CXX_COMPILER "/usr/bin/clang++")

include("../../numc/numc.cmake")

aux_source_directory(. SOURCES)
add_compile_options(-std=c++11 -march=native -save-temps -O3 -Rpass=loop-vectorize -Rpass-missed=loop-vectorize)  #-march=skylake-avx512
set(CMAKE_VERBOSE_MAKEFILE on)

# message for all information
get_property(include_directories DIRECTORY PROPERTY INCLUDE_DIRECTORIES)
get_property(compile_options DIRECTORY PROPERTY COMPILE_OPTIONS)
get_property(compile_flags DIRECTORY PROPERTY COMPILE_FLAGS)


# debug outputs
message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
message(STATUS "SOURCES: ${SOURCES}")
message(STATUS "INCLUDE_DIRECTORIES: ${include_directories}")
message(STATUS "COMPILE_OPTIONS: ${compile_options}")

add_executable(${PROJECT_NAME} ${SOURCES})





