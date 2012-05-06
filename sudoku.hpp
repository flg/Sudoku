#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <math.h> //sqrt
#include <string.h> //memcpy

template <typename T, unsigned N>
Sudoku<T, N>::Sudoku()
    : _CurrentDigit((T*)_Grid)
{
    float const f = sqrt(N);
    if (f*f != N) throw std::runtime_error("N must be a perfect square");
    _BlockSize = static_cast<unsigned>(f);
}

template <typename T, unsigned N>
Sudoku<T,N>::Sudoku(Sudoku const & s)
{
    _BlockSize = s._BlockSize;

    memcpy(_Grid, s._Grid, N*N*sizeof(T));

    _CurrentDigit = (T*)_Grid + (s._CurrentDigit - (T*)s._Grid);
}

template <typename T, unsigned N>
void Sudoku<T, N>::read_from_file(std::string const & filename)
{
    std::ifstream file(filename.c_str());
    if (!file) {
        throw std::runtime_error("read_from_file: cannot open file " + filename);
    }

    std::string line;
    std::istringstream iss;
    unsigned nb_lines_read = 0;
    while (getline(file, line)) {
        if (++nb_lines_read > N) {
            std::ostringstream oss;
            oss << "read_from_file: too many lines: ";
            oss << nb_lines_read;
            throw std::runtime_error(oss.str());
        }

        iss.clear();
        iss.str(line);

        unsigned nb_digit = 0;
        char digit;
        while (iss >> digit) {
            if (++nb_digit > N) {
                std::ostringstream oss;
                oss << "read_from_file: too many digits (";
                oss << nb_digit;
                oss << ") on line #";
                oss << nb_lines_read;
                throw std::runtime_error(oss.str());
            }

            if (isdigit(digit)) {
                digit -= '0';
            } else {
                digit = 0;
            }
            _Grid[nb_lines_read - 1][nb_digit - 1] = digit;
        }

        if (nb_digit < N) {
            std::ostringstream oss;
            oss << "read_from_file: too few digits (";
            oss << nb_digit;
            oss << ") on line #";
            oss << nb_lines_read;
            throw std::runtime_error(oss.str());
        }
    }

    if (nb_lines_read < N) {
        std::ostringstream oss;
        oss << "read_from_file: too few lines: ";
        oss << nb_lines_read;
        throw std::runtime_error(oss.str());
    }

    // Look for the first missing digit
    for (unsigned L = 0; L < N; ++L) {
        for (unsigned C = 0; C < N; ++C) {
            if (_Grid[L][C] == 0) {
                _CurrentDigit = ((T*)_Grid) + (L*N + C);
                goto first_missing_digit_found;
            }
        }
    }

first_missing_digit_found:
    (void)_CurrentDigit;
}

template <typename T, unsigned N>
void Sudoku<T, N>::write_to_file(std::string const & filename)
{
    std::ofstream file(filename.c_str());
    if (file) {
        file << (*this);
    } else {
        std::runtime_error("write_to_file:: cannot open file " + filename);
    }
}

template <typename T, unsigned N>
std::ostream & operator << (std::ostream & os, Sudoku<T, N> const & s)
{
    for (unsigned L = 0; L < N; ++L) {
        for (unsigned C = 0; C < N; ++C) {
            os << s._Grid[L][C] << " ";
        }
        os << std::endl;
    }
    return os;
}


template <typename T, unsigned N>
bool Sudoku<T,N>::is_valid()
{
    for (unsigned L = 0; L < N; ++L) {
    for (unsigned C = 0; C < N; ++C) {
        T & d = _Grid[L][C];
        if (d == 0) {
            continue;
        }

        // Line check
        for (unsigned c = 0; c < N; ++c) {
            if (c != C && _Grid[L][c] == d) {
                return false;
            }
        }
        // Column check
        for (unsigned l = 0; l < N; ++l) {
            if (l != L && _Grid[l][C] == d) {
                return false;
            }
        }
        // Block check
        unsigned const l_low = (L / _BlockSize) * _BlockSize;
        unsigned const c_low = (C / _BlockSize) * _BlockSize;
        for (unsigned l = l_low; l < l_low + _BlockSize; ++l) {
        for (unsigned c = c_low; c < c_low + _BlockSize; ++c) {
            if (c != C && l != L && _Grid[l][c] == d) {
                return false;
            }
        }}
    }} // double for loop
    return true;
}

template <typename T, unsigned N>
bool Sudoku<T,N>::is_complete()
{
    for (unsigned L = 0; L < N; ++L) {
    for (unsigned C = 0; C < N; ++C) {
        if (_Grid[L][C] == 0) {
            return false;
        }
    }}
    return true;
}

template <typename T, unsigned N>
bool Sudoku<T,N>::next()
{
    if (*_CurrentDigit < N) {
        ++(*_CurrentDigit);
        return true;
    }
    return false;
}

template <typename T, unsigned N>
bool Sudoku<T,N>::first()
{
    while (_CurrentDigit - (T*)_Grid < N*N) {
        if (*_CurrentDigit == 0) {
            break;
        }
        ++_CurrentDigit;
    }
    if (_CurrentDigit - (T*)_Grid == N*N) {
        return false;
    }
    *_CurrentDigit = 1;
    return true;
}

