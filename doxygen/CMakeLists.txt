# The CMake setting of 'doxygen/'

# Break
if(NOT SCSC_BUILD_DOC)
  return()
endif()

# Set documentation directory
set(SCSC_DOCS_DIR "${PROJECT_BINARY_DIR}/docs")
set(SCSC_DOCS_DIR "${SCSC_DOCS_DIR}" PARENT_SCOPE)

# Add rule
add_custom_target(
  doc
  COMMAND doxygen "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile"
  COMMENT "Generating documentation with Doxygen"
)

# Add to clean rule
set_directory_properties(
  PROPERTIES
  ADDITIONAL_MAKE_CLEAN_FILES
  "${SCSC_DOCS_DIR}"
)

# Set install rule
install(DIRECTORY "${SCSC_DOCS_DIR}/" DESTINATION docs)
