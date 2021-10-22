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


void CandidateList::menu() {}