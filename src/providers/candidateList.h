#ifndef CANDIDATE_LIST_H
#define CANDIDATE_LIST_H
#include <iostream>
#include<vector>
#include "../models/candidate.h"
#define MAX_CANDIDATES 50
#define CANDIDATES_DB_FILEPATH "../db/candidates.csv"

using namespace std;

typedef struct CandidateList
{
    private:
        int _positionCount = 0;//number of positions
        vector<string>_positionNames{};
        int _addNewPosition(string posName);
    public:
    int positionCount();
    vector<string> positionNames();
    
    Candidate candidates[MAX_CANDIDATES];
    int last;
    int locate(string *studentId,int* ballotId);
    int insert(Candidate can);
    void makeNull();
    int isFull();
    int isEmpty();
    void display();
    void menu();
    int retrieve();
    int save();

} CandidateList;


#endif