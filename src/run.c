#include<stdlib.h>

int main(void){
    system("g++ main.cpp models/*.cpp providers/*.cpp screens/*.cpp -o test && test");
}