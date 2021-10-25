#ifndef HOMESCREEN_H
#define HOMESCREEN_H

#include "../providers/listProvider.h"
#include "../providers/candidateList.h"
#include "../providers/studentList.h"

class HomeScreen
{
private:
    void _buildHomeScreen();
    void _loginPage();
    void _signUpPage();
    void _voteScreen();
    void _registrationScreen();
    int _generateVoterId();
    void _votingSystem();
    int validateVote(int ballotID,string pos);
public:
    HomeScreen();
    
};

#endif
