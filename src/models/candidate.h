#ifndef CANDIDATE_H
#define CANDIDATE_H
#include<iostream>
#include "student.h"
using namespace std;

//declarations
class Candidate : public Student//a class that inherits from the Student class
//this means that all properties and methods of student class is inherited by this class
{
private://these properties are only visible in this class
    string _position;//it will hold the position of the candidate
    int _voteCount;//this will hold the votecount of the candidate
    int _ballotId;//this will hold the ballot id(ballot number) of the candidate
public:
    void incrementVoteCount();//this will increment the _voteCOunt property

    //getter methods,
    string position();//returns the value of _position
    int voteCount();//returns the value of _voteCount
    int ballotId();//returns the value of _ballotId

    //these are class constructors (special methods that will be called every time an instance of this class is created)
    //this constructor can accept parameters, when u create a Candidate object, you can initialize its properties
    Candidate(int ballotId ,string name,string studentId,string position,int voteCount);
    Candidate();//this is a default constructor, accepts no parameter
};


#endif