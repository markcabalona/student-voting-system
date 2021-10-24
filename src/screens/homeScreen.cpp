
#include "homeScreen.h"
#include <unistd.h>
#include<ctime>

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
    if ((index = provider.studentList().locate(&id,nullptr)) < 0)
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
        else
        {
            // todo voting system
            cout << "Vote Wisely." << endl;
            system("pause");
        }
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
            cout<<"Your voter ID is: "<< provider.user()->voterId()<<endl;
            system("pause");
            _buildHomeScreen();
        }
    }
}

int HomeScreen::_generateVoterId()
{
    srand((unsigned)time(0));
    int temp = 1000 + rand() % 9000;
    while (provider.studentList().locate(nullptr,&temp) >= 0)
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
