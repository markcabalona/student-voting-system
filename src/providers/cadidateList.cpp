#include <iostream>
#include "candidateList.h"
#include <fstream>
#include <sstream>

using namespace std;

int CandidateList::retrieve() //returns -1 on error, returns 0 on success
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
        //parse the csv file row by row
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
            //parse a row
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
            if (insert(Candidate(ballotId, name, studId, pos, voteCount)) < 0) //if insrtion has error
            {
                fs.close();
                return 0;
            }
        }
    }
    fs.close();
    return 0;
}

int CandidateList::save()
{
    FILE *fp = fopen(CANDIDATES_DB_FILEPATH, "w");

    fprintf(fp, "ballot_id,name,position,student_id,vote_count\n");

    candidateNode *head_copy = candidates;
    while (head_copy != nullptr)
    {
        fprintf(fp, "%d,%s,%s,%s,%d\n", head_copy->candidate.ballotId(), head_copy->candidate.name().c_str(), head_copy->candidate.position().c_str(), head_copy->candidate.studentId().c_str(), head_copy->candidate.voteCount());
        head_copy = head_copy->next;
    }
    fclose(fp);
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
    candidateNode *newCandidate = new candidateNode;
    newCandidate->candidate = can;
    newCandidate->next = nullptr;

    if (candidates == nullptr)
    {
        candidates = newCandidate;
        length++;
        return 0;
    }

    string tempName = can.name();
    if (locate(&tempName, nullptr) != nullptr)
    {
        return 1;
    }

    candidateNode *head_copy = new candidateNode;
    head_copy = candidates;
    while (head_copy->next != nullptr)
    {
        head_copy = head_copy->next;
    }
    head_copy->next = newCandidate;

    length++;
    return 0;
}

void CandidateList::makeNull()
{
    length = 0;
    candidates = new candidateNode;
    candidates = nullptr;
}

bool CandidateList::isEmpty()
{
    return candidates == nullptr;
}

candidateNode* CandidateList::locate(string *studentId, int *ballotID)
{

    candidateNode *head_copy = new candidateNode;
    head_copy = candidates;

    if (isEmpty())
    {
        return nullptr;
    }

    if (studentId != NULL)
    {
        while (head_copy != nullptr)
        {
            if (head_copy->candidate.studentId().compare(*studentId) == 0)
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
            if (head_copy->candidate.ballotId() == *ballotID)
            {
                return head_copy;
            }
            head_copy = head_copy->next;
        }

        return nullptr;
    }
}
