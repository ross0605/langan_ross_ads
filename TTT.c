#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define MAX 9

void board();
void reset();

//
// STACK ONE
//
 
struct stack {
    int array[MAX];
    int top;
};

void init_stack(struct stack * s) {
    s -> top = -1;
}

void push(struct stack * s, int item) {
    if (s -> top == MAX - 1) {
        printf("Stack is full. Couldn't push '%d' onto stack\n", item);
        return;
    }
    s -> top++;
    s -> array[s -> top] = item;
}

int * pop(struct stack * s) {
    int * data;
    if (s -> top == -1) {
        printf("       No moves to undo\n");
        return NULL;
    }
    data = & s -> array[s -> top];
    s -> top--;
    return data;
}

//
// STACK TWO
//

struct stack2 {
    int array2[MAX];
    int top2;
};

void init_stack2(struct stack2 * rs) {
    rs -> top2 = -1;
}

void push2(struct stack2 * rs, int item) {
    if (rs -> top2 == MAX - 1) {
        printf("   Stack is full. Couldn't push '%d' onto stack\n", item);
        return;
    }
    rs -> top2++;
    rs -> array2[rs -> top2] = item;
}

int * pop2(struct stack2 * rs) {
    int * data2;
    if (rs -> top2 == -1) {
        printf("             No moves to redo.\n");
        return NULL;
    }
    data2 = & rs -> array2[rs -> top2];
    rs -> top2--;
    return data2;
}

//
// STACK THREE
//

struct stack3 {
    int array3[MAX];
    int top3;
};

void init_stack3(struct stack3 * rrs) {
    rrs -> top3 = -1;
}

void push3(struct stack3 * rrs, int item) {
    if (rrs -> top3 == MAX - 1) {
        printf("   Stack is full. Couldn't push '%d' onto stack\n", item);
        return;
    }
    rrs -> top3++;
    rrs -> array3[rrs -> top3] = item;
}

int * pop3(struct stack3 * rrs) {
    int * data3;
    if (rrs -> top3 == -1) {
        printf("             No moves to pop fucker.\n");
        return NULL;
    }
    data3 = & rrs -> array3[rrs -> top3];
    rrs -> top3--;
    return data3;
}


// Checks if stack is empty

int isempty3(struct stack3 * rrs)
{
    if (rrs->top3 == -1)
        return 1;
    else
        return 0;
}

//
// END OF STACK SETUP
//


// Square array holds value of each square of the board 
char square[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

// Moves array used for comparing against square to check if a position has been taken 
char moves[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

// Keeps track of turn in game
int turn = 1;

// i set to checkwin return value
i = -1;

// v variable set to valid number return value
v = 0;

// Keeps track of the user choice
int choice = 0;

// Keeps track of if there is moves to undo. If stack number is >1 the stack is not empty.
// Could be improved using a 'is stack empty' function instead as seen in stack 3
int stacknumber = 0;

// Represents the chosen case (aka menu item)
int casenumber = 1;

// Set casenumber to playchoice
int playchoice = 0;

//int arr[MAX];
//int front = -1, rear = -1;

// Set X and O characters to X and O chars

char X = 'X';
char O = 'O';

char winner1[] = "\n\tWINNER WINNER CHICKEN DINNER! PLAYER ONE WINS! \n";
char winner2[] = "\n\tWINNER WINNER CHICKEN DINNER! PLAYER TWO WINS! \n";
int x;
double y;


int main(void) {

// Initialise stack 3. This retains the contents after a game, ensuring that the game can be replayed.

    struct stack3 rrs;
    init_stack3( & rrs);


// Game loop. Starts the game again.
game:


// Initialise game stack and redo stacks. Initialising here ensures they are empty when the game is started.
    struct stack s;
    init_stack( & s);

    struct stack2 rs;
    init_stack2( & rs);


// K holds popped value from stack.
    int * k = NULL;
// M holds popped value from stack2.
    int * m = NULL;
// c holds converted K value.
    char c;

// Clear screen and draw board.
    system("cls");
    board();

// Holds valid value- if number is valid will be 0.
    int valid = 0;

// Call reset function to reset all values before game starts.
    reset();

// This while loop shows the initial game message and prompts the user for a choice of which game mode they would like to play. Choice 1 is AI. 2 is PVP and 3 is REPLAY
    while(valid == 0)
    {
        printf("\n\n    Welcome to Noughts and Crosses- A game by Ross Langan. \n\n 	 Type (1) to play against the computer or \n              (2) to play against another player or \n              (3) Replay last game:  ");
        scanf("%i", & playchoice);

        if (playchoice == 1)
        {
            casenumber = 2;
            valid = 1;
        }

        if (playchoice == 2)
        {
            casenumber = 1;
            valid = 1;
        }

        if (playchoice == 3)
        {
            casenumber = 3;
            valid = 1;
        }

        if (playchoice != 1 && playchoice != 2 && playchoice != 3)
        {
            valid = 0;
        }
    }


    switch (casenumber) {
    case 1:

// LOOP- if there is no moves to redo in the stack start here again.
LOOP:

// While game has not been won or drawn, if turn is not divisible by 2, clear the screen, draw the board and request a number from player one. Check number
// is valid and check for undo and redo moves.

        while (i == -1) {
            if (turn % 2 == 1) {

                system("cls");
                board();
                printf("\n\n          Player ONE, enter a number: ");
                scanf("%i", & choice);

				
                v = validno();
                while (v == 1) {
                    printf("   Please enter another number. This number is not valid.\n");
                    printf("Number must be 1-9, or when 44 or 66 are entered, there must be moves\n");
                    printf("                    to undo or redo.");

                    printf("\n\n          Player ONE, enter a number: ");
                    scanf("%i", & choice);

                    v = validno();
                }

				// While square has already been taken, request another number.

                while ((square[choice - 1] == 'X') || (square[choice - 1] == O)) {
                    printf("   Please enter another number. This position has already been taken");

                    printf("\n\n          Player ONE, enter a number: ");
                    scanf("%i", & choice);

                }

                if (choice == 44 && turn > 1) {
                    k = pop( & s);

                    c = * k + '0';

                    square[ * k - 1] = c;
                    turn--;

                    system("cls");
                    board();
                    //printf("%i", * k);

                    push2( & rs, * k);

                    stacknumber++;

                    continue;
                }
				
				// if redo move and moves in stack, redo

                if (choice == 66 && stacknumber != 0) {
                    printf("here");
                    m = pop2( & rs);

                    square[ * m - 1] = X;
                    turn++;

                    system("cls");
                    board();
                    //printf("%i", * k);

                    push( & s, * m);

                    stacknumber--;

                    continue;
                }

				// if redo move and no moves in stack, restart request for move.
				
                if (choice == 66 && stacknumber == 0) {
                    printf("No moves to redo. Please enter a valid number.");
                    goto LOOP;
                }

                if (choice != 44 || choice != 66) {
                    push( & s, choice);
                    square[choice - 1] = X;

                    system("cls");
                    board();

                }
            }
			
			// If turn is divisible by 2, perform same actions for player 2.

            if (turn % 2 == 0) {
                printf("\n\n          Player TWO, enter a number: ");
                scanf("%i", & choice);

                v = validno();
                while (v == 1) {
                    printf("   Please enter another number. This number is not valid.\n");
                    printf("Number must be 1-9, or when 44 or 66 are entered, there must be moves\n");
                    printf("                    to undo or redo.");

                    printf("\n\n          Player TWO, enter a number: ");
                    scanf("%i", & choice);

                    v = validno();
                }

                while ((square[choice - 1] == X) || (square[choice - 1] == O)) {
                    printf("   Please enter another number. This position has already been taken");

                    printf("\n\n         Player TWO, enter a number: ");
                    scanf("%i", & choice);

                }

                if (choice == 44) {
                    k = pop( & s);

                    c = * k + '0';

                    square[ * k - 1] = c;
                    turn--;

                    system("cls");
                    board();
                    //printf("%i", * k);
                    push2( & rs, * k);

                    stacknumber++;

                    continue;
                }

                if (choice == 66 && stacknumber != 0) {
                    printf("here");
                    m = pop2( & rs);

                    square[ * m - 1] = 'O';
                    turn++;

                    system("cls");
                    board();
                    //printf("%i", * k);

                    push( & s, * m);

                    stacknumber--;

                    continue;
                }

                if (choice == 66 && stacknumber == 0) {
                    printf("No moves to redo. Please enter a valid number.");
                    goto LOOP;
                }

                if (choice != 44 || choice != 66) {
                    push( & s, choice);
                    square[choice - 1] = O;

                    system("cls");
                    board();
                }
            }
			
			// Increase the turn by 1 and check for a win.
            turn++;
            i = checkwin();

        }
		
		
		// If i = 1 (when there is a winner) determine which player has won and print a message to the screen.
		// Determine which player has won by checking who's turn it is. If turn is 2 player 1 wins because turn is increased before win is checked.
        if (i == 1) {

            if (turn % 2 == 0) {
                system("cls");
                board();
                
				for(x=0; winner1[x] != '\0'; x++)
				{
					printf("%c",winner1[x]);
					for(y=0; y<=6666666; y++)
					{
					}
				}
            }
            else
            {
                system("cls");
                board();
                
				for(x=0; winner2[x] != '\0'; x++)
				{
					printf("%c",winner2[x]);
					for(y=0; y<=6666666; y++)
					{
					}
				}

            }
        }
		
		// If i = 0 it's a draw, print to screen

        if (i == 0) {

            system("cls");
            board();

            printf("\n            NO WINNER THIS TIME!\n");

        }
		
		// After appropriate message printed ask user to play again. If they wish to play again pop contents of game stack into replay stack.

        printf("\n 		       Play again?");
        printf("\n     Type 0 to quit or any other number to play again: ");
        scanf("%i", & playchoice);

        if(playchoice == 0)
        {
            return 0;

        }
        else
        {
            while(turn >1)
            {
                k = pop(&s);
                push3(&rrs, *k);
                printf("turn = %i", turn);
                printf("%i", * k);

                turn--;
            }

            goto game;

        }
        break;

// Case 2 is game against computer. Exact same as above for player 1s turn.
    case 2:

LOOP2:
        while(i == -1)
        {
            if(turn % 2 == 1)
            {
                system("cls");
                board();
                printf("\n\n          Player ONE, enter a number: ");
                scanf("%i", &choice);

                v = validno();
                while(v == 1)
                {
                    printf("   Please enter another number. This number is not valid.\n");
                    printf("Number must be 1-9, or when 44 or 66 are entered, there must be moves\n");
                    printf("                    to undo or redo.");

                    printf("\n\n          Player ONE, enter a number: ");
                    scanf("%i", &choice);

                    v = validno();
                }

                while((square[choice-1] == X) || (square[choice-1] == O))
                {
                    printf("   Please enter another number. This position has already been taken");

                    printf("\n\n          Player ONE, enter a number: ");
                    scanf("%i", &choice);

                }

                if(choice == 44 && turn >1)
                {
                    k = pop(&s);

                    c = *k + '0';

                    square[*k-1] = c;
                    turn --;

                    system("cls");
                    board();
                    //printf("%i", *k);

                    push2(&rs, *k);

                    stacknumber++;

                    continue;
                }

                if(choice == 66 && stacknumber != 0)
                {
                    printf("here");
                    m = pop2(&rs);

                    square[*m-1] = X;
                    turn ++;

                    system("cls");
                    board();
                    //printf("%i", *k);

                    push(&s, *m);

                    stacknumber--;

                    continue;
                }

                if(choice == 66 && stacknumber == 0)
                {
                    printf("No moves to redo. Please enter a valid number.");
                    goto LOOP2;
                }


                if(choice != 44 || choice != 66)
                {
                    push(&s, choice);
                    square[choice-1] = X;

                    system("cls");
                    board();
                }
            }

			// Player 2 is the computer
			
            if(turn % 2 == 0)
            {

				// Seed random function		
                srand ( time(NULL) );

				// Generate random number
                int r = rand() % 9;

				// If number in moves array does not match number in square array then the square is taken, generate new number until empty square found.
                while(moves[r] != square[r])
                {
                    r = rand() % 9;
                }

                choice = r+1;

                push(&s, choice);
                square[choice-1] = O;

                system("cls");
                board();

                printf("%i", r);
                printf("%c", moves[r]);
                printf("%c", square[r]);


            }

            turn ++;
            i = checkwin();
        }



        if(i == 1)
        {

            if(turn % 2 == 0)
            {
                system("cls");
                board();
                
				for(x=0; winner1[x] != '\0'; x++)
				{
					printf("%c",winner1[x]);
					for(y=0; y<=6666666; y++)
					{
					}
				}
            }
            else
            {
                system("cls");
                board();
                
				for(x=0; winner2[x] != '\0'; x++)
				{
					printf("%c",winner2[x]);
					for(y=0; y<=6666666; y++)
					{
					}
				}
            }
        }

        if(i == 0)
        {

            system("cls");
            board();

            printf("\n            NO WINNER THIS TIME!\n");

        }


        printf("\n 		       Play again?");
        printf("\n     Type 0 to quit or any other number to play again: ");
        scanf("%i", & playchoice);

        if(playchoice == 0)
        {
            return 0;

        }
        else
        {

            while(turn >1)
            {
                k = pop(&s);
                push3(&rrs, *k);
                printf("turn = %i", turn);
                printf("%i", * k);

                turn--;
            }

            goto game;

        }
        break;


	// Case 3 is replay game
    case 3:

		// N holds input value- shouold be 1.
        int n = 0;
		// gg holds popper stack value
        int * gg = NULL;
		
		// While stack isn't empty, pop moves one at a time and plot on screen
        while(rrs.top3 != -1) {

            system("cls");
            board();
            printf("turn: %i", turn);


                gg = pop3(&rrs);
                printf("%i", *gg);

                if (turn % 2 == 1)
                {
                    square[*gg -1] = X;
                    system("cls");
                    board();
					printf("turn: %i", turn);
					printf("\nplayer: 1");
                }
                else
                {
                    square[*gg -1] = O;
                    system("cls");
                    board();
					printf("turn: %i", turn);
					printf("\nplayer: 2");
                }

                turn++;
				Sleep(1500);
            }
			

        }


        if (turn % 2 == 1)
        {
            for(x=0; winner2[x] != '\0'; x++)
				{
					printf("%c",winner2[x]);
					for(y=0; y<=6666666; y++)
					{
					}
				}
        }
        else
        {
            for(x=0; winner1[x] != '\0'; x++)
				{
					printf("%c",winner1[x]);
					for(y=0; y<=6666666; y++)
					{
					}
				}
        }

        printf("\n 		       Play again?");
        printf("\n     Type 0 to quit or any other number to play again: ");
        scanf("%i", & playchoice);

        if(playchoice == 0)
        {
            return 0;

        }
        else
        {
            goto game;

        }

    }



// Build board. Replace C values with value in square array.
void board() {
    printf("  +--------------------------------------------------------+\n");
    printf("  | (1-9) Number Selection, (44) Undo Move, (66) Redo Move |\n");
    printf("  +--------------------------------------------------------+");
    printf("\n\n\n                  NOUGHTS AND CROSSES");
    printf("\n            PLAYER ONE (X) v (O) PLAYER TWO\n\n");

    printf("                     +---+---+---+\n");

    printf("                     | %c | %c | %c | \n", square[0], square[1], square[2]);

    printf("                     +---+---+---+\n");

    printf("                     | %c | %c | %c | \n", square[3], square[4], square[5]);

    printf("                     +---+---+---+\n");

    printf("                     | %c | %c | %c | \n", square[6], square[7], square[8]);

    printf("                     +---+---+---+\n");

}

// Check win checks if 3 values in a row are the same.
int checkwin() {
    if (square[0] == square[1] && square[1] == square[2])
        return 1;

    else if (square[3] == square[4] && square[4] == square[5])
        return 1;

    else if (square[6] == square[7] && square[7] == square[8])
        return 1;

    else if (square[0] == square[3] && square[3] == square[6])
        return 1;

    else if (square[1] == square[4] && square[4] == square[7])
        return 1;

    else if (square[2] == square[5] && square[5] == square[8])
        return 1;

    else if (square[0] == square[4] && square[4] == square[8])
        return 1;

    else if (square[2] == square[4] && square[4] == square[6])
        return 1;

    else if (square[0] != '1' && square[1] != '2' && square[2] != '3' &&
             square[3] != '4' && square[4] != '5' && square[5] != '6' && square[6] !=
             '7' && square[7] != '8' && square[8] != '9')
        return 0;
    else
        return -1;
}

// Checks if number is valid aka 1-9 or 66 or 44
int validno()
{
    if (choice < 1 || choice > 9)
    {
        if (choice == 44 && turn == 1)
        {
            return 1;
        }

        if (choice == 44 && turn > 1)
        {
            return 0;
        }

        if (choice == 66)
        {
            return 0;
        }

        return 1;
    }
    else
    {
        return 0;
    }
}


// Resets all values for board, as well as values that need reset for game to work.

void reset()
{
    square[0] = '1';
    square[1] = '2';
    square[2] = '3';
    square[3] = '4';
    square[4] = '5';
    square[5] = '6';
    square[6] = '7';
    square[7] = '8';
    square[8] = '9';

    turn = 1;

    i = -1;

    v = 0;

    choice = 0;

    stacknumber = 0;

    casenumber = 1;

    playchoice = 0;
}
