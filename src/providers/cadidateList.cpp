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
            if (insert(Candidate(ballotId, name, pos, studId, voteCount)))
            {
                fs.close();
                return 0;
            }
        }
    }
    fs.close();
    return 0;
}

int CandidateList::insert(Candidate can)
{
    if (isFull())
    {
        return -1;
    }
    else if (int i = locate(can.name()) >= 0)
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

int CandidateList::locate(string studentId)
{
    for (int i = 0; i < last + 1; i++)
    {
        if (candidates[i].studentId().compare(studentId) == 0)
        {
            return i;
        }
    }
    return -1;
}

void CandidateList::display()
{
    // TODO
}

void CandidateList::menu() {}