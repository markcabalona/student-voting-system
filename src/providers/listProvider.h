#ifndef LIST_PROVIDER_H
#define LIST_PROVIDER_H
#include <iostream>

#include "candidateList.h"
#include "studentList.h"
#include <future>


using namespace std;


class ListProvider
{
private:
    Student* _user = nullptr;//this will hold the content of user's flashdrive
    CandidateList _candidateList;
    StudentList _studentList;

public:
    Student* user();
    CandidateList candidateList();//getter, returns _candidateList
    StudentList studentList();//getter, returns _studentList
    int retrieve();
    void save();
    Student checkFlashDrive();


    ListProvider();
};

extern ListProvider provider;


#endif