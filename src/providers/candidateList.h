#ifndef CANDIDATE_LIST_H
#define CANDIDATE_LIST_H
#include <iostream>
#include<vector>
#include "../models/candidate.h"
#define MAX_CANDIDATES 50
#define CANDIDATES_DB_FILEPATH "../db/candidates.csv"

using namespace std;

typedef struct candidateNode{
    Candidate candidate;
    candidateNode* next;
}candidateList;



typedef struct CandidateList
{
    private:
        int _positionCount = 0;//number of positions
        //this is just an array of strings that may varyy in size
        vector<string>_positionNames{};//list of positions
        int _addNewPosition(string posName);//append 
    public:
    int positionCount();//getter for _positionCount
    vector<string> positionNames();//getter for _positionNames
    
    //Candidate candidates[MAX_CANDIDATES];// declare an array of Candidates with size of MAX_CANDIDATES
    candidateList *candidates;
    int length;//this is just the candidates.length
    //returns the index of the candidate if found, returns -1 otherwise
    candidateNode* locate(string *studentId,int* ballotId);//one parameter must be nullptr
    int insert(Candidate can);
    void makeNull();//sets the last property to -1
    bool isEmpty();//returns true(1) if list is empty returns 0 otherwise
    int retrieve();//populate the candidates(read from a csv file)
    int save();//saves the content of candidates back to the csv file

} CandidateList;


#endif