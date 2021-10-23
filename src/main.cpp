#include <iostream>
#include "providers/listProvider.h"
#include "screens/homeScreen.h"
#include <unistd.h>
using namespace std;

ListProvider provider;
future<void> userReady = async(&ListProvider::checkFlashDrive, &provider);
int main(void)
{
    // check for flashdrive asycnhronously

    HomeScreen();

    // todo

    system("pause");
}
