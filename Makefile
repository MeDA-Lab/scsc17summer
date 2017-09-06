#################################################
##   Makefile for spectral graph partitioning  ##
##   Create by Wei-Chien Liao                  ##
##   Date  : 2017/09/04                        ##
##   Update:                                   ##
#################################################

#=======================
# Compiler settings
#=======================
CC          = g++
NVCC        = nvcc
LOADER      = $(CC)

ARCH        = ar
ARCHFLAGS   = cr
RANLIB      = ranlib

#=======================
# Flag settings.
#=======================
CCFLAGS		= -O3 -m64 -std=c++11
NVCCFLAGS	= -m64 -std=c++11

#======================
# Library PATH settings
#======================
#MKL
MKLROOT = /opt/intel/mkl
MKLINCS = -I${MKLROOT}/include
MKLLNKS = -L${MKLROOT}/lib/intel64 -lmkl_intel_lp64 -lmkl_sequential -lmkl_core -lpthread -lm -ldl

#CUDA
CUDA_PATH = /usr/local/cuda-8.0
CUDA_INC  = -I$(CUDA_PATH)/include
CUDA_LIB_PATH   = $(CUDA_PATH)/lib64
CUDA_LD_FLAGS   = -lcudart -lcublas -lcufft -lcusolver -lcusparse -lgomp -lm -ldl
CUDA_LD_LIB	    = -L$(CUDA_LIB_PATH) $(CUDA_LD_FLAGS)

#==============================================================

obj = read_graph.o graph_adjacency.o

INCS = -I include
TARGETS_O	:= $(TARGETS_SRC:.cpp=.o)

.PHONY: all clean

all: MakeObj MakeExe

MakeObj: $(TARGETS_O)

%.o: src/%.cpp
	$(CC) -c $< $(INCS) $(CCFLAGS) $(MKLINCS)

%.o: src/core/%.cpp
	$(CC) -c $< $(INCS) $(CCFLAGS) $(MKLINCS) $(CUDA_INC)

MakeExe:sgp_main.out

sgp_main.out: sgp_main.o $(obj)
	$(LOADER) $< -o $@ $(obj) $(CCFLAGS) $(MKLLNKS) $(CUDA_LD_FLAGS)

clean:
	-rm *.o -f
	-rm *.out -f