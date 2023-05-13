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
    if(n!=1)// continue until the number is equal to one
    {
        if(n%2==0)//if the number is even divide by two
        {
            JarvisSequence(n/2);
        }
        else //if the number is odd multiply by 3 and add one
        {
            JarvisSequence(n*3+1);
        }

    }
}
void FillArray(int x[],int size)
{
    if(size > 0)
    {
        x[size-1] = rand() % 314 + 7;//from 7 to 320
        FillArray(x,size-1);
    }
}
void printArray(int x[],int size)
{
    if(size > 1)
    {
        printArray(x,size-1);//this goes in front of the printf so that it stacks everything up before it prints
        printf("%i,  ",x[size-2]);//prints all but the last number in the array
    }
}
void copyArray(int x[],int a[], int size,int index)
{
    if(size >= 0)
    {
        x[size-1] = a[index];//x gets backward a
        copyArray(x,a,size-1,index+1);
    }
}
checkRepeat(int array[],int size,int repeat)
{
    int timesRepeated = 0;
    if(size!=0)//as long as the array still has boxes unchecked
    {
        if(array[size-1]==repeat)//if the current box being checked is equal to the number being checked for
        {
            return timesRepeated = checkRepeat(array, size-1, repeat) + 1;//add one to the answer
        }
        return timesRepeated = checkRepeat(array, size-1, repeat);
    }
    return timesRepeated;
}

void main()
{
    srand((unsigned)time(NULL));

    /**Part 2**/
    printf("\nFast Powering\n\n");
    printf("Enter a base\n");
    int base = posNumReturn();
    printf("Enter an exponent\n");
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
    printf("Enter the size of the array\n");
    int size = posNumReturn();
    int array[size];
    FillArray(array, size);

    /**Part 5**/
    printf("\n\nPrint Array\n\n");
    printArray(array, size);
    printf("%i\n",array[size-1]);//prints the last number w/o a comma

    /**Part 6**/
    printf("\n\nCopy Array Backwards\n\n");
    int index = 0;
    int secondArray[size];
    copyArray(secondArray, array, size, index);
    printArray(secondArray, size);
    printf("%i\n",secondArray[size-1]);

    /**Part 7**/
    printf("\n\nHow many times\n\n");
    printf("Enter the number you want to check for in the array: ");
    int repeat = posNumReturn();
    int numRepeated = checkRepeat(array, size, repeat);
    printf("The number was repeated %i times.\n\n",numRepeated);



}
