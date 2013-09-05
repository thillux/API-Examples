CXX:=g++
CXXFLAGS:=-O3 -march=native -lclang -g -Wall -Wextra

all: complete.cc
	$(CXX) $(CXXFLAGS) -o complete complete.cc

clean:
	rm -f complete

run: all
	./complete
