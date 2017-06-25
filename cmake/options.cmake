# Set install prefix
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX "/opt/scsc17c" CACHE PATH "The install path prefix." FORCE)
endif()

# Set options
option(SCSC_BUILD_BIN "Build binaries."      "ON")
option(SCSC_BUILD_DOC "Build documentation." "ON")

option(SCSC_USE_MKL "Enable MKL support." "ON")
option(SCSC_USE_GPU "Enable GPU support." "ON")

set(SCSC_USE_OMP "OFF" CACHE STRING "Selected OpenMP library. [OFF/GOMP/IOMP] (Require 'SCSC_USE_MKL')")
set_property(CACHE SCSC_USE_OMP PROPERTY STRINGS "OFF;GOMP;IOMP")
if(NOT SCSC_USE_OMP STREQUAL "OFF" AND NOT SCSC_USE_OMP STREQUAL "GOMP" AND NOT SCSC_USE_OMP STREQUAL "IOMP" )
  message(FATAL_ERROR "SCSC_USE_OMP must be either OFF, GOMP, or IOMP")
endif()

# Set variables
set(MKL_OMP ${SCSC_USE_OMP})

# Check compiler support
if(SCSC_BUILD_BIN)
  include(CheckCXXCompilerFlag)
  CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
  if(NOT COMPILER_SUPPORTS_CXX11)
    message(
      FATAL_ERROR
      "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. "
      "Please use a diffferent C++ compiler."
    )
  endif()
endif()
