
#include "homeScreen.h"
#include <unistd.h>
#include <ctime>
#include "../utils/utils.h"

using namespace std;

HomeScreen::HomeScreen()
{
    _buildHomeScreen(); // display the main page whenever an instance of this class is called
}

void HomeScreen::_buildHomeScreen()
{
    bool running = true;

    while (running)
    {
        system("cls");
        cout << "===============Welcome To Our Student Voting System===============" << endl;

        cout << "   1.) Vote" << endl;
        cout << "   2.) Register to Vote" << endl;
        cout << "   3.) Profile" << endl;
        cout << "   4.) Exit" << endl;

        int input;
        bool valid = false;
        do
        {
            input = getInt("Enter: ");
            if (input < 1 || input > 4)
                cout << "Input must be 1 - 4 only.\n";
            else
                valid = true;

        } while (!valid);

        switch (input)
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
            _profile();

            break;
        }
        case 4:
        {
            // stop the flashdrive checking that is running asynchronously
            // provider.cancelFlashDriveChecking();
            cout << "Thank you for using our system." << endl;
            running = false;
            break;
        }

        default:
            break;
        }
    }
}

bool HomeScreen::_loginPage()
{
    // headers
    system("cls");
    cout << "=======================REGISTER======================" << endl;
    cout << endl
         << "Your Information is Listed Below." << endl;
    cout << endl
         << "Name: " << provider.user()->name() << endl;
    cout << "Student ID: " << provider.user()->studentId() << endl;
    cout << "Verify it's you." << endl;
    // end of headers

    // getting user's input
    string pwd = getPassword("Enter your password: ");
    // end of user's input

    int trials = 0;
    while (trials < 3)
    {
        if (pwd.compare(provider.user()->password()) == 0) // validating the password
        {
            cout << endl
                 << "Verified" << endl;
            return true;
        }
        cout << endl
             << "Incorret Password." << endl;
        cout << "Remaining trial: " << 3 - trials << endl;
        pwd = getPassword("\nEnter your password: ");
        trials++;
    }

    system("pause");
    return false;
}

bool HomeScreen::_signUpPage()
{
    system("cls");
    // headers
    cout << "=======================REGISTER======================" << endl;
    cout << "Enter your Student ID: ";
    // end of headers

    // user's input
    string id;
    cin >> id;
    // end of user's input

    // validating the student id
    // only students of the school can sign up
    int isValid;

    //provider.setUser(provider.studentList().students[index])
    if (!(isValid = provider.setUser(id)))//provider.studentList().locate(&id, nullptr)) < 0)
    {
        cout << "Student ID is invalid." << endl;
        system("pause");
        return false;
    }
    // end of validation

    // on success
    else
    {
        cout << "   Signed Up" << endl;
        cout << endl
             << "Your Information is Listed Below." << endl;
        cout << endl
             << "Name: " << provider.user()->name() << endl;
        cout << "Student ID: " << provider.user()->studentId() << endl;

        string pwd;
        bool valid = false;
        do
        {
            pwd = getPassword("Create New Password: ");
            if (pwd.length() < 4 || pwd.length() > 8)
            {
                cout << endl
                     << "Password must be 4 - 8 characters long." << endl;
            }
            else if (pwd.compare(getPassword("\nRe-enter Password: ")) != 0)
            {
                cout << endl
                     << "Password not validated." << endl;
            }
            else
            {
                valid = true;
            }

        } while (!valid);

        provider.user()->setPassword(pwd);
        cout << endl
             << "Account Successfully Created.\n";
        return true;
    }
}

void HomeScreen::_profile()
{
    // if (provider.user() == NULL) // wala pang nakainsert na fd
    // {
    //     cout << "Please Insert a FlashDrive." << endl;
    //     sleep(1);
    //     return;
    // }
    if (provider.isGuestUser())
    {
        cout << "Please Register first." << endl;
    }
    else
    {
        system("cls");
        cout << "========================Profile=========================" << endl;

        cout << "Name: " << provider.user()->name() << endl;
        cout << "Student Id: " << provider.user()->studentId() << endl;
        // cout << "Password: " << decodePassword(provider.user()->password()) << endl;
        cout << "Voter ID: " << to_string(provider.user()->voterId()) << endl;
        cout << "Voted: " << (provider.user()->voted() ? "True" : "False") << endl;

        cout << endl
             << "   1.) Go Back to Main Menu." << endl;
        cout << "   2.) Change Password." << endl;
        int input;
        do
        {
            input = getInt("\nEnter (1 - 2) : ");
        } while (input < 1 || input > 2);

        if (input == 2)
        {
            _changePassword();
        }
    }
    system("pause");
}

void HomeScreen::_changePassword()
{
    system("cls");
    cout << "========================Profile=========================" << endl;

    string pwd = getPassword("Enter your password: ");
    // end of user's input

    if (pwd.compare(provider.user()->password()) != 0) // validating the password
    {
        cout << "\nIncorrect Password.\n";
        return;
    }

    bool valid = false;
    do
    {
        pwd = getPassword("\nCreate New Password: ");
        if (pwd.length() < 4 || pwd.length() > 8)
        {
            cout << endl
                 << "Password must be 4 - 8 characters long." << endl;
        }
        else if (pwd.compare(getPassword("\nRe-enter Password: ")) != 0)
        {
            cout << endl
                 << "Password not validated." << endl;
        }
        else
        {
            valid = true;
        }

    } while (!valid);

    provider.user()->setPassword(pwd);
    cout << endl
         << "Password Changed.\n";
}

void HomeScreen::_voteScreen()
{
    // if (provider.user() == NULL) // if no flashdrive inserted
    // {
    //     cout << "Please Insert a FlashDrive." << endl;
    //     sleep(1);
    // }
    // flashdrive is inserted
    // else
    // {
        // if flashdrive has no student info or if flashdrive has student info but not yet registered
        if (provider.isGuestUser() || !provider.user()->registered())
        {
            cout << "You are not yet registered." << endl;
        }
        else if (_loginPage())
        {
            if (provider.user()->voted())
            {
                cout << "You already voted. You cannot vote again." << endl;
            }

            else
            {
                _votingSystem();
                // set voted to true
                provider.user()->setVoted(true);
            }
        }
        system("pause");
    //}
}

void HomeScreen::_votingSystem()
{
    system("cls");
    cout << "===============Vote Wisely===============" << endl;

    cout << endl;

    // display the candidates based on their position
    //..positionNames contains the position labels = ex [pres,vp,etc..]
    //..positionCount is the length of positionNames
    for (int i = 0; i < provider.candidateList()->positionCount(); i++)
    {
        // print the position name
        cout << "\t\t" << provider.candidateList()->positionNames()[i] << endl
             << endl;

        candidateNode* head_copy = new candidateNode;
        head_copy = provider.candidateList()->candidates;
        for (int j = 0; j < provider.candidateList()->length; j++)
        {
            // filtering the candidates
            if (provider.candidateList()->positionNames()[i].compare(head_copy->candidate.position()) == 0)
            {
                cout << "   " << head_copy->candidate.ballotId() << "  "
                     << head_copy->candidate.name() << endl;
            }
            head_copy = head_copy->next;
        }
        cout << endl
             << endl;
    }

    // getting user's vote
    cout << "\t***Enter ballot ID to vote***" << endl;
    int vote;

    // get a vote per position
    for (int i = 0; i < provider.candidateList()->positionCount(); i++)
    {
        // prompt user to vote for positionNames[i]
        cout << "Who is your " << provider.candidateList()->positionNames()[i] << ": ";
        cin >> vote;
        candidateNode* tempCandidate;

        // check if user's vote is a valid ballot id
        while ((tempCandidate = validateVote(vote, provider.candidateList()->positionNames()[i])) == nullptr)
        {
            cout << endl
                 << "Not a valid ballot ID" << endl;
            cout << "Who is your " << provider.candidateList()->positionNames()[i] << ": ";
            cin >> vote;
        }
        // if user's vote is valid increment the candidate's voteCount
        tempCandidate->candidate.incrementVoteCount();
    }
}

candidateNode* HomeScreen::validateVote(int ballotID, string pos)
{ // returns the index of the candidate if found, returns -1 otehrwise

    candidateNode* tempCandidate = provider.candidateList()->locate(nullptr, &ballotID); // search for the candidate with given ballot id
    // check if the candidate runs for the given position;
    // so the user can only vote for candidate with the position of pos
    if (pos.compare(tempCandidate->candidate.position()) == 0)
    {
        return tempCandidate;
    }
    else
    {
        return nullptr;
    }
}

void HomeScreen::_registrationScreen()
{
    // provider._user is initialized to null
    // when a flashdrive is inseted provider._user will be pointing to a student (with or without initialized value)
    // if (provider.user() == NULL) // check if flashdrive is inserted
    // {
    //     cout << "Please Insert a FlashDrive." << endl;
    //     sleep(1);
    //     return;
    // }
    // else
    // {
        // if flashdrive is inserted but has no student info in it
        if (provider.isGuestUser())
        {
            if(!_signUpPage()) // this will assign new values to the provider._user
            {
                return;
            }
        }
        // if flashdrive is inserted and has a student inside
        else
        {
            if (!_loginPage())
                return;
        }
        // if provider._user is already registered
        if (provider.user()->registered())
        {
            cout << "You are already Registered." << endl;
            system("pause");
            return;
        }
        else // register the user
        {
            // generate voter id
            provider.user()->setVoterId(_generateVoterId());
            // mark user as registered
            provider.user()->setRegistered(true);
            // display the voter id
            cout << "Your voter ID is: " << provider.user()->voterId() << endl;
            system("pause");
            return;
        }
    //}
}

int HomeScreen::_generateVoterId()
{
    srand((unsigned)time(0));
    int temp = 1000 + rand() % 9000;
    while (provider.studentList().locate(nullptr, &temp) != nullptr)
    {
        temp = 1000 + rand() % 9000;
    }
    return temp;
}
