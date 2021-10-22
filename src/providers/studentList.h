#ifndef STUDENT_LIST_H
#define STUDENT_LIST_H

#include "../models/student.h"
#define MAX_STUDENTS 128
#define STUDENT_DB_FILEPATH "../db/students.csv"

using namespace std;

typedef struct StudentList
{
    Student students[MAX_STUDENTS];
    int last;
    int locate(string studentId);
    int insert(Student stud);
    void makeNull();
    void display();
    int isFull();
    int isEmpty();
    int update(string studentId);
    void menu();
    int retrieve();

} StudentList;

#endif

/*
#ifndef CANDIDATE_LIST_H
#define CANDIDATE_LIST_H
#include <iostream>
#include "../models/candidate.h"

#define MAX_CANDIDATE 20
using namespace std;

typedef struct CandidateList
{
    Candidate candidates[MAX_CANDIDATE];
    int last;
} CandidateList;

class CandidateListProvider
{
private:
    CandidateList _list[MAX_CANDIDATE];
public:
    CandidateList* list();
    void retrieve();
    void save();

    int locate(string studentId);
    int insert(Candidate can);
    void makeNull();
    void display();
    int isFull();
    int isEmpty();
    int update(string studentId);
    void menu();
    void dispose();

    CandidateListProvider();
};


// void initializeCandidateList();

// void retrieve();
// void save();

// // list operations
// int locate(string studentId);
// void makeNull();
// void display();
// int isFull();
// int isEmpty();
// int update(string studentId);

// void menu();

// // utilities
// char *get_string(); // returns a pointer to a string
// int get_int();      // returns an integer input from user, this filters nonnumeric characters
// float get_float();  // same as get_int

#endif
*/