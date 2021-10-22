#include <iostream>
#include <string.h>
#include "studentList.h"

using namespace std;

//list operations defenition

int StudentList::insert(Student stud){

     if (isFull())
    {
        return -1;
    }
    else if (int i = locate(stud.name()) >= 0)
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

int StudentList::locate(string studentId)
{
    for (int i = 0; i < last + 1; i++)
    {
        if (students[i].studentId().compare(studentId) == 0)
        {
            return i;
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
    int index = locate(studentId);
    if (index < 0)
    {
        return -1;
    }
    return 0;
}

int StudentList::retrieve(){

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
        char buff[129];
        char *token;
        int col;
        int line = 0;
        while (fgets(buff, 129, fp))
        {
            if(line == 0){
                //we don't want to read the header
                line = 1;
                continue;
            }
            col = 0;
            token = strtok(buff, ",\n");
            while (token != NULL)
            {
                //parse the csv
                //csv columns looks like this
                //student_id,pasword,name,voter_id,isRegistered,voted
                switch (col)
                {
                case 0://col 1
                    id = token;
                    break;
                case 1://col 2
                    pw = token;
                    break;
                case 2://col 3
                    name = token;
                    break;
                case 3://col 4
                    voterId = atoi(token);
                    break;
                case 4://col 5
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
            //return 0 if list is full
            if(insert(Student(id, pw, name, voterId, isReg, voted)) < 0){
                fclose(fp); // close the file
                return 0;
            }
        }
        fclose(fp); // close the file
        return 1;
    }
}
