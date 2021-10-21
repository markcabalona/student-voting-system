#ifndef CANDIDATE_LIST_H
#define CANDIDATE_LIST_H
#include<iostream>
#include "../models/candidate.h"

#define MAX_CANDIDATE 20
using namespace std;

typedef struct CandidateList
{
    Candidate candidates[MAX_CANDIDATE];
    int last;
}CandidateList;

extern CandidateList cList;
void initializeCandidateList();

void retrieve();
void save();

//list operations
int locate(string studentId); 
void makeNull();
void display();
int isFull();
int isEmpty();
int update(string studentId);

void menu();

//utilities
char *get_string(); //returns a pointer to a string
int get_int();      //returns an integer input from user, this filters nonnumeric characters
float get_float();  //same as get_int




#endif