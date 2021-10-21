#include <iostream>
#include "candidate.h"

using namespace std;

Candidate::Candidate() : Student()
{
}

Candidate::Candidate(string position, string name, string studentId, string pwd) : Student(name, studentId, pwd)
{
    _position = position;
}

void Candidate::setVoteCount(int vcount)
{
    _voteCount = vcount;
}

void Candidate::incrementVoteCount()
{
    _voteCount++;
}

string Candidate::position()
{
    return _position;
}
int Candidate::voteCount()
{
    return _voteCount;
}