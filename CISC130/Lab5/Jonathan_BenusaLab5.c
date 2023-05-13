/*Jonathan Benusa*/
#include <stdio.h>

void main()
{

    char a[1000];
    char junk;
    char op;
    char temp;
    int index;
    index=0;
    int index2;
    index2 = 0;


    printf("Would you like to encrypt (e) or decrypt (d):  ");//asks the user what they want to do
    op=getchar();
    junk=getchar();

    while(op!='e' && op!='d')
    {
        printf("Would you like to encrypt (e) or decrypt (d):  ");//if the user doesn't type a e or d it asks again
        op=getchar();
        junk=getchar();
    }



    if(op=='e')//if they want to encrypt
    {
        printf("Enter the message you would like to encrypt:  ");//tells the user what to do
        temp = getchar();//scans what they type

        while(temp != '\n')//will continue until it gets to the new line character
        {
            a[index] = temp;//stores each character in order
            temp = getchar();
            index = index + 1;
        }
        while(index2 < index)
        {
            if(a[index2] + index2 + 1 <= 'z' && a[index2] + index2 + 1 > 'a' && a[index2] <= 'z' && a[index2] >= 'a')//for all letters that will end up being between a and z
            {
                a[index2] = a[index2] + index2 + 1;
            }
            else
            {
                if(a[index2] + index2 + 1 > 'z' && a[index2] <= 'z' && a[index2] >= 'a')//for lowercase where the value will be greater than z
                {
                    a[index2] = a[index2] + index2 - 'z' + 'a';
                }
            }
            if(a[index2] + index2 + 1 <= 'Z' && a[index2] + index2 + 1 > 'A' && a[index2] <= 'Z' && a[index2] >= 'A')//for capital letters that will be less than Z
            {
                a[index2] = a[index2] + index2 + 1;
            }
            else
            {
                if(a[index2] + index2 + 1 > 'Z' && a[index2] <= 'Z' && a[index2] <= 'Z' && a[index2] >= 'A')//for capital letters that will be greater than Z
                {
                    a[index2] = a[index2] + index2  - 'Z' + 'A';
                }
            }

            printf("%c",a[index2]);
            index2=index2+1;
        }


    }
    else//if they want to decrypt
    {
        printf("Enter the message you would like to decrypt:  ");//tells the user what to do
        temp = getchar();//scans what they type

        while(temp!='\n')//will continue until it gets to the new line character
        {
            a[index] = temp;//stores each character in order
            temp = getchar();
            index = index + 1;
        }
        while(index2 < index)
        {
            if(a[index2]>='a' && a[index2]<='z' && a[index2]-index2-1>='a')//if a[index2] is a lowercase letter that will not be less than a
            {
                a[index2]=a[index2]-index2-1;
            }
            else
            {
                if(a[index2]>='a' && a[index2]<='z' && a[index2]-index2-1<'a')//if a[index2] is lowercase and will be less than a
                {
                    a[index2]=a[index2]-index2+'z'-'a';
                }
            }

            if(a[index2]>='A' && a[index2]<='Z' && a[index2]-index2-1>='A')//if a[index2] is a uppercase letter that will not be less than a
            {
                a[index2]=a[index2]-index2-1;
            }
            else
            {
                if(a[index2]>='A' && a[index2]<='Z' && a[index2]-index2-1<'A')//if a[index2] is uppercase and will be less than a
                {
                    a[index2]=a[index2]-index2+'z'-'a';
                }
            }
            printf("%c",a[index2]);
            index2 = index2 + 1;
        }


    }



}
