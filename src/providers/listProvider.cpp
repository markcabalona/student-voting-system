#include <iostream>
#include "listProvider.h"
#include <unistd.h>
#include <string.h>
//#define FLASHDRIVE_PATH "e:/myInfo.csv"
#define FLASHDRIVE_PATH "../db/testFlashDrive.csv"

using namespace std;

//this is called when a ListProvider instance is called
ListProvider::ListProvider()//a constructor
{
    system("cls");//clears the screen
    _candidateList.makeNull();//set the 'last' property of _candidateList to -1
    _studentList.makeNull();//set the 'last' property of _studentList to -1
    //error handling
    if (retrieve() < 0)//retrieve returns -1 if reading database has error
    {
        //displays exit message
        cout << "Exiting Program..." << endl;
        system("pause");
        system("cls");
        exit(1);
    }
}

//this is called when an instance of this class is destroyed
ListProvider::~ListProvider()//class destructor
{
    //is guestUser holds a boolean 
    if (!_isGuestUser)
    {
        _studentList.update(_user->studentId(), *_user);//update the studentList
        _saveUser();//save the _user info to the flashdrive
    }

    if (_studentList.save())//saves the list to the database
    {
        cout << "Database is Updated" << endl;
    }
    if (_candidateList.save())//saves the list to the database
    {
        cout << "Candidate DB is Updated" << endl;
    }
    system("pause");
}

bool ListProvider::isGuestUser()//getter, returns the value of _isGUestUser property
{
    return _isGuestUser;
}

void ListProvider::checkFlashDrive()//checks if a flashdrive is inserted
{

    // checks if flashdrive is inserted
    // if a flashdrive is inserted, opens a myinfo.csv file for append and read
    //  meaning myinfo.csv will always be created in the inserted flashdrive (if there is no file in it)
    FILE *fd = fopen(FLASHDRIVE_PATH, "a+");
    while (!fd)//while no flashdrive is inserted
    {
        fd = fopen(FLASHDRIVE_PATH, "a+");//check again
        // if (!_checkFlashDriveToken) // if cancel option was chosen
        // {
        //     fclose(fd);
        //     return;
        // }
    }
    // pag nandito na ibigsabihin may nakainsert na na flashdrive

    
    char buff[255];
    int row = 0;
    //this counts the number of lines in the file inside fd
    while (fgets(buff, 255, fd))//reads the file line by line
    {
        row++;
    }

    if (row == 0)//this means the file has no data in it, meaning it is opened and created for the first time
    {
        fprintf(fd, "student_id,password,name,voter_id,isRegistered,voted\n");//write a header in the file
        fclose(fd);//close the file
        Student temp = Student();
        _user = &temp;
        return;
    }
    else if (row == 1)//if the file in fd already has a header, but no student record in it
    {
        Student temp = Student();
        _user = &temp;
        fclose(fd);//close the file
        return;
    }
    // fclose(fd);

    //the codes below will only be executed when there is a student record in the fd
    //the current value of buff now is the student record

    //declaration of variables
    string id, pw, name;
    int voterId, isReg, voted;
    int col = 0;
 
    char *token = strtok(buff, ","); //tokenize the buff with ',' as delimeter
    //strtok returns a NULL if it reaches the end of the string
    while (token != NULL)
    {
        //the file has this kind of format
        //student_id,password,name,voter_id,isRegistered,voted
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
    _user = new Student(id, pw, name, voterId, isReg, voted);//set _assign the records in the file to the _user property
    fclose(fd);//close the file
    _isGuestUser = false;//set _isGuesUser to false
    return;
}

void ListProvider::_saveUser()
{
    //overwrite the file in the flashdrive
    FILE *fd = fopen(FLASHDRIVE_PATH, "w");
    fprintf(fd, "student_id,password,name,voter_id,isRegistered,voted\n");
    fprintf(fd, "%s,%s,%s,%d,%d,%d", _user->studentId().c_str(), _user->password().c_str(), _user->name().c_str(), _user->voterId(), _user->registered(), _user->voted());
    fclose(fd);
}

// void ListProvider::cancelFlashDriveChecking()
// {
//     _checkFlashDriveToken = false;
    
//     return;
// }

Student *ListProvider::user()
{
    return _user;
}

bool ListProvider::setUser(string id)
{
    studentNode*stud;
    if((stud = _studentList.locate(&id,nullptr)) == nullptr){
        return false;
    }
    _user = new Student;
    _user = &stud->student;//new Student(stud->student.studentId(), stud->student.password(), stud->student.name(), stud->student.voterId(), stud->student.registered(), stud->student.voted());
    
    _isGuestUser = false;
}

CandidateList *ListProvider::candidateList()
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

    // // call the cadidate and student list's retrieve functions asynchronously to speed up retrieving data
    // future<int> _sListResponse = async(&StudentList::retrieve, &_studentList);
    // // TODO implement _candidateList.retrieve()
    // future<int> _cListResponse = async(&CandidateList::retrieve, &_candidateList);

    if (_studentList.retrieve() < 0 || _candidateList.retrieve() < 0)//retrieve funtions returns -1 for error and 0 for success
    {
        //reading the database has failed
        system("cls");//clear screen
        //display error messages
        cout << "An error occured while reading the database." << endl;
        cout << "Make sure your database is initialized.";
        return -1;
    }
    else if (_studentList.isEmpty())
    {
        //student database is empty, no students is in the csv file
        system("cls");
        cout << "Student Database is empty." << endl;
        return -1;
    }
    

    return 0;
}
