#ifndef STUDENT_LIST_H
#define STUDENT_LIST_H

#include "../models/student.h"
#define MAX_STUDENTS 128
#define STUDENT_DB_FILEPATH "../db/students.csv"

using namespace std;

typedef struct studentNode{
    Student student;
    studentNode* next;
}studentList;

typedef struct StudentList
{
    studentList *students;
    //int last;
    studentNode* locate(string *studentId,int* voterId);
    int insert(Student stud);
    void makeNull();
    bool isEmpty();
    int update(string studentId,Student stud);
    
    int retrieve();
    int save();

} StudentList;

#endif