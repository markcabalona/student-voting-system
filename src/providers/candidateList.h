#ifndef CANDIDATE_LIST_H
#define CANDIDATE_LIST_H
#include <iostream>
#include "../models/candidate.h"
#define MAX_CANDIDATES 50
#define CANDIDATES_DB_FILEPATH "../db/candidates.csv"

using namespace std;

typedef struct CandidateList
{
    Candidate candidates[MAX_CANDIDATES];
    int last;
    int locate(string studentId);
    int insert(Candidate can);
    void makeNull();
    int isFull();
    int isEmpty();
    void display();
    void menu();
    int retrieve();

} CandidateList;


#endif