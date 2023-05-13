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
    while(check<=a && check<=b) //the gcd can't be greater than either of the numbers
    {
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
int perfectNum(int a)//stores all numbers that a number is divisible by into an array
{
    a = a + 1;//so it will only test numbers bigger than the current one
    int b = a;//place holder for a before it gets a + 1
    int check = 1;
    int result;
    int sum = 0;
    while(sum!=b)
    {
        check = 1;
        sum = 0;
        while(check<a)
        {
            if (a%check==0)//If the number is perfectly divisible by check add check to sum
            {
                sum = sum + check;
            }
            check = check + 1;//make progress in the loop
        }
        b = a;
        a = a + 1;//this will continue progress to the next number that may or may not be a perfect number
    }
    result = b;
    return result;
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
void printArray(int a[], int size)
{
    int index = 0;
    while(index < size)
    {
        printf("%i   ",a[index]);//prints current number in a[index]
        index = index + 1;//moves to the next number
    }
}
void fillmatrix(int a[20][20])
{
    int row = 0;
    int col = 0;
    while(row<20)
    {
        while(col<20)
        {
                a[row][col] = rand()%101;
                col = col + 1;
        }
        col = 0;
        row = row + 1;
    }
}
int dotProduct(int a[],int b[])
{
    int index = 0;
    int sum = 0;
    while(index<12)
    {
        sum = sum + a[index] * b[index];//adds the product of like terms
        index = index + 1;
    }
    return sum;
}
void printMatrix(int matrix[20][20])
{
    int row = 0;
    while(row<20)
    {
        printArray(matrix[row],20);//prints the current row
        row = row + 1;
    }
}

void main()
{
    srand((unsigned)time(NULL));
    char junk;

    /**EXAMPLE 1**/
    printf("\nExample 1\n");
    int sq;
    int sqr;
    printf("Enter a positive number: ");
    scanf("%i",&sq);
    scanf("%c",&junk);
    sqr = squarerootfloor(sq);
    printf("The Square root floor of %i is %i\n",sq,sqr);

    /**Example 2**/
    printf("\nExample 2\n");
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
    printf("\nExample 3\n");
    printf("Enter a positive number: ");
    scanf("%i",&num1);
    scanf("%c",&junk);
    int nextperfect = perfectNum(num1);
    printf("The next perfect number after %i is %i.\n",num1,nextperfect);

    /**Example 4**/
    printf("\nExample 4\n");
    printf("Enter the size of your array: ");
    int size;
    scanf("%i",&size);
    int x[size];
    fillarray(x,size);

    /**Example 5**/
    printf("\nExample 5\n");
    size = 15;
    int d[size];
    fillarray(d,size);
    printArray(d,size);

    /**Example 6**/
    printf("\n\nExample 6\n");
    size=12;
    int w[size];
    int y[size];
    fillarray(w,size);
    fillarray(y,size);
    printArray(w,size);
    printf("\n");
    printArray(y,size);
    printf("\n");
    int dotXY = dotProduct(w,y);
    printf("The dot product of these two vectors is %i\n",dotXY);

    /**Example 7**/
    printf("\n\nExample 7\n");
    size = 20;
    int matrix[size][size];
    fillmatrix(matrix);

    /**Example 8**/
    printf("\n\nExample 8\n");
    printMatrix(matrix);


}
