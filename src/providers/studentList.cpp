#include <iostream>
#include <string.h>
#include "studentList.h"

using namespace std;

// list operations defenition

int StudentList::insert(Student stud)
{
    string studName = stud.name();
    if (isFull())
    {
        return -1;
    }
    else if (int i = locate(&studName, nullptr) >= 0)
    {
        return i;
    }
    last++;
    students[last] = stud;
    return 0;
}

void StudentList::makeNull()
{
    last = -1;
}

int StudentList::locate(string *studentId, int *voterId)
{
    if (studentId != NULL)
    {
        for (int i = 0; i < last + 1; i++)
        {
            if ((*studentId).compare(students[i].studentId()) == 0)
            {
                return i;
            }
        }
    }
    else
    {
        for (int i = 0; i < last + 1; i++)
        {
            if (*voterId == students[i].voterId())
            {
                return i;
            }
        }
    }
    return -1;
}

int StudentList::isFull()
{
    return last == MAX_STUDENTS;
}
int StudentList::isEmpty()
{
    return last == -1;
}
int StudentList::update(string studentId)
{
    int index = locate(&studentId, nullptr);
    if (index < 0)
    {
        return -1;
    }
    return 0;
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
            // return 0 if list is full
            if (insert(Student(id, pw, name, voterId, isReg, voted)) < 0)
            {
                fclose(fp); // close the file
                return 0;
            }
        }
        fclose(fp); // close the file
        return 1;
    }
}

int StudentList::save(){
    FILE *fp = fopen(STUDENT_DB_FILEPATH,"w");

    char*tempStudId,*tempPassword,*tempName;

    fprintf(fp,"student_id,password,name,voter_id,isRegistered,voted\n");
    for (int i =0; i<= last; i++){
        
        fprintf(fp,"%s,%s,%s,%d,%d,%d\n",students[i].studentId().c_str(),students[i].password().c_str(),students[i].name().c_str(),students[i].voterId(),students[i].registered(),students[i].voted());
    }
    fclose(fp);
    return 1;
}