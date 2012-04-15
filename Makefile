CXXFLAGS = -Wall -Wextra
LDFLAGS = -lrt

all: sudoku

sudoku: main.o
	g++ -o sudoku main.o ${LDFLAGS}

main.o: main.cpp sudoku.h sudoku.hpp backtrack.h
	g++ -c main.cpp ${CXXFLAGS}

.PHONY: clean
clean:
	rm sudoku main.o

