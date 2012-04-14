#ifndef _SUDOKU_H_
#define _SUDOKU_H_

#include <vector>
#include <iostream>
#include <algorithm>

template <typename T = unsigned, unsigned N = 9>
class Sudoku
{
public:
    Sudoku();
    Sudoku(Sudoku const & s);

    void read_from_file(std::string const & filename);
    void write_to_file(std::string const & filename);
    
    // <-- Solve interface: used by Backtrack algo
    bool next();
    bool first();
    bool is_valid();
    bool is_complete();
    // --> Solve interface: used by Backtrack algo
    
    template <typename U, unsigned M>
    friend std::ostream & operator << (std::ostream & os, Sudoku<U, M> const & s);

private:
    Sudoku & operator=(Sudoku const & s);

    typedef T TGridLine[N];
    typedef TGridLine TGrid[N];

    TGrid _Grid;
    unsigned _BlockSize;
    T* _CurrentDigit;
};

template <typename T, int N>
std::ostream & operator << (std::ostream & os, Sudoku<T, N> const & s);

#include "sudoku.hpp"

#endif
