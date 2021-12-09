/*
    
    Mark Cabalona   
    Eyvind Balasta

    BSCS 2A             STUDENT VOTING SYSTEM AND REGISTRATION
*/

//libraries/modules we used
#include <iostream>

#include "providers/listProvider.h"//this contains the declarations of the list
#include "screens/homeScreen.h"//this contains the declaration of screen functions
using namespace std;

//this variable is declared as extern in providerList.h
// that means that this var can be accessed anywhere in the project (in cpp that includes providerList.h)
ListProvider provider;
// check for flashdrive asycnhronously
//future<void> userReady = async(&ListProvider::checkFlashDrive, &provider);
int main(void)
{
    //prompts the user to insert a flashdrive
    cout<<"Insert FlashDrive"<<endl;
    cout<<"Press <Ctrl+C> to exit"<<endl;

    //runs a loop to check if a flashdrive is inserted
    provider.checkFlashDrive();

    HomeScreen();//this is the responsible of what will the user see in the terminal
    
}
