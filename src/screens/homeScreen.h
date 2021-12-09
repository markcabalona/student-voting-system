#ifndef HOMESCREEN_H
#define HOMESCREEN_H

#include "../providers/listProvider.h"
#include "../providers/candidateList.h"
#include "../providers/studentList.h"

class HomeScreen
{
private:
    void _buildHomeScreen();//the main page where the user can vote, register, and see his/her profile
    bool _loginPage();//
    bool _signUpPage();//
    void _profile();
    void _changePassword();
    void _voteScreen();//voting system validations happens here
    void _registrationScreen();// registration
    int _generateVoterId();// returns a 4 digit integer that will serve as voter id of the user
    void _votingSystem();//actual voting 
    candidateNode* validateVote(int ballotID,string pos);//validating the candidate's ballot id and posiiton
public:
    HomeScreen();//constructor
    
};

#endif
