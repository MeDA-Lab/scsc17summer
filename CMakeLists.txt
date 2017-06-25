# The main CMake setting

# Set project
project(SCSC17c)
cmake_minimum_required(VERSION 2.8.12)

# Set Makefile
set(CMAKE_COLOR_MAKEFILE ON)
# set(CMAKE_VERBOSE_MAKEFILE ON)

# Set module path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")

# Set the include path
include_directories("${PROJECT_SOURCE_DIR}/include")

# Sets the options
include(cmake/options.cmake)

# Sets the packages
include(cmake/packages.cmake)

# Add subdirectories
add_subdirectory(data)
add_subdirectory(src)
add_subdirectory(doxygen)

# Create configure files
include(cmake/configure.cmake)
