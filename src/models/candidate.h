#ifndef CANDIDATE_H
#define CANDIDATE_H
#include<iostream>
#include "student.h"
using namespace std;
class Candidate : public Student
{
private:
    string _position;
    int _voteCount;
    int _ballotId;
public:
    void incrementVoteCount();

    string position();
    int voteCount();
    int ballotId();

    Candidate(int ballotId ,string name,string studentId,string position,int voteCount);
    Candidate();
};


#endif