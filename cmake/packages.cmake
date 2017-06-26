  # Set complier flags
set(CMAKE_CXX_FLAGS "-std=c++11 -O2 -g -Wall -Wextra -pedantic -Wl,--no-as-needed")

if(NOT SCSC_BUILD_BIN)
  return()
endif()

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

# Set default variables
set(INCS "")
set(LIBS "")
set(COMFLGS "")
set(LNKFLGS "")

# MKL
if(SCSC_USE_MKL)
  find_package(MKL REQUIRED)
  if(MKL_FOUND)
    list(APPEND INCS "${MKL_INCLUDES}")
    list(APPEND LIBS "${MKL_LIBRARIES}")
    set(COMFLGS "${COMFLGS} ${MKL_FLAGS}")
  endif()
endif()

# OpenMP
if(SCSC_USE_OMP)
  set(OpenMP ${SCSC_USE_OMP})

  find_package(OpenMP REQUIRED)
  if(OpenMP_FOUND)
    set(COMFLGS "${COMFLGS} ${OpenMP_CXX_FLAGS}")
    set(LNKFLGS "${LNKFLGS} ${OpenMP_CXX_FLAGS}")
  endif()

  find_package(OpenMPLib REQUIRED)
  if(OpenMPLib_FOUND)
    list(APPEND LIBS "${OpenMP_LIBRARIES}")
  endif()

  unset(OpenMP)
elseif(SCSC_USE_GPU)
  find_package(OpenMP REQUIRED)
  if(OpenMP_FOUND)
    set(COMFLGS "${COMFLGS} ${OpenMP_CXX_FLAGS}")
    set(LNKFLGS "${LNKFLGS} ${OpenMP_CXX_FLAGS}")
  endif()
endif()

# CUDA & MAGMA
if(SCSC_USE_GPU)
  find_package(CUDA REQUIRED)
  find_package(MAGMA REQUIRED)
  if(MAGMA_FOUND)
    list(APPEND INCS "${MAGMA_INCLUDES}")
    list(APPEND LIBS "${MAGMA_SPARSE_LIBRARY}" "${MAGMA_LIBRARY}")
  endif()
  if(CUDA_FOUND)
    list(APPEND INCS "${CUDA_INCLUDE_DIRS}")
    list(APPEND LIBS "${CUDA_cusparse_LIBRARY}" "${CUDA_cublas_LIBRARY}" "${CUDA_CUDART_LIBRARY}")
  endif()
endif()

# DOxygen
if(SCSC_BUILD_DOC)
  find_package(Doxygen REQUIRED)
endif()
