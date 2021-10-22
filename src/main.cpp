#include <iostream>
//#include "models/candidate.h"
//#include "providers/candidateList.h"
//#include "providers/studentList.h"
#include "providers/listProvider.h"

using namespace std;

int main(void)
{
    cout<<"Hello";
    cout<<"Hello";
    
    ListProvider provider;
    
    cout<<"Hello";
    cout<<provider.candidateList().last<<endl;
    cout<<provider.studentList().last<<endl;

   for (int i = 0; i <= provider.studentList().last; i++){
       cout<<i+1<<provider.studentList().students[i].name()<<endl;
   }

    system("pause");

    

}
