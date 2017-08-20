/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */

void init(void)
{
    // Create the board without printing the numbers
int tilespaces=(d*d)-1;//define variable

    for (int i=0; i<d; i++) //iterate over the rows
        {
            for (int j=0; j<d; j++)//iterate over the columns
            {
                //set the tile number
                    board [i][j]=tilespaces;
                    tilespaces--;
            }
            printf("\n");
        }
        
    //if the number of tiles is even, if it is you need to swap 2 and 1
    
    if (d%2==0)
        {
            // int swap = board [d-1] [d-2];
            // board [d-1] [d-2]=board [d-1] [d-3];
            // board [d-1] [d-3]=swap;
            board [d-1] [d-2]=2;
            board [d-1] [d-3]=1;
        }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    // Print the numbers that were established in init
    for (int i=0; i<d; i++) 
        {
            for (int j=0; j<d; j++)
            {
                if (board[i][j]==0)//if the space is 0, print __ instead
                {
                    printf("| __  |");
                }
                else
                {
                    printf ("| %2i  |", board [i][j]);//print two spaces for the number with a space on each side
                }
            }
        printf("\n");    
        }    
    //identify blank tile
    //int blank=board [d-1] [d-1];
    
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
int tilespaces=(d*d)-1;//define variable
int row;
int column;
int move;

    //return false if the tile is not on the board 
    if (tile>tilespaces || tile < 1) 
    {
        return false;
    }
    printf("tile =%d\n",tile);
    //search the board for the tile
    for (int i=0; i<d; i++) 
        {
            for (int j=0; j<d; j++)
            {
               // printf("test 3  i=%d j=%d\n",i,j);
                if (board [i][j]== tile)//if you find the tile you are looking for set variable i to row and j to column
                {
                    row=i;
                    column=j;
                }
               
            }
        }       
            //check if edge of board and if blank space is ajacent to tile you want to move, if so, move

            if (board [row-1] [column]==0 && row > 0)//up
                {
                    move = board [row-1] [column];
                    board [row-1] [column]=board [row] [column];
                    board [row] [column]=move;
                    return true;
                }    
    
                else if (board [row+1] [column]==0 && row < d-1)//down
                {
                    move = board [row+1] [column];
                    board [row+1] [column]=board [row] [column];
                    board [row] [column]=move;
                    return true;
                }            
                else if (board [row] [column+1]==0 && column < d-1) //right
                {
                    move = board [row] [column+1];
                    board [row] [column+1]=board [row] [column];
                    board [row] [column]=move;
                    return true;
                }
                else if (board [row] [column -1]==0 && column > 0) //left
                {
                    move = board [row] [column-1];
                    board [row] [column-1]=board [row] [column];
                    board [row] [column]=move;
                    return true;
                    
                }            
             
    return false;
}



/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    // Check to make sure the board is in the correct order and that 0 is in the bottom right space.
    int correct=1;//define variable
    if (board [d-1] [d-1]!=0)
    {
        return false;
    }

    for (int i=0; i<d; i++) 
    {
        for (int j=0; j<d; j++)
        {
            if (board [i][j] == correct || board [i][j] == 0)
            {
                correct ++;                
            }
            else
            {
            return false;
            }
        }
    }    

    return true;
}