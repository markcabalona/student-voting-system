#include <iostream>
#include "candidate.h"

using namespace std;

Candidate::Candidate()
{
}

Candidate::Candidate(int ballotId, string name, string studentId, string position, int voutCount) :Student(name,studentId)
{
    _ballotId = ballotId;
    _position = position;
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