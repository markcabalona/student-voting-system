#include <iostream>
#include "listProvider.h"
#include <future>
#include <unistd.h>

using namespace std;

ListProvider::ListProvider()
{
    system("cls");
    _candidateList.makeNull();
    _studentList.makeNull();
    if (retrieve() < 0)
    {
        cout << "Exiting Program..." << endl;
        system("pause");
        system("cls");
        exit(1);
    }
    cout << "\nPlease Insert a Flashdrive to continue..." << endl;
    cout << "***(Hit Ctrl + C to exit.)***" << endl;
}

void ListProvider::checkFlashDrive()
{
    // todo

    while (true)
    {
        if (!_checkFlashDriveToken) // if cancel option was chosen
        {
            return;
        }

        // mimicking flashdrive insertion
        // sleep(10);
        // break;
    }

    Student temp;
    _user = &temp;
    return;
}

// void ListProvider::initUser()
// {
//     async(launch::async, &ListProvider::checkFlashDrive, this);
// }

void ListProvider::cancelFlashDriveChecking()
{
    _checkFlashDriveToken = false;
    userReady.wait();
}

Student *ListProvider::user()
{
    return _user;
}

CandidateList ListProvider::candidateList()
{
    return _candidateList;
}
StudentList ListProvider::studentList()
{
    return _studentList;
}

int ListProvider::retrieve()
{
    // list's retrieve functions returns -1 if database reading has error
    // returns 1 if success
    // returns 0 if list is full

    // call the cadidate and student list's retrieve functions asynchronously to speed up retrieving data
    future<int> _sListResponse = async(&StudentList::retrieve, &_studentList);
    // TODO implement _candidateList.retrieve()
    future<int> _cListResponse = async(&CandidateList::retrieve, &_candidateList);

    if (_sListResponse.get() < 0 || _cListResponse.get() < 0)
    {
        system("cls");
        cout << "An error occured while reading the database." << endl;
        cout << "Make sure your database is initialized.";
        return -1;
    }
    else if (_studentList.isEmpty())
    {
        system("cls");
        cout << "Student Database is empty." << endl;
        return -1;
    }
    // TODO _candidateList.retrieve();

    return 0;
}
void ListProvider::save()
{
    // TODO
}
