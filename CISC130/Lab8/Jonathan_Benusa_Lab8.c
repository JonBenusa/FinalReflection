/** Jonathan Benusa **/
#include <stdio.h>
int censor(char phrase[], int psize, char curses[], int csize, char cens[1000][1000])
{
    int row=0;
    int col=0;
    int n;
    int index;
    index = 0;
    int foul = 0;
    int j = 0;
    while(cens[row-1][col]!='\n')
    {
        while(phrase[index] != '\0')
        {
            /** If the first letter matches **/
            if(phrase[index]==curses[0] && phrase[index-1]==' ' || index==0)//this checks to see if the first letter in the word is bad
            {
                int match = 1; // match is true

                while(curses[j] != '\0' && match == 1)
                {
                    if(curses[j] != phrase[index+j])
                    {
                        match = 0; // match is false
                    }
                    j = j + 1;
                }
                if(match == 0)//if there is one letter that isn't a match restart looking for the first letter
                {
                    j = 0;
                }
                if(curses[j] == '\0')
                {
                    if(phrase[index+j] == ' ' || phrase[index+j] == '\0')//if index plus j gets all of the way through the word and it still only had matches the word was bad
                    {
                        foul = 1;
                        int k = 0;
                        while(k <= j)
                        {
                            phrase[index+k] = '*';
                            k = k + 1;
                        }
                        phrase[index+j] = ' ';
                        j = 0;
                    }
                }
            }
            index = index + 1;
            /** Skip to the next word **/
            while(phrase[index] == ' ' && phrase[index] != '\0')
            {
                index = index + 1;
            }
            index + index + 1;
        }
    }
    return foul;
}

int main()
{
    /** Sets curse word **/
    int csize = 5;
    char curse[5] = "darn"; // the curse words, this actually works

    char cens[1000][1000];
    int col = 0;
    int row = 0;
    while(col<1000)
    {
        cens[row][col] = 'a';
        col = col + 1;
    }

    char tem;
    col = 0;
    while(cens[row-1][0]!='\n')
    {
        printf("Enter a curse word you would like to have censored. If you would like to continue just press enter.");
        tem = getchar();
        cens[row][col]=tem;
        while(tem!='\n')
        {
            col = col + 1;
            tem = getchar();
            cens[row][col]=tem;
        }
        col = 0;
        row = row + 1;
    }
    /** Reads in a phrase **/
    int strsize = 1001;
    char str[strsize];

    printf("Please enter a phrase:\n");
    char temp[strsize];//will hold the character
    scanf("%c",&temp[0]);// scans in the user's phrase
    int index = 0;
    while(temp[index]!='\n')//gets the phrase from the user
    {
        str[index] = temp[index];
        index = index + 1;
        temp[index] = getchar();
    }
    str[index] = '\0';
    str[index+1] = '\0';//the code would glitch if the last word was "darn "

    int foul = censor(str, strsize, curse, csize, cens);
    if(1 == foul)
    {
        printf("\nThere was potty language in your phrase. It was censored. See below:\n");
    }
    else
    {
        printf("\nYour sentence was clean. Here is what you entered:\n");
    }

    index = 0;
    while(str[index] != '\0')
    {
        printf("%c",str[index]);
        index = index + 1;
    }
    printf("\n\n");
}
