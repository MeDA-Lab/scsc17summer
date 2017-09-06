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

obj = read_graph.o

INCS = -I include
TARGETS_O	:= $(TARGETS_SRC:.cpp=.o)

.PHONY: all clean

all: MakeObj MakeExe

MakeObj: $(TARGETS_O)

%.o: src/%.cpp
	$(CC) -c $< $(INCS) $(CCFLAGS)

%.o: src/core/%.cpp
	$(CC) -c $< $(INCS) $(CCFLAGS)

MakeExe:sgp_main.out

sgp_main.out: sgp_main.o $(obj)
	$(LOADER) $< -o $@ $(obj) $(CCFLAGS)