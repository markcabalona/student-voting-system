#include <iostream>
#include "listProvider.h"
#include <future>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <string.h>

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

bool ListProvider::isGuestUser()
{
    return _isGuestUser;
}

void ListProvider::checkFlashDrive()
{
    char *userInfoPath = strdup("e:/myInfo.csv");

    // checks if flashdrive is inserted
    // if a flashdrive is inserted, opens a myinfo.csv file for writing
    //  meaning myinfo.csv will always be created in the inserted flashdrive
    FILE *fd = fopen(userInfoPath, "r+");
    while (!fd)
    {
        fd = fopen(userInfoPath, "r+");
        if (!_checkFlashDriveToken) // if cancel option was chosen
        {
            return;
        }
    }
    char *buff = (char *)malloc(255 * sizeof(char));
    int row = 0;
    while (fgets(buff, 255, fd))
    {
        row++;
    }

    if (row == 0)
    {
        fprintf(fd, "student_id,password,name,voter_id,isRegistered,voted\n");
        Student temp = Student();
        _user = &temp;
        return;
    }
    else if (row == 1)
    {
        Student temp = Student();
        _user = &temp;
        return;
    }
    fclose(fd);

    fd = fopen(userInfoPath, "r");
    // end of checking
    string id, pw, name;
    int voterId, isReg, voted;
    int col = 0;
    char *token = strtok(buff, ",");
    while (token != NULL)
    {
        switch (col)
        {
        case 0: // col 1
            id = token;
            break;
        case 1: // col 2
            pw = token;
            break;
        case 2: // col 3
            name = token;
            break;
        case 3: // col 4
            voterId = atoi(token);
            break;
        case 4: // col 5
            isReg = atoi(token);
            break;
        case 5:
            voted = atoi(token);
            break;
        default:
            break;
        }
        col++;
        token = strtok(NULL, ",");
    }
    Student temp = Student(id, pw, name, voterId, isReg, voted);
    _user = &temp;
    fclose(fd);
    _isGuestUser = false;
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
