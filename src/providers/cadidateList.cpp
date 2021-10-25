#include <iostream>
#include "candidateList.h"
#include <fstream>
#include <sstream>

using namespace std;

int CandidateList::retrieve()
{
    fstream fs(CANDIDATES_DB_FILEPATH);

    if (!fs)
    {
        return -1;
    }
    else
    {
        string line, token;
        string name, pos, studId;
        int ballotId, voteCount;
        int col, row = 0;
        while (getline(fs, line))
        {
            stringstream s(line);

            if (row == 0)
            {
                // we don't want to read the header
                row = 1;
                continue;
            }

            col = 0;
            while (getline(s, token, ','))
            {
                switch (col)
                {
                case 0: // col 1
                    ballotId = stoi(token);
                    break;
                case 1: // col 2
                    name = token;
                    break;
                case 2: // col 3
                    pos = token;
                    break;
                case 3: // col 4
                    studId = token;
                    break;
                case 4: // col 5
                    voteCount = stoi(token);
                    break;
                default:
                    break;
                }
                col++;
            }
            _addNewPosition(pos);
            if (insert(Candidate(ballotId, name, studId, pos, voteCount)))
            {
                fs.close();
                return 0;
            }
        }
    }
    fs.close();
    return 0;
}

int CandidateList::save(){
    FILE *fp = fopen(CANDIDATES_DB_FILEPATH,"w");

    fprintf(fp,"ballot_id,name,position,student_id,vote_count\n");
    for (int i = 0; i<= last; i++){
        fprintf(fp,"%d,%s,%s,%s,%d\n",candidates[i].ballotId(),candidates[i].name().c_str(),candidates[i].position().c_str(),candidates[i].studentId().c_str(),candidates[i].voteCount());
    }

    return 1;
}

int CandidateList::_addNewPosition(string posName)
{
    for (int i = 0; i < _positionCount; i++)
    {
        if (posName.compare(_positionNames[i]) == 0)
        {
            return -1;
        }
    }
    _positionNames.push_back(posName);
    _positionCount++;
    return 0;
}

int CandidateList::positionCount()
{
    return _positionCount;
}

vector<string> CandidateList::positionNames()
{
    return _positionNames;
}

int CandidateList::insert(Candidate can)
{
    string tempName = can.name();
    if (isFull())
    {
        return -1;
    }
    else if (int i = locate(&tempName, nullptr) >= 0)
    {
        return i;
    }
    last++;
    candidates[last] = can;
    return 0;
}

void CandidateList::makeNull()
{
    last = -1;
}

int CandidateList::isFull()
{
    return last == MAX_CANDIDATES;
}

int CandidateList::isEmpty()
{
    return last == -1;
}

int CandidateList::locate(string *studentId, int *ballotID)
{
    if (studentId != NULL)
    {
        for (int i = 0; i < last + 1; i++)
        {
            if (candidates[i].studentId().compare(*studentId) == 0)
            {
                return i;
            }
        }
    }
    else
    {
        for (int i = 0; i < last + 1; i++)
        {
            if (*ballotID == candidates[i].ballotId())
            {
                return i;
            }
        }
    }
    return -1;
}

void CandidateList::display()
{
    // TODO
}

void CandidateList::menu() {}