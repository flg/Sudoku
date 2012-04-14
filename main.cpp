#include "sudoku.h" 
#include "backtrack.h"

#include <iostream>

void usage()
{
    std::cout << "Usage: sudoku {input_file}\n";
    std::cout << "Example of input file:\n";
    std::cout << ". . . . 5 3 . . 8" << std::endl;
    std::cout << "3 . . 6 . . . . ." << std::endl;
    std::cout << ". 1 . 4 . . 7 . 3" << std::endl;
    std::cout << ". 8 4 7 . . . 9 ." << std::endl;
    std::cout << ". . 7 9 . 2 5 . ." << std::endl;
    std::cout << ". 5 . . . 6 2 1 ." << std::endl;
    std::cout << "8 . 5 . . 1 . 7 ." << std::endl;
    std::cout << ". . . . . 4 . . 2" << std::endl;
    std::cout << "7 . . 3 9 . . . ." << std::endl;
}

int main(int argc, char** argv)
{
    typedef Sudoku<> TSudoku;

    if (argc != 2) {
        usage();
        return -1;
    }

    TSudoku s;
    s.read_from_file(argv[1]);
    
    std::cout << "Problem:\n" << s << std::endl;

    Backtrack<TSudoku> backtrack(std::cout);
    backtrack(s);

    unsigned nb_cand = backtrack.getNbCandidate();
    std::cout << "Explored " << nb_cand << " candidate" << (nb_cand > 1 ? "s\n" : "\n");
    unsigned nb_sol = backtrack.getNbSolution();
    std::cout << "Found " << nb_sol << " solution" << (nb_sol > 1 ? "s\n" : "\n");

    return 0;
}
