#ifndef _BACKTRACK_H_
#define _BACKTRACK_H_

#include <stack>
#include <ostream>

//#define TRACE_BACKTRACK

#ifdef TRACE_BACKTRACK
#include <sstream>
#define TRACE(a)\
    {\
        std::ostringstream oss;\
        oss << a;\
        _Output << oss.str() << std::endl;\
    }
#else
#define TRACE(a) 
#endif

template <typename T>
class Backtrack
{
public:
    Backtrack(std::ostream & os);
    void operator()(T & candidate);
    unsigned getNbSolution() {return _NbSolution;}
    unsigned getNbCandidate() {return _NbCandidate;}

private:
    Backtrack(Backtrack<T> const &);
    void operator= (Backtrack<T> const &);

    unsigned _NbSolution;
    unsigned _NbCandidate;
    std::ostream & _Output;
};

template <typename T>
Backtrack<T>::Backtrack(std::ostream & os)
    : _NbSolution(0)
    , _NbCandidate(0)
    , _Output(os)
{
    // nothing
}

template <typename T>
void Backtrack<T>::operator()(T & candidate)
{
    TRACE("new candidate:\n" << candidate);
    ++_NbCandidate;

    if (!candidate.is_valid()) {
        TRACE("not valid\n");
        return;
    }

    if (candidate.is_complete()) {
        // complete and valid => solution
        TRACE("solution");
        ++_NbSolution;
        _Output << candidate << std::endl;
        return;
    }

    // As this algo takes candidate as a reference, it needs to be copied before generating children. 
    T next = candidate;

    // valid and not complete: generate first extension...
    TRACE("generate first");
    next.first();

    do {
        //... test every possible extensions
        operator()(next); // recurse
        TRACE("generate next");
    } while (next.next());

    TRACE("no more possibilities for this extension");
}

#endif
