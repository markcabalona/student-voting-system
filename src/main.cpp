#include <iostream>
#include "models/candidate.h"
#include "list_providers/candidateList.h"
#include <map>
#include <list>
#include <iterator>

using namespace std;
CandidateList cList;

int main(void)
{
    initializeCandidateList();
    
    cout<<cList.last;

    cout<<"GoodBye World";
    
}