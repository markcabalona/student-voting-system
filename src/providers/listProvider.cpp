#include <iostream>
#include "listProvider.h"
#include <future>
#include<unistd.h>

using namespace std;

ListProvider::ListProvider()
{
    system("cls");
    _candidateList.makeNull();
    _studentList.makeNull();
    if (retrieve() < 0)
    {
        system("pause");
        system("cls");
        exit(1);
    }
    cout<<"\nPlease Insert a Flashdrive to continue..."<<endl;
    cout<<"***(Hit Ctrl + C to exit.)***"<<endl;
    
    //di pa sure tong sa asynchronous calls, try lang hahaha
    // mali ata to e hahaha
    future<Student> temp = async(&ListProvider::checkFlashDrive,this);
    Student temp1 = temp.get();
    _user = &temp1;
    
}

Student ListProvider::checkFlashDrive(){
    //todo
    //wala pa ito tinetesting ko lang yung kakalabasan hahaha
    sleep(5);
    return Student();
}


Student* ListProvider::user(){
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
    if (_studentList.retrieve() < 0)
    {
        cout << "An error occured while reading the database." << endl;
        cout << "Make sure your database is initialized.";
        return -1;
    }
    else if (_studentList.isEmpty())
    {
        cout << "Database is empty." << endl;
        return -1;
    }
    // TODO _candidateList.retrieve();

    return 0;
}
void ListProvider::save()
{
    // TODO
}
