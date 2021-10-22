#include <iostream>
#include "student.h"

using namespace std;

Student::Student() {}

Student::Student(string name, string studentId,string pwd)
{
    _password = pwd;
    _name = name;
    _studentId = studentId;
}
Student::Student(string studentId,string pwd,string name,int voterId,bool isRegistered, bool voted){
    _studentId = studentId;
    _password = pwd;
    _name = name;
    _voterId = voterId;
    _registered = isRegistered;
    _voted = voted;
}

string Student::name()
{
    return _name;
}
string Student::studentId()
{
    return _studentId;
}

string Student::password(){
    return _password;
}
void Student::setPassword(string pw){
    _password = pw;
}

int Student::voterId(){
    return _voterId;
}
void Student::setVoterId(int id){
    _voterId = id;
}
bool Student::voted(){
    return _voted;
}
void Student::setVoted(bool val){
    _voted = val;
}

bool Student::registered()
{
    return _registered;
}
void Student::setRegistered(bool val)
{
    _registered = val;
}