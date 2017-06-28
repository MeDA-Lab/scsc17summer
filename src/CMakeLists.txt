# The CMake setting of 'src/'

# Break
if(NOT SCSC_BUILD_BIN)
  return()
endif()

# Function
macro(SET_TARGET target suffix files)
  target_include_directories(${target} SYSTEM PUBLIC "${INCS}")
  target_link_libraries(${target} "${LIBS}")
  target_compile_definitions(${target} PUBLIC "${DEFS}")
  set_target_properties(${target} PROPERTIES COMPILE_FLAGS "${COMFLGS}")
  set_target_properties(${target} PROPERTIES LINK_FLAGS    "${LNKFLGS}")

  add_custom_target(
    run${suffix}
    COMMAND $<TARGET_FILE:${target}> "-f${CMAKE_SOURCE_DIR}/${SCSC_OBJ_INPUT}" "-o${CMAKE_SOURCE_DIR}/${SCSC_OBJ_OUTPUT}"  "-t${SCSC_METHOD}"
    DEPENDS ${target}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Running ${target} with ${files}"
  )
endmacro()

# Function
function(SET_CODE prefix text)
  string(TOUPPER ${prefix} PREFIX)
  file(
    GLOB_RECURSE files
    RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/*/${prefix}*.cpp"
  )
  file(
    GLOB_RECURSE spfiles
    RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/*/${prefix}*sparse*.cpp"
  )
  if(spfiles)
    list(REMOVE_ITEM files ${spfiles})
  else()
    set(spfiles ${files})
  endif()
  list(GET files 0 file0)
  list(GET spfiles 0 spfile0)
  set(SCSC_SRC_${PREFIX} ${file0} CACHE STRING "The ${text} code for dense version.")
  set(SCSC_SRC_SP_${PREFIX} ${spfile0} CACHE STRING "The ${text} code for sparse version.")
  set_property(CACHE SCSC_SRC_${PREFIX} PROPERTY STRINGS "${files}")
  set_property(CACHE SCSC_SRC_SP_${PREFIX} PROPERTY STRINGS "${spfiles}")
endfunction()

# Set codes
set_code(construct_laplacian "Laplacian construction")
set_code(map_boundary        "boundary mapping")
set_code(solve_harmonic      "harmonic problem solving")

# Dense target
list(APPEND core_files
  core/read_args.cpp
  core/read_object.cpp
  core/verify_boundary.cpp
  core/reorder_vertex.cpp
  core/write_object.cpp
)
add_executable(main main.cpp ${core_files} ${SCSC_SRC_CONSTRUCT_LAPLACIAN} ${SCSC_SRC_MAP_BOUNDARY} ${SCSC_SRC_SOLVE_HARMONIC})
set_target(main "" "${SCSC_SRC_CONSTRUCT_LAPLACIAN} ${SCSC_SRC_MAP_BOUNDARY} ${SCSC_SRC_SOLVE_HARMONIC}")

# Sparse target
list(APPEND sparse_files
  core/read_args.cpp
  core/read_object.cpp
  sparse/verify_boundary_sparse.cpp
  core/reorder_vertex.cpp
  core/write_object.cpp
)
add_executable(main_sp main_sparse.cpp ${sparse_files} ${SCSC_SRC_SP_CONSTRUCT_LAPLACIAN} ${SCSC_SRC_SP_MAP_BOUNDARY} ${SCSC_SRC_SP_SOLVE_HARMONIC})
set_target(main_sp "_sp" "${SCSC_SRC_SP_CONSTRUCT_LAPLACIAN} ${SCSC_SRC_SP_MAP_BOUNDARY} ${SCSC_SRC_SP_SOLVE_HARMONIC}")

# Test target
list(APPEND test_files
  core/read_args.cpp
  core/read_object.cpp
)
add_executable(test_laplacian test.cpp ${test_files} ${SCSC_SRC_CONSTRUCT_LAPLACIAN})
set_target(test_laplacian "_test" "${SCSC_SRC_CONSTRUCT_LAPLACIAN}")
