#include <iostream>
#include "candidate.h"

using namespace std;

Candidate::Candidate()
{
}

//assigns the values of parameter to the properties of the parent class and the properties of this class
Candidate::Candidate(int ballotId, string name, string studentId, string position, int voteCount) :Student(name,studentId)
{
    _ballotId = ballotId;
    _position = position;
    _voteCount = voteCount;
}

void Candidate::incrementVoteCount()
{
    _voteCount++;//increments _voteCount
}

string Candidate::position()
{
    return _position;//returns the value of _position
}
int Candidate::voteCount()
{
    return _voteCount;//returns the value of _voteCount
}
int Candidate::ballotId(){
    return _ballotId;//returns the value of _ballotId
}