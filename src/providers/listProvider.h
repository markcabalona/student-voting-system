#ifndef LIST_PROVIDER_H
#define LIST_PROVIDER_H
#include <iostream>

#include "candidateList.h"
#include "studentList.h"


using namespace std;


class ListProvider
{
private:
    CandidateList _candidateList;
    StudentList _studentList;

public:
    CandidateList candidateList();
    StudentList studentList();
    void retrieve();
    void save();

    ListProvider();
};


#endif