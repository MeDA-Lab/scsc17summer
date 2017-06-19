CXX      ?= g++
CXXFLAGS  = -O2 -std=c++11 -fopenmp -Wall -Wextra -pedantic

RM       = rm -rf
RANLIB   = ranlib
AR       = ar
ARFLAGS  = rv
ARCHIVE  = $(AR) $(ARFLAGS)

DOX = doxygen

MKLROOT ?=
MKLINC   = $(MKLROOT)/include
MKLLIB   = $(MKLROOT)/lib/intel64
MKLLNK   = -m64 -Wl,--no-as-needed -lmkl_rt -lpthread -lm -ldl

MAGMAROOT ?= /opt/magma/2.2/
MAGMAINC   = $(MAGMAROOT)/include
MAGMALIB   = $(MAGMAROOT)/lib
MAGMALNK   = -lmagma -lcusparse -lcublas -lcudart 

TGT      = main
MKLTGT   = main_mkl
MAGMATGT = main_magma
TGTS     = $(TGT) $(MKLTGT) $(MAGMATGT)
HDRS     = src/harmonic.hpp

INC = ./src
LIB = .
LNK = -lcore

OBJ = \
	read_args.o \
	read_object.o \
	verify_boundary.o \
	reorder_vertex.o \
	construct_laplacian.o \
	map_boundary.o \
	solve_harmonic.o \

MKL_OBJ = \
	solve_harmonic_mkl.o \

MAGMA_OBJ = \
	solve_harmonic_magma.o \

.PHONY: all run doc clean

all: main

%.o: src/%.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< -I$(INC)

%.o: src/core/%.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< -I$(INC)

%.o: src/mkl/%.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< -I$(INC) -I$(MKLINC)

%.o: src/magma/%.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< -I$(INC) -I$(MKLINC) -I$(MAGMAINC)

libcore.a: $(OBJ)
	$(ARCHIVE) $@ $(OBJ)
	-$(RANLIB) $@

main: main.o | libcore.a
	$(CXX) $(CXXFLAGS) $^ -o $@ -L$(LIB) $(LNK)

main_mkl: main.o $(MKL_OBJ) | libcore.a
	$(CXX) $(CXXFLAGS) $^ -o $@ -L$(LIB) $(LNK) -L$(MKLLIB) $(MKLLNK)

main_magma: main.o $(MAGMA_OBJ) | libcore.a
	$(CXX) $(CXXFLAGS) $^ -o $@ -L$(LIB) $(LNK) -L$(MKLLIB) -L$(MAGMALIB) $(MKLLNK) $(MAGMALNK)

run: $(TGT)
	./$(TGT) -f square.txt

run_mkl: $(MKLTGT)
	./$(MKLTGT) -f square.txt

run_magma: $(MAGMATGT)
	./$(MAGMATGT) -f square.txt

doc:
	$(DOX) doxygen/Doxyfile

clean:
	$(RM) $(TGTS) *.o *.a docs
