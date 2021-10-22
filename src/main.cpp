#include <iostream>
#include "providers/listProvider.h"
#include "screens/homeScreen.h"

using namespace std;

ListProvider provider;


int main(void)
{   
    //todo
    HomeScreen();
    
    if (provider.user() == NULL){
        cout<<"User is Null";
    }
    else cout<<"User is initialized";


    system("pause");

}

