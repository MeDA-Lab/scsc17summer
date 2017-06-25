  # Set complier flags
set(CMAKE_CXX_FLAGS "-std=c++11 -O2 -g -Wall -Wextra -pedantic")

if(SCSC_BUILD_BIN)
  set(findtype REQUIRED)
else()
  set(findtype "")
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
  find_package(MKL ${findtype})
  if(MKL_FOUND)
    list(APPEND INCS "${MKL_INCLUDES}")
    list(APPEND LIBS "${MKL_LIBRARIES}")
    set(COMFLGS "${COMFLGS} ${MKL_FLAGS}")
  endif()
endif()

# OpenMP
if(SCSC_USE_OMP)
  set(OpenMP ${SCSC_USE_OMP})

  find_package(OpenMP ${findtype})
  if(OpenMP_FOUND)
    set(COMFLGS "${COMFLGS} ${OpenMP_CXX_FLAGS}")
    set(LNKFLGS "${LNKFLGS} ${OpenMP_CXX_FLAGS}")
  endif()

  find_package(OpenMPLib ${findtype})
  if(OpenMPLib_FOUND)
    list(APPEND LIBS "${OpenMP_LIBRARIES}")
  endif()

  unset(OpenMP)
elseif(SCSC_USE_GPU)
  find_package(OpenMP ${findtype})
  if(OpenMP_FOUND)
    set(COMFLGS "${COMFLGS} ${OpenMP_CXX_FLAGS}")
    set(LNKFLGS "${LNKFLGS} ${OpenMP_CXX_FLAGS}")
  endif()
endif()

# CUDA & MAGMA
if(SCSC_USE_GPU)
  find_package(CUDA ${findtype})
  find_package(MAGMA ${findtype})
  if(MAGMA_FOUND)
    list(APPEND INCS "${MAGMA_INCLUDES}" "${CUDA_INCLUDE_DIRS}")
    # list(APPEND LIBS "${MAGMA_LIBRARY}" "${MAGMA_SPARSE_LIBRARY}" "${CUDA_CUDART_LIBRARY}" "${CUDA_cublas_LIBRARY}" "${CUDA_cusparse_LIBRARY}")
    list(APPEND LIBS "-lmagma_sparse -lmagma -lcusparse -lcublas -lcudart")
  endif()
endif()

# DOxygen
if(SCSC_BUILD_DOC)
  find_package(Doxygen REQUIRED)
endif()
