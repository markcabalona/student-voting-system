
#include "homeScreen.h"
#include <unistd.h>
#include <ctime>

HomeScreen::HomeScreen()
{
    _buildHomeScreen();
}

void HomeScreen::_loginPage()
{
    system("cls");
    cout << "=======================REGISTER======================" << endl;
    cout << endl
         << "Your Information is Listed Below." << endl;
    cout << endl
         << "Name: " << provider.user()->name() << endl;
    cout << "Student ID: " << provider.user()->studentId() << endl;

    cout << "Verify it's you." << endl;
    cout << "(Your default Password is you last name(in CAPITAL LETTERS).)" << endl;
    cout << "Please Enter Your Password: ";

    string pwd;
    cin >> pwd;
    int trials = 0;
    while (trials < 3)
    {
        if (pwd.compare(provider.user()->password()) == 0)
        {
            cout << "Verified" << endl;
            break;
        }
        trials++;
        cout << "Incorret Password." << endl;
        cout << "Remaining trial: " << 3 - trials << endl;
        cout << "Enter Your Password: ";
        cin >> pwd;
    }
}

void HomeScreen::_signUpPage()
{
    cout << "=======================REGISTER======================" << endl;
    cout << "Enter your Student ID: ";
    string id;
    cin >> id;
    int index;
    if ((index = provider.studentList().locate(&id, nullptr)) < 0)
    {
        cout << "Student ID is invalid." << endl;
        system("pause");
        _buildHomeScreen();
    }

    else
    {
        cout << "   Signed Up" << endl;
        provider.setUser(provider.studentList().students[index]);

        cout << endl
             << "Your Information is Listed Below." << endl;
        cout << endl
             << "Name: " << provider.user()->name() << endl;
        cout << "Student ID: " << provider.user()->name() << endl;
        cout << "Default Password: " << provider.user()->password() << endl;
    }
}

void HomeScreen::_voteScreen()
{
    if (provider.user() == NULL)
    {
        cout << "Please Insert a FlashDrive." << endl;
        sleep(1);
        _buildHomeScreen();
    }
    else
    {
        if (provider.isGuestUser() || !provider.user()->registered())
        {
            cout << "You are not yet registered." << endl;
            system("pause");
            _buildHomeScreen();
        }
        else if(provider.user()->voted())
        {
            cout<<"You already voted. You cannot vote again."<<endl;
            system("pause");
            _buildHomeScreen();
        }
        
        else
        {
            // todo voting system
            _votingSystem();
            provider.user()->setVoted(true);
            cout << "Vote Wisely." << endl;
            system("pause");
        }
    }
}
void HomeScreen::_votingSystem()
{
    system("cls");
    cout << "===============Voting Wisely===============" << endl;

    cout << "Vote For" << endl;
    for (int i = 0; i < provider.candidateList()->positionCount(); i++)
    {
        cout << "\t\t" << provider.candidateList()->positionNames()[i] << endl
             << endl;
        for (int j = 0; j <= provider.candidateList()->last; j++)
        {
            if (provider.candidateList()->positionNames()[i].compare(provider.candidateList()->candidates[j].position()) == 0)
            {
                cout << "   " << provider.candidateList()->candidates[j].ballotId() << "  "
                     << provider.candidateList()->candidates[j].name() << endl;
            }
        }
        cout << endl
             << endl;
    }

    cout << "\t***Enter ballot ID to vote***" << endl;
    int vote;
    for (int i = 0; i < provider.candidateList()->positionCount(); i++)
    {
        cout << "Who is your " << provider.candidateList()->positionNames()[i] << ": ";
        cin >> vote;
        int index;
        while ((index = validateVote(vote, provider.candidateList()->positionNames()[i])) < 0)
        {
            // update candidate here
            cout << endl
                 << "Not a valid ballot ID" << endl;
            cout << "Who is your " << provider.candidateList()->positionNames()[i] << ": ";
            cin >> vote;
        }
        cout<<provider.candidateList()->candidates[index].voteCount()<<endl;
        provider.candidateList()->candidates[index].incrementVoteCount();//bat ayaw neto gumana puta hahah
        cout<<provider.candidateList()->candidates[index].voteCount()<<endl;
    }
}
int HomeScreen::validateVote(int ballotID, string pos)
{
    int index = provider.candidateList()->locate(nullptr, &ballotID);
    if (pos.compare(provider.candidateList()->candidates[index].position()) == 0)
    {
        return index;
    }
    else
    {
        return -1;
    }
}

void HomeScreen::_registrationScreen()
{
    if (provider.user() == NULL)
    {
        cout << "Please Insert a FlashDrive." << endl;
        sleep(1);
        _buildHomeScreen();
    }
    else
    {
        if (provider.isGuestUser())
        {
            _signUpPage();
        }

        else
        {
            _loginPage();
        }
        if (provider.user()->registered())
        {
            cout << "You are already Registered." << endl;
            system("pause");
            _buildHomeScreen();
        }
        else
        {
            // generate voter id
            provider.user()->setVoterId(_generateVoterId());
            provider.user()->setRegistered(true);
            cout << "Your voter ID is: " << provider.user()->voterId() << endl;
            system("pause");
            _buildHomeScreen();
        }
    }
}

int HomeScreen::_generateVoterId()
{
    srand((unsigned)time(0));
    int temp = 1000 + rand() % 9000;
    while (provider.studentList().locate(nullptr, &temp) >= 0)
    {
        temp = 1000 + rand() % 9000;
    }
    return temp;
}

void HomeScreen::_buildHomeScreen()
{
    system("cls");
    cout << "===============Welcome To Our Student Voting System===============" << endl;

    cout << "   1.) Vote" << endl;
    cout << "   2.) Register to Vote" << endl;
    cout << "   3.) Profile" << endl;
    cout << "   4.) Exit" << endl;

    int x;
    cout << "enter: ";
    cin >> x;

    switch (x)
    {
    case 1:
    {
        _voteScreen();
        break;
    }
    case 2:
    {
        _registrationScreen();
        break;
    }
    case 3:
    {
        if (provider.user() == NULL)
        {
            cout << "Please Insert a FlashDrive." << endl;
            sleep(1);
            _buildHomeScreen();
        }
        else
        {
            cout << "========================Profile=========================" << endl;

            cout << "Name: " << provider.user()->name();
            cout << "Student Id: " << provider.user()->studentId();
            cout << "Password: " << provider.user()->password();
            // TODO show all
        }

        break;
    }
    case 4:
    {
        provider.cancelFlashDriveChecking();
        cout << "Cancelled" << endl;
        if (provider.user() == NULL)
        {
            cout << "User is NULL." << endl;
        }
        else
        {
            cout << "user is not NULL." << endl;
        }

        break;
    }

    default:
        break;
    }
}
