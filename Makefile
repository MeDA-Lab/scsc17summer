CXX      ?= g++
CXXFLAGS  = -O2 -std=c++11 -fopenmp -Wall -Wextra -pedantic

RM       = rm -rf
RANLIB   = ranlib
AR       = ar
ARFLAGS  = rv
ARCHIVE  = $(AR) $(ARFLAGS)

DOX      = doxygen

MKLROOT ?=
MKLINC   = -isystem $(MKLROOT)/include
MKLLIB   = -L$(MKLROOT)/lib/intel64
# MKLLNK   = -m64 -Wl,--no-as-needed -lmkl_intel_lp64 -lmkl_sequential -lmkl_core -lpthread -lm -ldl
MKLLNK   = -m64 -Wl,--no-as-needed -lmkl_intel_lp64 -lmkl_gnu_thread -lmkl_core -lgomp -lpthread -lm -ldl

MAGMAROOT ?= /opt/magma/2.2/
MAGMAINC   = -isystem $(MAGMAROOT)/include
MAGMALIB   = -L$(MAGMAROOT)/lib
MAGMALNK   = -lmagma -lcusparse -lcublas -lcudart

TGT        = main
MKLTGT     = main_mkl
MAGMATGT   = main_magma
MKLSPTGT   = main_mkl_sp
MAGMASPTGT = main_magma_sp
TGTS       = $(TGT) $(MKLTGT) $(MAGMATGT) # $(MKLSPTGT) $(MAGMASPTGT)

HDRS       = \
	src/harmonic.hpp \
	src/timer.hpp

INC =\
	-I src \
	-I ext

EXTOBJ = \

OBJ = \
	read_args.o \
	read_object.o \
	verify_boundary_sparse.o \
	reorder_vertex.o \
	construct_laplacian.o \
	map_boundary.o \
	write_object.o \
	solve_harmonic.o \
	$(EXTOBJ)

MKLOBJ = \
	read_args.o \
	read_object.o \
	verify_boundary_sparse.o \
	reorder_vertex.o \
	construct_laplacian.o \
	map_boundary.o \
	write_object.o \
	solve_harmonic_mkl.o \
	$(EXTOBJ)

MAGMAOBJ = \
	read_args.o \
	read_object.o \
	verify_boundary_sparse.o \
	reorder_vertex.o \
	construct_laplacian.o \
	map_boundary.o \
	write_object.o \
	solve_harmonic_magma.o \
	$(EXTOBJ)

MKLSPOBJ = \
	read_args.o \
	read_object.o \
	verify_boundary_sparse.o \
	reorder_vertex.o \
	construct_laplacian_sparse.o \
	map_boundary.o \
	write_object.o \
	solve_harmonic_mkl.o \
	$(EXTOBJ)

MAGMASPOBJ = \
	read_args.o \
	read_object.o \
	verify_boundary_sparse.o \
	reorder_vertex.o \
	construct_laplacian_sparse.o \
	map_boundary.o \
	write_object.o \
	solve_harmonic_magma.o \
	$(EXTOBJ)

.PHONY: all run run_mkl run_magma doc clean

all: $(TGTS)

%.o: src/%.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< $(INC)

%.o: src/core/%.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< $(INC)

%.o: src/mkl/%.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< $(INC) $(MKLINC)

%.o: src/magma/%.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< $(INC) $(MKLINC) $(MAGMAINC)

main: main.o $(OBJ)
	$(CXX) $(CXXFLAGS) $< $(OBJ) -o $@

main_mkl: main.o $(MKLOBJ)
	$(CXX) $(CXXFLAGS) $< $(MKLOBJ) -o $@ $(MKLLIB) $(MKLLNK)

main_magma: main.o $(MAGMAOBJ)
	$(CXX) $(CXXFLAGS) $< $(MAGMAOBJ) -o $@ $(MKLLIB) $(MAGMALIB) $(MKLLNK) $(MAGMALNK)

main_mkl_sp: main_sparse.o $(MKLSPOBJ)
	$(CXX) $(CXXFLAGS) $< $(MKLSPOBJ) -o $@ $(MKLLIB) $(MKLLNK)

main_magma_sp: main_sparse.o $(MAGMASPOBJ)
	$(CXX) $(CXXFLAGS) $< $(MAGMASPOBJ) -o $@ $(MKLLIB) $(MAGMALIB) $(MKLLNK) $(MAGMALNK)

run: $(TGT)
	./$(TGT)

run_mkl: $(MKLTGT)
	./$(MKLTGT)

run_magma: $(MAGMATGT)
	./$(MAGMATGT)

run_mkl_sp: $(MKLSPTGT)
	./$(MKLSPTGT)

run_magma_sp: $(MAGMASPTGT)
	./$(MAGMASPTGT)

doc:
	$(DOX) doxygen/Doxyfile

clean:
	$(RM) $(TGTS) *.o *.a docs
