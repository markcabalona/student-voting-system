#include <iostream>
#include "listProvider.h"

using namespace std;

ListProvider::ListProvider()
{
    _candidateList.makeNull();
    _studentList.makeNull();
    retrieve();
}
CandidateList ListProvider::candidateList()
{
    return _candidateList;
}
StudentList ListProvider::studentList()
{
    return _studentList;
}


void ListProvider::retrieve()
{
    // TODO
    cout<<"nice";
    _studentList.retrieve();
}
void ListProvider::save()
{
    // TODO
}
