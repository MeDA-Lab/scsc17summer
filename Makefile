CXX      ?= g++
CXXFLAGS  = -O2 -std=c++11 -Wall -Wextra -pedantic

RM = rm -rf

TGT  = main
HDRS = src/harmonic.hpp src/utility.hpp
INCS = ./src
OBJS = utility.o \
			 read_object.o \
			 verify_boundary.o \
			 reorder_vertex.o \
			 construct_laplacian.o \
			 map_boundary.o \
			 solve_harmonic.o \

.PHONY: all

all: main

%.o: src/%.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< -I$(INCS)

%.o: src/core/%.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< -I$(INCS)

%.o: src/mkl/%.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< -I$(INCS)

%.o: src/magma/%.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< -I$(INCS)

main: main.o $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

run: $(TGT)
	./$(TGT)

clean:
	$(RM) $(TGT) *.o
