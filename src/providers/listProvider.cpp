#include <iostream>
#include "listProvider.h"
#include <future>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <string.h>
#define FLASHDRIVE_PATH "e:/myInfo.csv"

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
}

ListProvider::~ListProvider(){
    // FILE *fp = fopen("testDestruct.txt","w");
    // fclose(fp);
    _studentList.update(_user->studentId(),*_user);

    if(_studentList.save()){
        cout<<"Database is Updated"<<endl;
        system("pause");
    }
    if(_candidateList.save()){
        cout<<"Candidate DB is Updated"<<endl;
        system("pause");
    }
    _saveUser();
    // call save functions here;
}


bool ListProvider::isGuestUser()
{
    return _isGuestUser;
}

void ListProvider::checkFlashDrive()
{

    // checks if flashdrive is inserted
    // if a flashdrive is inserted, opens a myinfo.csv file for writing
    //  meaning myinfo.csv will always be created in the inserted flashdrive
    FILE *fd = fopen(FLASHDRIVE_PATH, "w");
    while (!fd)
    {
        fd = fopen(FLASHDRIVE_PATH, "w");
        if (!_checkFlashDriveToken) // if cancel option was chosen
        {
            fclose(fd);
            return;
        }
    }
    fclose(fd);
    fd = fopen(FLASHDRIVE_PATH,"r");
    // pag nandito na ibigsabihin may nakainsert na na flashdrive
    char *buff = (char *)malloc(255 * sizeof(char));
    int row = 0;
    while (fgets(buff, 255, fd))
    {
        row++;
    }
    fclose(fd);

    if (row == 0)
    {
        fd = fopen(FLASHDRIVE_PATH,"w");
        fprintf(fd, "student_id,password,name,voter_id,isRegistered,voted\n");
        fclose(fd);
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
    //fclose(fd);

    fd = fopen(FLASHDRIVE_PATH, "r");
    // end of checking
    string id, pw, name;
    int voterId, isReg, voted;
    int col = 0;
    char *token = strtok(buff, ",");//buff = "TUPM-20-0621,BUENAVENTURA,BUENAVENTURA NICOLE,-1,0,0"
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
    _user = new Student(id, pw, name, voterId, isReg, voted);
    fclose(fd);
    _isGuestUser = false;
    return;
}

void ListProvider::_saveUser(){
    FILE *fd = fopen(FLASHDRIVE_PATH,"w");
    fprintf(fd, "student_id,password,name,voter_id,isRegistered,voted\n");
    fprintf(fd,"%s,%s,%s,%d,%d,%d",_user->studentId().c_str(),_user->password().c_str(),_user->name().c_str(),_user->voterId(),_user->registered(),_user->voted());
    fclose(fd);
}

void ListProvider::cancelFlashDriveChecking()
{
    _checkFlashDriveToken = false;
    userReady.wait();
}

Student *ListProvider::user()
{
    return _user;
}

void ListProvider::setUser(Student stud){
    //student_id,password,name,voter_id,isRegistered,voted
    _user = new Student(stud.studentId(),stud.password(),stud.name(),stud.voterId(),stud.registered(),stud.voted());
    _isGuestUser = false;
}

CandidateList* ListProvider::candidateList()
{
    return &_candidateList;
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

