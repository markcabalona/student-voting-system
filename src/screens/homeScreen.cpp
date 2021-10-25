
#include "homeScreen.h"
#include <unistd.h>
#include <ctime>

HomeScreen::HomeScreen()
{
    _buildHomeScreen();// display the main page whenever an instance of this class is called
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
        // todo
        if (provider.user() == NULL)//wala pang nakainsert na fd
        {
            cout << "Please Insert a FlashDrive." << endl;
            sleep(1);
            _buildHomeScreen();
        }
        else if(provider.isGuestUser()){
            cout<<"Please Register first."<<endl;
        }
        else
        {
            //remind me to put this inside a function(method)
            system("cls");
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
        //stop the flashdrive checking that is running asynchronously
        provider.cancelFlashDriveChecking();
        cout << "Thank you for using our system." << endl;
        break;
    }

    default:
        break;
    }
}

void HomeScreen::_loginPage()
{
    //headers
    system("cls");
    cout << "=======================REGISTER======================" << endl;
    cout << endl
         << "Your Information is Listed Below." << endl;
    cout << endl
         << "Name: " << provider.user()->name() << endl;
    cout << "Student ID: " << provider.user()->studentId() << endl;
    cout << "Verify it's you." << endl;
    cout << "(Your default Password is you last name(in CAPITAL LETTERS).)" << endl;
    //end of headers

    //getting user's input
    cout << "Please Enter Your Password: ";
    string pwd;
    cin >> pwd;
    //end of user's input


    int trials = 0;
    while (trials < 3)
    {
        if (pwd.compare(provider.user()->password()) == 0)//validating the password
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
    //headers
    cout << "=======================REGISTER======================" << endl;
    cout << "Enter your Student ID: ";
    //end of headers

    //user's input
    string id;
    cin >> id;
    //end of user's input

    //validating the student id
    //only students of the school can sign up
    int index;
    if ((index = provider.studentList().locate(&id, nullptr)) < 0)
    {
        cout << "Student ID is invalid." << endl;
        system("pause");
        _buildHomeScreen();
    }
    //end of validation

    //on success
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
    if (provider.user() == NULL)//if no flashdrive inserted
    {
        cout << "Please Insert a FlashDrive." << endl;
        sleep(1);
        _buildHomeScreen();
    }
    //flashdrive is inserted
    else
    {
        //if flashdrive has no student info or if flashdrive has student info but not yet registered
        if (provider.isGuestUser() || !provider.user()->registered())
        {
            cout << "You are not yet registered." << endl;
            system("pause");
            _buildHomeScreen();
        }
        //if user already voted
        else if(provider.user()->voted())
        {
            cout<<"You already voted. You cannot vote again."<<endl;
            system("pause");
            _buildHomeScreen();
        }
        
        else
        {
            //let the user vote
            _votingSystem();
            //set voted to true
            provider.user()->setVoted(true);
            system("pause");
        }
    }
}

void HomeScreen::_votingSystem()
{
    system("cls");
    cout << "===============Voting Wisely===============" << endl;

    cout << "Vote For" << endl;

    //display the candidates based on their position
    //..positionNames contains the position labels = ex [pres,vp,etc..]
    //..positionCount is the length of positionNames
    for (int i = 0; i < provider.candidateList()->positionCount(); i++)
    {
        //print the position name
        cout << "\t\t" << provider.candidateList()->positionNames()[i] << endl
             << endl;
        
        //print all the candidates who is running for positionNames[i]
        for (int j = 0; j <= provider.candidateList()->last; j++)
        {
            //filtering the candidates
            if (provider.candidateList()->positionNames()[i].compare(provider.candidateList()->candidates[j].position()) == 0)
            {
                cout << "   " << provider.candidateList()->candidates[j].ballotId() << "  "
                     << provider.candidateList()->candidates[j].name() << endl;
            }
        }
        cout << endl
             << endl;
    }

    //getting user's vote
    cout << "\t***Enter ballot ID to vote***" << endl;
    int vote;

    //get a vote per position
    for (int i = 0; i < provider.candidateList()->positionCount(); i++)
    {
        //prompt user to vote for positionNames[i]
        cout << "Who is your " << provider.candidateList()->positionNames()[i] << ": ";
        cin >> vote;
        int index;

        //check if user's vote is a valid ballot id
        while ((index = validateVote(vote, provider.candidateList()->positionNames()[i])) < 0)
        {
            cout << endl
                 << "Not a valid ballot ID" << endl;
            cout << "Who is your " << provider.candidateList()->positionNames()[i] << ": ";
            cin >> vote;
        }
        //if user's vote is valid increment the candidate's voteCount
        provider.candidateList()->candidates[index].incrementVoteCount();
    }
}

int HomeScreen::validateVote(int ballotID, string pos)
{   //returns the index of the candidate if found, returns -1 otehrwise

    int index = provider.candidateList()->locate(nullptr, &ballotID);//search for the candidate with given ballot id
    //check if the candidate runs for the given position;
    //so the user can only vote for candidate with the position of pos
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
    //provider._user is initialized to null
    //when a flashdrive is inseted provider._user will be pointing to a student (with or without initialized value)
    if (provider.user() == NULL)//check if flashdrive is inserted
    {
        cout << "Please Insert a FlashDrive." << endl;
        sleep(1);
        _buildHomeScreen();//go back to home screen
    }
    else
    {
        //if flashdrive is inserted but has no student info in it
        if (provider.isGuestUser())
        {
            _signUpPage();//this will assign new values to the provider._user
        }
        //if flashdrive is inserted and has a student inside
        else
        {
            _loginPage();//this will validate the provider._user's password
        }
        //if provider._user is already registered
        if (provider.user()->registered())
        {
            cout << "You are already Registered." << endl;
            system("pause");
            _buildHomeScreen();
        }
        else//register the user
        {
            // generate voter id
            provider.user()->setVoterId(_generateVoterId());

            //mark user as registered
            provider.user()->setRegistered(true);
            //display the voter id
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
