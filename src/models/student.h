// hindi pa sure pwedeng bawasan pa ng mga properties
#ifndef STUDENT_H
#define STUDENT_H
#include<iostream>
using namespace std;

//isang blue print ng isang student
// para siyang bagong data type na Student, ang laman nyan e yung mga properties na nakadeclare sa loob
// may mga methods din ito na pwedeng mag manipulate ng state ng isang student
class Student
{

//ito yung mga properties ng isang student
// ito yung parang characteristics ng isang student hahaha
private://pag private property ibig sabiihn sa loob lang ng Student class maaaccess at mamomodify ang values
//ang isang student merong name etc.
    string _name;
    string _password;
    string _studentId;
    bool _registered = false;
    int _voterId = 0;
    bool _voted = false;

//pag public open siya sa lahat meaning pag gumawa ka ng student,
//pwede mong baguhin directly yung state o yung values ng mga property ng student class
public:
// dito wala akong ginawa na public property 
//ang ginawa ko ay gumawa ako ng mga getter at setter methods
//para makuha at mamodify natin yung state ng mga private property ng Student class
//ito at class method, function siya sa loob ng
    string name();//this will simply return the current value of _name property
    string password();
    void setPassword(string pw);
    string studentId();
    bool registered();
    int voterId();
    void setVoterId(int id);
    void setRegistered(bool val);
    bool voted();
    void setVoted(bool val);

    //ito naman ay ang class constructor meaning pag gumawa tayo ng student object
    //ito yung unang mangyayari (defined sa student.cpp)
    Student(string name,string studentId);
    //student_id,password,name,voter_id,isRegistered,voted
    Student(string studentId,string pwd,string name,int voterId,bool isRegistered, bool voted);
    //ito ay default constructor para pwede tayo gumawa ng student object nang hindi pinapasahan ng kahit na anong paremeters
    Student();
};


#endif