/*Jonathan Benusa*/
#include <stdio.h>
int main ()
{

    /*These next lines of code, generate a
    **random number between 0 and 2 (inclusive)
    **and assign it to the variable “comp_throw”.
    **This number is computer's "throw" (rock, paper, or scissors).
    ***/
    srand((unsigned)time(NULL));
    int comp_throw = rand()%3;

    /**Your code below here**/


    int user_throw;//thjs will store what the user chooses
    float win;//stores wins
    float loss;//stores losses
    float tie;//stores ties
    char junk;
    char again;

    loss=0;//defines how many wins losses and ties there are at the start of the program which is 0
    win=0;
    tie=0;

    again='y';

    while(again=='y')//the game will continue as long as again gets y
    {
        srand((unsigned)time(NULL));//establishes a new random throw for each game
        int comp_throw = rand()%3;

        printf("select rock (1), paper (2), or scissors (3):  ");//tells the user what to do
        scanf("%i",&user_throw);//scans what the user entered and assigns it to int userthrow
        scanf("%c",&junk);

        while(user_throw!=3 && user_throw!=2 && user_throw!=1)//if the user doesn't enter a 1 2 or 3
        {
            printf("select rock (1), paper (2), or scissors (3):  ");
            scanf("%i",&user_throw);
            scanf("%c",&junk);
        }


        if(user_throw==1) //checks to see if the user entered rock
        {
            if(comp_throw==0) //checks to see if the computer entered a rock
            {
                printf("You tied!\n");//tells the user what happened
                tie=tie+1.0;//adds a tie
            }
            if(comp_throw==1) //checks to see if the computer entered paper
            {
                printf("You lost!\n");//tells the user what happened
                loss=loss+1.0;//adds a loss
            }
            if(comp_throw==2) //checks to see if the computer entered scissors
            {
                printf("You won!\n");//tells the user what happened
                win=win+1.0;//adds a win
            }
        }

        if(user_throw==2) //checks to see if the user entered paper
        {
            if(comp_throw==0) //checks to see if the computer entered a rock
            {
                printf("You won!\n");//tells the user what happened
                win=win+1.0;//adds a win
            }
            if(comp_throw==1) //checks to see if the computer entered paper
            {
                printf("You tied!\n");//tells the user what happened
                tie=tie+1.0;//adds a tie
            }
            if(comp_throw==2) //checks to see if the computer entered scissors
            {
                printf("You lost!\n");//tells the user what happened
                loss=loss+1.0;//adds a loss
            }
        }

        if(user_throw==3) //checks to see if the user entered scissors
        {
            if(comp_throw==0) //checks to see if the computer entered a rock
            {
                printf("You lost!\n");//tells the user what happened
                loss=loss+1.0;//adds a loss
            }
            if(comp_throw==1) //checks to see if the computer entered paper
            {
                printf("You won!\n");//tells the user what happened
                win=win+1.0;//adds a win
            }
            if(comp_throw==2) //checks to see if the computer entered scissors
            {
                printf("You tied!\n");//tells the user what happened
                tie=tie+1.0;//adds a tie
            }
        }
        printf("If you would like to play again enter y. If not enter n.  ");//asks if they want to play again
        scanf("%c",&again);
        scanf("%c",&junk);

        while(again!='y' && again!='n')
        {
            printf("You didn't enter a y or n. If you would like to play again enter y. If not enter n.  ");//asks if they want to play again
            scanf("%c",&again);
            scanf("%c",&junk);
        }
    }

    float totalgames;
    float winpercent;
    totalgames=win+loss+tie;
    winpercent=(win/totalgames)*100;

    printf("You won %f times, tied %f, and lost %f times. You won %f%% of the time.\n\n",win,tie,loss,winpercent);





}
