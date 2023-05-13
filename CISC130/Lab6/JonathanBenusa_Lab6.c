/***Jonathan Benusa***/
#include <stdio.h>

int main()
{
    //2d array that will hold the names of the candidates
    char cand[100][1000];
    //The following code has the user enter the the names of the
    //candidates.  It places a \0 character at the end of each name
    printf("How many candidates are in the race? ");
    //Holds the number of candidates in the race
    int numCand;
    scanf("%i",&numCand);
    //get rid of the return from the scanf above
    getchar();
    //Get the names of the candidates
    int row = 0;
    //one name per row and go until we have the number of candidates
    while(row < numCand)
    {
        printf("Please enter the name candidate number %i: ",row+1);
        //get the first character of the name
        char cur = getchar();
        int col = 0;
        //while they haven't hit enter get the next character
        while(cur != '\n')
        {
            cand[row][col] = cur;
            cur = getchar();
            col = col +1;
        }
        //add the \0 character at the end of the useful info in the array
        cand[row][col]='\0';
        row = row + 1;
    }

    //Finally ask them how many people will be voting
    printf("How many people will be voting? ");
    int numVoters;
    scanf("%i",&numVoters);

    printf("\n**********VOTING WILL COMMENCE NOW***********\n");
    /*YOU WORK GOES HERE*/

    int curvoter = 0;//this will keep track of what voter we are currently on
    int vote[numVoters];//will store the vote ARRAY
    int candvotes[numCand];
    int index = 0;

    while(index<numVoters)
    {
        vote[index] = 0;
        index = index + 1;
    }
    index=0;
    while(index<numCand)
    {
        candvotes[index] = 0;
        index = index + 1;
    }

    while(curvoter < numVoters)//this will cause the program to run until all the voters get through
    {
        printf("Hello voter number %i. The candidates are: \n",curvoter+1);//header will only be voted once before each voter
        row=0;//resets row
        while(row < numCand)
        {
            printf("\t%i. ",row+1);//numbers the candidate
            int col = 0;
            while(cand[row][col] != '\0')//runs the while loop until the
            {
                printf("%c",cand[row][col]);//prints each letter
                col = col + 1;//tells the computer to switch to the next letter
            }
            row= row + 1;//switches to the next row
            printf("\n");
        }
        printf("Please select the number of the voter you wish to vote for:  ");//prompts the user
        scanf("%i",&vote[curvoter]);//stores the vote of the current voter
        candvotes[vote[curvoter]-1] = candvotes[vote[curvoter]-1] + 1;//the candidate that was voted for gets one extra vote
        while(vote[curvoter]>numCand)//repeats if they didn't actually pick a candidate
        {
            printf("Please select the number of the voter you wish to vote for:  ");//prompts the user
            scanf("%i",&vote[curvoter]);//stores the vote of the current voter
            candvotes[vote[curvoter]-1] = candvotes[vote[curvoter]-1] + 1;//the candidate that was voted for gets one extra vote
        }

        curvoter = curvoter + 1;//moves on to the next voter
    }

    printf("\nThe results are:\n");//header for the results
    row=0;//resets row
    while(row < numCand)
    {
        printf("\t%i. ",row+1);//numbers the candidate
        int col = 0;
        while(cand[row][col] != '\0')//runs the while loop until the
        {
            printf("%c",cand[row][col]);//prints each letter
            col=col+1;//tells the computer to switch to the next letter
        }
        printf("\t received %i votes",candvotes[row]);
        row=row+1;//switches to the next row
        printf("\n");
    }


}
