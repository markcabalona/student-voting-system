#ifndef CANDIDATE_H
#define CANDIDATE_H
#include<iostream>
#include "student.h"
using namespace std;
class Candidate : public Student
{
private:
    string _position;
    int _voteCount = 0;
public:
    void incrementVoteCount();

    string position();
    int voteCount();
    void setVoteCount(int vcount);

    Candidate(string position ,string name,string studentId,string pwd);
    Candidate();
};


#endif