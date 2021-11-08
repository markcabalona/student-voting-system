/*
    devs contributions:
        Mark Cabalona - Lead, debugger
        Eyvind Balasta - tester, debugger

    BSCS 2A             STUDENT VOTING SYSTEM AND REGISTRATION
*/


#include <iostream>
#include "providers/listProvider.h"
#include "screens/homeScreen.h"
#include <unistd.h>
using namespace std;

//these variables are declared as extern in providerList.h
// that means that these vars can be accessed anywhere in the project (in cpp that includes providerList.h)
ListProvider provider;
// check for flashdrive asycnhronously
//future<void> userReady = async(&ListProvider::checkFlashDrive, &provider);
int main(void)
{
    as
    cout<<"Insert FlashDrive"<<endl;
    cout<<"Press <Ctrl+C> to exit"<<endl;
    provider.checkFlashDrive();
    HomeScreen();//this is the responsible of what will the user see in the terminal
}
