# The CMake setting of 'data/'

# Set objects
file(GLOB_RECURSE obj_files RELATIVE "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/*.obj")

set(SCSC_OBJ_INPUT "data/Square.obj" CACHE STRING "The input object.")
set_property(CACHE SCSC_OBJ_INPUT PROPERTY STRINGS "${obj_files}")

set(SCSC_OBJ_OUTPUT "output.obj" CACHE STRING "The output object.")
