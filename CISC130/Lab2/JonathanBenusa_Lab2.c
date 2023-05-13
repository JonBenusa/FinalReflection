/*Jonathan Benusa*/
#include <stdio.h>
int main ()
{

    printf("PART 1\n\n");

/***SOLUTION FOR PART 1***/

    int a; //defining my integers
    int b;
    int c;
    int d;

    a=1;  //assigning random values
    b=3;
    c=-1;
    d=b; //making d a place holder for the variable that is redefined first
    printf("initially: a is %i, b is %i, and c is %i,\n",a,b,c);

    b=a;
    a=c;
    c=d;
    printf("After first swap: a is %i, b is %i, c is %i\n",a,b,c);

    d=b;  //defining d to become the new b again as a place holder
    b=a;
    a=c;
    c=d;
    printf("After second swap: a is %i, b is %i, c is %i",a,b,c);


    printf("\n\nPART 2\n\n");

/***SOLUTION FOR PART 2***/

    float totalbill;  //defining my floats
    float tip;
    float remander;

    totalbill=8;  //assigning random values
    tip=totalbill*0.1;  //multiply by .1 to see what 10% is

    printf("The tip for a bill when the bill is $%f and you are tipping 10%% is $%f\n",totalbill,tip);

    tip=totalbill*3/20; //multiply by 3/20 to find what 15% is

    printf("The tip for a bill when the bill is $%f and you are tipping 15%% is $%f\n",totalbill,tip);

    tip=totalbill*0.2; //multiply by .2 to find what 20% is

    printf("The tip for a bill when the bill is $%f and you are tipping 20%% is $%f\n",totalbill,tip);



    printf("\n\nPART 3\n\n");

/***SOLUTION FOR PART 3***/
    int number;  //defining my integers
    int x;
    int y;
    int z;
    int w;

    number=2101;  //assigning a random value
    x=number%10;   //assigning each variable to one of the digits
    y=(number%100-x)/10;
    z=(number%1000-x-y)/100;
    w=number/1000;


    int reversed;
    reversed=x*1000+y*100+z*10+w;  //plugging each digit back in as its reversed number

    printf("the number %i with its digits reversed is %i",number,reversed);




}
