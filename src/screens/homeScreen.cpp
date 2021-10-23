
#include "homeScreen.h"

HomeScreen::HomeScreen()
{

    // TODO

    _buildHomeScreen();
    //   for (int i = 0; i <= provider.studentList().last; i++){
    //      cout<<i+1<<provider.studentList().students[i].name()<<endl;
    //  }
}
void HomeScreen::_buildHomeScreen()
{
    system("cls");
    cout << "===============Welcome To Our Student Voting System===============\n"
         << endl;

    cout << "   1.) Vote" << endl;
    cout << "   2.) Register to Vote" << endl;
    cout << "   3.) Exit" << endl;

    int x;
    cout << "enter: ";
    cin >> x;

    switch (x)
    {
    case 1:
    {
        if (provider.user() == NULL)
        {
            cout << "Please Insert a FlashDrive." << endl;
            system("pause");
            _buildHomeScreen();
        }
        else
        {
            if (provider.isGuestUser())
            {
                cout << "Please Log In first.";
                system("pause");
                _buildHomeScreen();
            }
            else
            {
                cout << "Vote Wisely." << endl;
            }
        }
        break;
    }
    case 2:
    {
        if (provider.user() == NULL)
        {
            cout << "Please Insert a FlashDrive." << endl;
            system("pause");
            _buildHomeScreen();
        }
        else
        {
            if (provider.isGuestUser())
            {
                // call login page here
                cout << "Please Log In first.";
                system("pause");
                _buildHomeScreen();
            }
            else
            {
                cout << "Registration." << endl;
            }
        }

        break;
    }
    case 3:
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