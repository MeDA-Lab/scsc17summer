CXX      ?= g++
CXXFLAGS  = -O2 -std=c++11 -Wall -Wextra -pedantic

RM = rm -rf

TGT  = main
HDRS = harmonic.hpp utility.hpp

.PHONY: all

all: main

%.o: %.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) $< -c

main: main.o utility.o
	$(CXX) $(CXXFLAGS) $^ -o $@

run: $(TGT)
	./$(TGT)

clean:
	$(RM) $(TGT)
