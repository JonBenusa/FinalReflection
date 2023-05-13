//Jonathan Benusa
//HW 3
#include <iostream>
#include <stdio.h>
using namespace std;

int main() {
    short Short = 0;
    unsigned short unsignedShort = 0;
    int Int = 0;

    for (int i=1; i<=200; i++) {    //loop through 200 times
        Short = Short + 512;
        unsignedShort = unsignedShort + 512;
        Int = Int + 512;
        if(i%10==0) {               //every ten times print the results
                printf("On the %d th time: Short = %d, Unsigned Short = %d, and Int = %d.\n", i, Short, unsignedShort, Int);
            }
    }


}
