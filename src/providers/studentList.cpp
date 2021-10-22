#include <iostream>
#include <string.h>
#include "studentList.h"

using namespace std;

//list operations defenition

int StudentList::insert(Student stud){
    last++;
    // TODO
    students[last] = stud;
    return 0;
}


void StudentList::makeNull()
{
    last = -1;
}

int StudentList::locate(string studentId)
{
    // TODO
    return 0;
}

void StudentList::display()
{
    // TODO
}
int StudentList::isFull()
{
    // TODO
    return 0;
}
int StudentList::isEmpty()
{ // di ata kailangan to
    // TODO
    return 0;
}
int StudentList::update(string studentId)
{
    // TODO
    return 0;
}

void StudentList::menu() {}

int StudentList::retrieve(){

    FILE *fp = fopen(STUDENT_DB_FILEPATH, "r");

    if (!fp)
    {
        cout<<"error";
        return 0;
    }
    else
    { // if dbf reading is successfull populate the List
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
                switch (col)
                {
                case 0:
                    id = token;
                    break;
                case 1:
                    pw = token;
                    break;
                case 2:
                    name = token;
                    break;
                case 3:
                    voterId = atoi(token);
                    break;
                case 4:
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
                
                //printf("%d", col);
            }
            
            insert(Student(id, pw, name, voterId, isReg, voted));
            cout<<line;
        }
        fclose(fp); // close the file
        return 1;
    }
}



/*
#include <iostream>
#include "candidateList.h"

using namespace std;

CandidateListProvider::CandidateListProvider(){
    makeNull();
}
CandidateList* CandidateListProvider::list(){
    return _list;
}
int CandidateListProvider::insert(Candidate can){
    _list->last++;
    // TODO
    _list->candidates[_list->last] = can;
    return 0;
}

void CandidateListProvider::dispose()
{
    save();
}
void CandidateListProvider::makeNull()
{
    _list->last = -1;
}
void CandidateListProvider::retrieve()
{
    // TODO
}
void CandidateListProvider::save()
{
    // TODO
}
int CandidateListProvider::locate(string studentId)
{
    // TODO
    return 0;
}

void CandidateListProvider::display()
{
    // TODO
}
int CandidateListProvider::isFull()
{
    // TODO
    return 0;
}
int CandidateListProvider::isEmpty()
{ // di ata kailangan to
    // TODO
    return 0;
}
int CandidateListProvider::update(string studentId)
{
    // TODO
    return 0;
}

void CandidateListProvider::menu() {}
*/