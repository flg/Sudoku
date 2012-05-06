#include "sudoku.h" 
#include "backtrack.h"

#include <iostream>
#include <time.h>

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

struct timespec timespec_subtract (struct  timespec  time1, struct  timespec  time2)
{
    struct timespec result ;

    if ((time1.tv_sec < time2.tv_sec) ||
            ((time1.tv_sec == time2.tv_sec) &&
             (time1.tv_nsec <= time2.tv_nsec))) {		/* TIME1 <= TIME2? */
        result.tv_sec = result.tv_nsec = 0 ;
    } else {						/* TIME1 > TIME2 */
        result.tv_sec = time1.tv_sec - time2.tv_sec ;
        if (time1.tv_nsec < time2.tv_nsec) {
            result.tv_nsec = time1.tv_nsec + 1000000000L - time2.tv_nsec ;
            --result.tv_sec ;				/* Borrow a second. */
        } else {
            result.tv_nsec = time1.tv_nsec - time2.tv_nsec ;
        }
    }

    return (result) ;
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

    struct timespec ts0, ts1;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts0);
    backtrack(s);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts1);

    // Print some stats
    struct timespec result = timespec_subtract(ts1, ts0);
    unsigned nb_cand = backtrack.getNbCandidate();
    std::cout << "Explored " << nb_cand << (nb_cand > 1 ? " candidates" : " candidate");
    std::cout << " in " << result.tv_sec << "," << result.tv_nsec << "s.\n";
    unsigned nb_sol = backtrack.getNbSolution();
    std::cout << "Found " << nb_sol << " solution" << (nb_sol > 1 ? "s\n" : "\n");

    return 0;
}
