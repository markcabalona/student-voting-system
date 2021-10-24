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
    Student *_user = nullptr; // this will hold the content of user's flashdrive
    bool _checkFlashDriveToken = true;
    CandidateList _candidateList;
    StudentList _studentList;
    bool _isGuestUser = true;

public:
    void checkFlashDrive();
    void cancelFlashDriveChecking();

    Student *user();
    CandidateList candidateList(); // getter, returns _candidateList
    StudentList studentList();     // getter, returns _studentList
    int retrieve();
    void save();
    bool isGuestUser();
    void setUser(Student stud);

    ListProvider();
};

extern ListProvider provider;
extern future<void> userReady;

#endif