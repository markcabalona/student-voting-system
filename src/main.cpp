#include <iostream>
#include "providers/listProvider.h"
#include "screens/homeScreen.h"
#include <unistd.h>
using namespace std;

ListProvider provider;
// check for flashdrive asycnhronously
future<void> userReady = async(&ListProvider::checkFlashDrive, &provider);
int main(void)
{
    HomeScreen();
}
