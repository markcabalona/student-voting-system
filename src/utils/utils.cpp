#include<iostream>
#include"utils.h"
#include<conio.h>
#include<stdlib.h>
#include<string.h>

using namespace std;

int code = 13;

int getInt(string prompt){

    string input;
    bool valid = false;
    do
    {
        cout<<prompt;
        cin>>input;
        try
        {
            stoi(input);
            valid = true;
        }
        catch(const std::exception& e)
        {
            std::cerr << "Input must be integer."<<endl;
        }
        
    } while (!valid);
    return stoi(input);
}

string getPassword(string prompt)
{
    cout<< prompt;

    int i = 0;
    char *pw = (char*)malloc(i * sizeof(char));
    char temp;
    while ((temp = getch()) != 13)
    {
        if (temp != '\b')
        {
            pw = (char*)realloc(pw,(i+1) * sizeof(char));//allocate more memory
            pw[i] = temp+code;
            putchar('*');
            i++;
        }
        else if (temp == '\b' && i > 0)
        {
            pw[i] = '\0';
            i--;
            printf("\b  \b\b");
        }
    }
    pw[i] = '\0';
    
    return string(pw);
}

string decodePassword(string pw){
    char* decoded = strdup(pw.c_str());
    for(int i = 0; i<pw.length();i++){
        decoded[i] = decoded[i] - code;
    }
    return string(decoded);
}