/** Jonthan Benusa **/
#include<stdio.h>

void fillBoardFromFile (int board[30][30])
{
    int  i;
    int j;
    char filename[101] = "Lab06_life.txt";
    FILE* fp;

    // Prompt the user for a file name
    printf("Please enter the path to the board file: ");
    gets(filename);

    // Open the file containing creature data
    fp = fopen(filename, "r");//    C:\Users\jdben\OneDrive - University of St. Thomas\CISC130\Lab10\Lab10NoCreaturesTest

    if (fp==NULL)
    {
        printf("The file (%s) was NOT opened.\n", filename );
        exit(1);
    }
    else
    {
        printf("The file (%s) was opened.\n", filename );
    }

    // From the data file, read each row

    for(i=0; i<30; i++)
    {
        for(j=0; j<30; j++)
        {
            if( fscanf(fp, " %d", &board[i][j] ) == 0)
            {
                printf("Unable to read the designated number of elements.\n");
                fclose(fp); // close the file when done reading
                exit(1);
            }
        }
    }
    fclose(fp); // close the file when done reading
}
int checkLife(int board[30][30], int row, int col)
{
    int sum = 0;//place holder for the number of creatures neighboring
    int x = row - 1;
    int y = col - 1;
    while(x<=1+row)//as long as x is a col neighboring or containing the current check
    {
        y = col - 1;
        while(y<=1+col)//as long as y is a row neighboring or containing the current check
        {
            if((x!=row || y!=col) && (x>=0 && y>=0) && (x<=30 && y<=30))//check to make sure that the neighbor is actually on the board and that it isn't the one currently being checked
            {
                if(board[x][y]==1)//if the neighbor being checked has a living creature add one to the sum
                {
                    sum = sum + 1;
                }
            }
            y = y + 1;
        }
        x = x + 1;
    }
    return sum;
}
void randFillBoard(int board[30][30])
{
    int row = 29;
    int col = 29;
    int alive;
    while(row>=0)
    {
        col = 29;
        while(col>=0)
        {
            alive = rand()%10;
            if(alive==0)
            {
                board[row][col] = 1;
            }
            else
            {
                board[row][col] = 0;
            }
            col = col - 1;
        }
        row = row - 1;
    }
}

void printBoard(int board[30][30])
{
    system("CLS");
    int row = 0;
    int col = 0;
    while(row<30)
    {
        col = 0;
        while(col<30)
        {
            if(board[row][col]==1)
            {
                printf("# ");//if there is an animal print the # symbol
            }
            else
            {
                printf("  ");//if there isn't an animal print a space
            }
            col = col + 1;
        }
        printf("\n");//at the end of the row make a new line
        row = row + 1;
    }
}
void reaction(int board[30][30],int whatHappens[30][30])
{
    int row = 0;
    int col = 0;
    while(row<30)
    {
        col = 0;
        while(col<30)
        {
            if(whatHappens[row][col]<=1 || whatHappens[row][col]>=4)//if there are too many or too few neighbors the creature dies
            {
                board[row][col] =  0;
            }
            if(whatHappens[row][col]==3)//if there are exactly 3 neighbors a new creature is either born if if there is already one it stays alive
            {
                board[row][col] = 1;
            }//no need to include if there are 2 neighbors because the number of creatures will stay the same
            col = col + 1;
        }
        printf("\n");//at the end of the row make a new line
        row = row + 1;
    }
}

void main()
{
    srand((unsigned)time(NULL));

    int board[30][30];
    int whatHappens[30][30];

    printf("Would you like to use your own board? Please enter y for yes or n for no:  ");//ask the user if they have a board or if they want a random board
    char start;
    char junk;
    scanf("%c",&start);
    scanf("%c",&junk);
    while(start!='y' && start!='n')
    {
        printf("Would you like to use your own board? Please enter y for yes or n for no:  ");
        scanf("%c",&start);
        scanf("%c",&junk);
    }
    if(start=='y')
    {
        fillBoardFromFile(board);//calls the function that fills the board with the premade board
    }
    else
    {
        randFillBoard(board);//calls the fill a random board function
    }

    printBoard(board);//prints the current board

    int row = 29;
    int col;

    while(row>=0)//for each spot on the board run the check life function that stores the number of neighbors before changes are made
    {
        col = 29;
        while(col>=0)
        {
            whatHappens[row][col] = checkLife(board, row, col);
            col = col - 1;
        }
        row = row - 1;
    }
    char nextGen;
    printf("Would you like to play this round? Enter y for yes and n for no:  ");//ask them if they would like to play. this is mostly here just to prevent the previous board from being deleted before it can be seen
    scanf("%c",&nextGen);
    scanf("%c",&junk);
    while(nextGen!='y' && nextGen!='n')
    {
        printf("Would you like to play this round? Please enter y for yes or n for no:  ");
        scanf("%c",&nextGen);
        scanf("%c",&junk);
    }

    while(nextGen=='y')
    {
        reaction(board, whatHappens);//creates a  new board based on the previous round results
        printBoard(board);//prints the new board

        row = 29;
          while(row>=0)//for each spot on the board run the check life function that stores the number of neighbors before changes are made
    {
        col = 29;
        while(col>=0)
        {
            whatHappens[row][col] = checkLife(board, row, col);
            col = col - 1;
        }
        row = row - 1;
    }


        printf("Would you like to play this round? Enter y for yes and n for no:  ");//ask them if they would like to play again
        scanf("%c",&nextGen);
        scanf("%c",&junk);
        while(nextGen!='y' && nextGen!='n')
        {
            printf("Would you like to play this round? Please enter y for yes or n for no:  ");
            scanf("%c",&nextGen);
            scanf("%c",&junk);
        }
    }



}
