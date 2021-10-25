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
    void _saveUser();//save user's info to user's fd

public:
    void checkFlashDrive();
    void cancelFlashDriveChecking();

    Student *user();
    CandidateList* candidateList(); // getter, returns _candidateList
    StudentList studentList();     // getter, returns _studentList
    int retrieve();
    bool isGuestUser();
    void setUser(Student stud);

    ListProvider();// constructor this will retrieve data from database and populate the lists
    ~ListProvider(); // destructor(this will save everything in our list provider to the database and the flashdrive)
};

extern ListProvider provider;
extern future<void> userReady;

#endif