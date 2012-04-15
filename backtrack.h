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

    void analyze_candidate();

    unsigned _NbSolution;
    unsigned _NbCandidate;
    std::ostream & _Output;

    std::stack<T> _Candidates;
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
    candidate.first();
    _Candidates.push(candidate);
    while (!_Candidates.empty()) {
        analyze_candidate();
    }
}

template <typename T>
void Backtrack<T>::analyze_candidate()
{
    T & candidate = _Candidates.top();
    ++_NbCandidate;
    TRACE("new candidate:\n" << candidate);

    if (candidate.is_valid()) {
        if (candidate.is_complete()) {
            TRACE("solution");
            ++_NbSolution;
            _Output << candidate << std::endl;
            do {
                TRACE("generate next");
                if (!_Candidates.top().next()) {
                    TRACE("no more possibilities for this extension");
                    _Candidates.pop();
                } else {
                    break;
                }
            } while (!_Candidates.empty());
        } else {
            TRACE("generate first");
            _Candidates.push(candidate);
            _Candidates.top().first();
        }
    } else {
        TRACE("not valid");
        do {
            TRACE("generate next");
            if (!_Candidates.top().next()) {
                TRACE("no more possibilities for this extension");
                _Candidates.pop();
            } else {
                break;
            }
        } while (!_Candidates.empty());
    }
}

#endif
