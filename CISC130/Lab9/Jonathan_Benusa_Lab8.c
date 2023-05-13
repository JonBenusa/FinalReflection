/**Jonathan Benusa**/
#include <stdio.h>
int posNumReturn()
{
    int x;
    printf("Enter a positive number: ");
    scanf("%i",&x);
    if(x<0)//while the number entered is negative
    {
        printf("You entered a negative number.");//tell them what they did wrong
        return posNumReturn();//run the function again
    }
    return x;//once the number entered is positive return the number
}
int fastPow(int base,int pow)
{
    int ans = 1;
    if(pow==0)
    {
        return 1;
    }
    if(pow%2==0)//if the exponent is divisible by two
    {
        ans = fastPow(base,pow-2) * base * base;//multiply two at a time
        return ans;
    }
    ans = fastPow(base,pow-1) * base;//if the exponent is odd
    return ans;
}
void JarvisSequence(int n)
{
    printf("%i, ",n);
    if(n!=1)
    {
        if(n%2==0)
        {
            JarvisSequence(n/2);
        }else
        {
            JarvisSequence(n*3+1);
        }

    }
}
void FillArray(int x[],int size)
{
    if(size >= 0)
    {
        x[size] = rand() % 314 + 7;//from 7 to 320
        FillArray(x,size-1);
    }
}
void printArray(int x[],int size)
{
    if(size > 1)
    {
        printArray(x,size-1);//this goes in front of the printf so that it stacks everything up before it prints
        printf("%i--%i,  ",size-2,x[size-2]);//prints all but the last number in the array
    }
}
void copyArray(int x[],int a[], int size,int index)
{
    if(size >= 0)
    {
        x[size-2] = a[index];
        copyArray(x,a,size-1,index+1);
    }
}

void main()
{
    srand((unsigned)time(NULL));

    /**Part 1**/
    int num = posNumReturn();

    /**Part 2**/
    printf("Fast Powering\n\n");
    int base = posNumReturn();
    int pow = posNumReturn();
    int ans = fastPow(base, pow);
    printf("%i",ans);

    /**Part 3**/
    printf("\n\nJarvis Sequence\n\n");
    int n = posNumReturn();
    printf("The Jarvis sequence of %i is: \n",n);
    JarvisSequence(n);

    /**Part 4**/
    printf("\n\nFill Array\n\n");
    int size = posNumReturn();
    int array[size];
    FillArray(array, size);

    /**Part 5**/
    printf("\n\nPrint Array\n\n");
    printArray(array, size);
    printf("%i\n",array[size]);//prints the last number w/o a comma

    /**Part 6**/
    printf("\n\nCopy Array Backwards\n\n");
    int index = 0;
    int secondArray[size];
    copyArray(secondArray, array, size, index);
    printArray(secondArray, size);

    /**Part 7**/
    printf("\n\n\n\n");



}
