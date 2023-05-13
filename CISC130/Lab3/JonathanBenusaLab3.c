//Jonthan Benusa

#include <stdio.h>
#include <math.h>

int main ()

{

    /***HAVE THE USER ENTER THEIR HAND BELOW***/
    int a;//These are the three cards that the player has
    int b;
    int c;

    char suit1;//these will hold what the suits of the payer's cards are
    char suit2;
    char suit3;
    char junk;

    printf("Enter the value of your first card:  ");
    scanf("%i",&a);//gets the value of the first card
    scanf("%c",&junk);
    printf("Enter the suit of your first card (h for heart, d for diamond, c for a club, and s for spade):  ");
    scanf("%c",&suit1);
    scanf("%c",&junk);//this will get rid of the \n that is left in the computer after scanning the the suits

    printf("Enter the value of your second card:  ");
    scanf("%i",&b);//gets the value of the second card
    scanf("%c",&junk);
    printf("Enter the suit of your first card (h for heart, d for diamond, c for a club, and s for spade):  ");
    scanf("%c",&suit2);
    scanf("%c",&junk);//this will get rid of the \n that is left in the computer after scanning the the suits

    printf("Enter the value of your third card:  ");
    scanf("%i",&c);//gets the value of the third card
    scanf("%c",&junk);
    printf("Enter the suit of your first card (h for heart, d for diamond, c for a club, and s for spade):  ");
    scanf("%c",&suit3);
    scanf("%c",&junk);//this will get rid of the \n that is left in the computer after scanning the the suits




    /***CALCULATE THEIR SCORE BELOW***/



    int total;//will eventually hold the total score of the player

    int card1;/*these will eventually hold the value of the cards so when I check for pairs the original face value of the cards will not be modified*/
    int card2;
    int card3;

    if (a==b && suit1==suit2 || b==c && suit2==suit3 || c==a && suit3==suit1) //This statement checks for any repeated cards
    {
        printf("You entered two of the same card\n");//If there are repeated cards, the computer will tell the user and not continue
    }
    else  //If there are no repeated cards the computer will skip the phrase and calculate the score
    {
        if(suit1=='d') //applies multiplier if first card is a diamond
        {
            card1=a*4;
        }
        if(suit1=='c') //applies multiplier if first card is a heart
        {
            card1=a*2;
        }
        if(suit1!='d' && suit1!='c')
        {
            card1=a;
        }


        if(suit2=='d') //applies multiplier if second card is a diamond
        {
            card2=b*4;
        }
        if(suit2=='c') //applies multiplier if second card is a heart
        {
            card2=b*2;
        }
        if(suit2!='d' && suit2!='c')
        {
            card2=b;
        }



        if(suit3=='d') //applies multiplier if first card is a diamond
        {
            card3=c*4;
        }
        if(suit3=='c') //applies multiplier if first card is a heart
        {
            card3=c*2;
        }
        if(suit3!='d' && suit3!='c')
        {
            card3=c;
        }


        total=card1+card2+card3;



        if(a==b || a==c || c==b) //checks for if a has a pair or a triplet
        {
            total=3*total;
        }

        if(c==b && b==a) //checks to see if there is a triplet
        {
            total=total*5/3;//divide by 3 to get to the original value of all of the card values added and then multiplies by 5 for the triplet multiplier
        }

        if(total%7==0) //checks to see if the total score is divisible by 7
        {
            if(a<=b && a<=c) //if a is the smallest card face value or is equal to both cards then multiply the total by itself
            {
                total=a*total;
            }
            if(b<=a && b<c) //if b is the smallest card or tied with a and not c  face value then multiply the total by itself
            {
                total=b*total;
            }
            if(c<b && c<=a) //if c is the smallest card face value or tied with a and not b then multiply the total by itself
            {
                total=c*total;
            }
        }

        printf("The value of your hand is %i\n",total);

    }
}
