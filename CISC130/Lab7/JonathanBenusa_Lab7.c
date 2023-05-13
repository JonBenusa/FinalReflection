/**Jonathan Benusa**/
#include <stdio.h>
#include <stdlib.h>

int squarerootfloor(int a) //Gives the square root of a number rounded
{
    int b = 0;

    while(b*b<=a) //while the a number times itself is less than or equal to the number entered check the next highest number
    {
        b = b + 1;
    }
    int ans = b - 1;//because the last number was too big
    return ans;
}
int greatestcommondivisor(int a, int b)//checks for a common divisor
{
    int result1 = 0;
    int result2 = 0;
    int check = 1;
    int ans = 0;
    while(check<=a && check<=b){//the gcd can't be greater than either of the numbers
        result1 = a % check;//if the number can be divided by the current number being checked
        result2 = b % check;
        if (result1==0 && result2==0)//if both numbers can be evenly divided by the number being checked
        {
                ans = check;
        }
        check = check + 1;
    }
    return ans;
}
void divisibleby(int a,int array[])//stores all numbers that a number is divisible by into an array
{
    int index=0;
    int check=0;
    int result1;
    while(a>index)
    {
        array[index]=0;
        index=index+1;
    }
    index=0;
     while(check<=a){
        result1 = a % check;
        if (result1==0)
        {
                array[index] = check;
                index = index + 1;
        }
        check = check + 1;
    }
}

int nextperfectnum(int a)
{
    a=1;
}
void fillarray(int a[],int size) //Fills an array with random values
{
    int index = 0;
    while(index < size)
    {
        a[index] = rand() % 101;//gives all values of a[] a random number between 0 and 100
        index = index + 1;
    }
}
void fillmatrix(int a[20][20])
{
    /*int row = 0;
    int col = 0;
    while ()
    {
        while()
        {
                a[row][col] = rand()
        }
    }*/
}

void main()
{
    srand((unsigned)time(NULL));
    char junk;

    /**EXAMPLE 1**/
    int sq;
    int sqr;
    printf("Enter a positive number: ");
    scanf("%i",&sq);
    scanf("%c",&junk);
    sqr = squarerootfloor(sq);
    printf("The Square root floor of %i is %i\n",sq,sqr);

    /**Example 2**/
    int num1;
    int num2;
    int gcd;
    printf("Enter a positive number: ");
    scanf("%i",&num1);
    scanf("%c",&junk);
    printf("Enter another positive number: ");
    scanf("%i",&num2);
    scanf("%c",&junk);
    gcd = greatestcommondivisor(num1,num2);
    printf("The greatest common divisor of %i and %i is %i\n",num1,num2,gcd);

    /**Example 3**/
    /*int perfect;
    int smallerthanperfect;
    printf("Enter the number smaller than the perfect number you want to find: ");
    scanf("%i",&smallerthanperfect);
    int nums[smallerthanperfect];
    divisibleby(smallerthanperfect,nums);
    int index = 0;
    while(nums[index]!=0){
        printf("%i",nums[index]);
        index=index+1;
    }*/

    /**Example 4**/
    printf("Enter the size of your array: ");
    int size;
    scanf("%i",&size);
    int x[size];
    fillarray(x,size);

}
