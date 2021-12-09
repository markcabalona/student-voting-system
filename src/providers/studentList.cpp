#include <iostream>
#include <string.h>
#include "studentList.h"

using namespace std;

// list operations defenition

int StudentList::insert(Student stud)
{
    studentNode *newStud = new studentNode;
    newStud->student = stud;
    newStud->next = nullptr;

    if (students == nullptr)
    {
        students = newStud;
        return 0;
    }
    string studId = stud.studentId();
    if (locate(&studId, nullptr) != nullptr)
    {
        return 1;
    }

    studentNode *head_copy = new studentNode;
    head_copy = students;
    while (head_copy->next != nullptr)
    {
        head_copy = head_copy->next;
    }
    head_copy->next = newStud;

    return 0;
}

void StudentList::makeNull()
{
    students = new studentNode;
    students = nullptr;
}

studentNode *StudentList::locate(string *studentId, int *voterId)
{

    studentNode *head_copy = new studentNode;
    head_copy = students;

    if (isEmpty())
    {
        return nullptr;
    }

    if (studentId != NULL)
    {
        while (head_copy != nullptr)
        {
            if (head_copy->student.studentId().compare(*studentId) == 0)
            {
                return head_copy;
            }
            head_copy = head_copy->next;
        }

        return nullptr;
    }
    else
    {
        while (head_copy != nullptr)
        {
            if (head_copy->student.voterId() == *voterId)
            {
                return head_copy;
            }
            head_copy = head_copy->next;
        }

        return nullptr;
    }
}

bool StudentList::isEmpty()
{
    return students == nullptr;
}
int StudentList::update(string studentId, Student stud)
{
    if (locate(&studentId, nullptr) != nullptr)
    {
        return -1;
    }
    studentNode *head_copy = new studentNode;
    head_copy = students;
    while (head_copy != nullptr)
    {
        head_copy = head_copy->next;
    }
    head_copy->student = stud;

    return 1;
}

int StudentList::retrieve()
{

    FILE *fp = fopen(STUDENT_DB_FILEPATH, "r");

    if (!fp)
    {
        return -1;
    }
    else
    { // if csv reading is successfull populate the List
        Student tempRec;
        string id, pw, name;
        int voterId, isReg, voted;
        char buff[255];
        char *token;
        int col;
        int line = 0;
        while (fgets(buff, 255, fp))
        {
            if (line == 0)
            {
                // we don't want to read the header
                line = 1;
                continue;
            }
            col = 0;
            token = strtok(buff, ",\n");
            while (token != NULL)
            {
                // parse the csv
                // csv columns looks like this
                // student_id,pasword,name,voter_id,isRegistered,voted
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
                token = strtok(NULL, ",\n");
            }
            insert(Student(id, pw, name, voterId, isReg, voted));
        }
        fclose(fp); // close the file
        return 1;
    }
}

int StudentList::save()
{
    FILE *fp = fopen(STUDENT_DB_FILEPATH, "w");

    fprintf(fp, "student_id,password,name,voter_id,isRegistered,voted\n");

    studentNode *head_copy = students;
    while (head_copy != nullptr)
    {
        fprintf(fp, "%s,%s,%s,%d,%d,%d\n", head_copy->student.studentId().c_str(), head_copy->student.password().c_str(), head_copy->student.name().c_str(), head_copy->student.voterId(), head_copy->student.registered(), head_copy->student.voted());
        head_copy = head_copy->next;
    }

    fclose(fp);
    return 1;
}