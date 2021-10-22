#include <iostream>
#include "candidateList.h"

using namespace std;



int CandidateList::insert(Candidate can){
    last++;
    // TODO
    candidates[last] = can;
    return 0;
}


void CandidateList::makeNull()
{
    last = -1;
}

int CandidateList::locate(string studentId)
{
    // TODO
    return 0;
}

void CandidateList::display()
{
    // TODO
}
int CandidateList::isFull()
{
    // TODO
    return 0;
}
int CandidateList::isEmpty()
{ // di ata kailangan to
    // TODO
    return 0;
}
int CandidateList::update(string studentId)
{
    // TODO
    return 0;
}

void CandidateList::menu() {}