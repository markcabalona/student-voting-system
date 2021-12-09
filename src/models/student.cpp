#include <iostream>
#include "student.h"

using namespace std;

Student::Student() {}//default constructor

//assigns the values of parameters to the properties
Student::Student(string name, string studentId)//constructor with 2 parameters
{
    _name = name;
    _studentId = studentId;
}
//class constructor with 6 parameters
//assigns the parameters to the class properties
Student::Student(string studentId,string pwd,string name,int voterId,bool isRegistered, bool voted){
    _studentId = studentId;
    _password = pwd;
    _name = name;
    _voterId = voterId;
    _registered = isRegistered;
    _voted = voted;
}

string Student::name()//getter method, returns the value of the private property _name
{
    return _name;
}
string Student::studentId()//getter method, returns the value of the private property _studentId
{
    return _studentId;
}

string Student::password(){
    return _password;//getter method, returns the value of the private property _password
}
//setter method, assigns a value to the _password property
void Student::setPassword(string pw){
    _password = pw;
}

int Student::voterId(){//getter method, returns the value of the private property _voterId
    return _voterId;
}
void Student::setVoterId(int id){//setter method, assigns a value to the _voterId property
    _voterId = id;
}
bool Student::voted(){//getter method, returns the value of the private property _voted
    return _voted;
}
void Student::setVoted(bool val){//setter method, assigns a value to the _voted property
    _voted = val;
}

bool Student::registered()//getter method, returns the value of the private property _voted
{
    return _registered;
}
void Student::setRegistered(bool val)//setter method, assigns a value to the _registered property
{
    _registered = val;
}