// THIS CODE WAS MADE ON DEV C++ AND WILL NOT RUN PROPERLY ON VSCODE
// made by Ali Rafay, Bilal Sarwar, Hadi Sohail on 29th April, 2024
// edited by Ali Rafay, Bilal Sarwar on 17th May, 2024
// edited by Hadi Sohail, Ali Rafay on 24th May, 2024

#include <stdio.h>
#include <conio.h> 
#include <stdlib.h> // for rand function
#include <stdbool.h> // for boolean type functions and variables
#include <windows.h> // to change the size of the ouput window
#include <string.h> // for string functions

#define SIZE 4 // constant size for tic-tac-toe board
#define MAX_LENGTH 50 // constant max length for strings

// struct to hold username and password of user
typedef struct {
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];
} Account;

// prototypes for functions defined below main function
void MaximizeOutputWindow(void);
void RestoreOutputWindow(void);
void registerAccount();
void login();
void updateScore(char username[], int change);
void initializeBoard();
void printBoard();
bool isBoardFull();
bool checkWinner(char player);
void userMove();
void aiMove();

// global variables
char board[SIZE][SIZE]; // tic-tac-toe board declaration
bool isAIStarting = true; // flag to alternate first move
int userScore = 0; // initial score of new user
char loggedInUser[MAX_LENGTH]; // variable of the logged in user, contains username string


// main function
int main()
{
    MaximizeOutputWindow(); // makes the output window full screen
    system("color f0"); // changes the output window color to white and font color to green
    int acc, game;

    printf("Welcome to Tic-Tac-Toe!\n\n");

    do
    {
    	printf("Do you want to register an account or login to an existing account?\n\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("\nEnter your choice (1 or 2): ");
        scanf("%d", &acc);
        getchar();

        if (acc != 1 && acc != 2) // if input is not 1 or 2
        	printf("\nERROR: Invalid input.\n\n"); // error is printed

    } while (acc != 1 && acc != 2); // do while loop for input validation

    // account registration
    if (acc == 1)
    {
    	system("cls"); // clears screen
        registerAccount(); // register account
        login(); // login account for extra security
    }

    // account login
    else
    {
    	system("cls"); // use conio.h header file to use clrscr(); function
        login(); // login to account
    }

    do
    {
        printf("\nDo you want to play a game of Tic-Tac-Toe? (0 for no, 1 for yes): ");
        scanf("%d", &game);

        if (game != 1 && game != 0) // if input is not 0 or 1
        	printf("\nERROR: Invalid input.\n"); // error is printed

    } while (game != 1 && game != 0); // do while loop for input validation

    // sentinel loop
    while (game != 0)
    {
        system("color f0"); // changes the background color of output window to white and font color to black
        system("cls"); // clears screen
        printf("Let's start the game!\n\n");
        printf("You are playing against an intelligent AI.\n");
        printf("You are 'X' and the AI is 'O'.\n");
        printf("\nEnter your moves by specifying row and column numbers (1-3) seperated by a space.\n");

        initializeBoard(); // initialises the tic-tac-toe board

        // alternates who makes the first move
        if (isAIStarting)
        {
            aiMove();
        }

        while (!isBoardFull())
        {
            printBoard(); // prints the tic-tac-toe board
            userMove(); // function to get user's move
            if (checkWinner('X')) // function to check if user has won
            {
                printBoard();
                printf("\nCongratulations! You win!\n"); // user's winning message
                updateScore(loggedInUser, 3); // increases score by 3 if won
                break;
            }
            aiMove(); // function to get AI's move
            if (checkWinner('O')) // function to check if AI has won
            {
                printBoard();
                printf("\nAI wins! Better luck next time.\n"); // AI's winning message
                updateScore(loggedInUser, -1); // decreases score by 1
                break;
            }
        }

        if (!checkWinner('X') && !checkWinner('O')) // condition: if neither user, nor AI has won
        {
            printBoard();
            printf("\nIt's a draw!\n"); // draw messafe and score remains the same
            
        }

        isAIStarting = !isAIStarting; // changes the boolean variable to alternate between first moves in successive games

        do { // loop repeats and game is restarted if 1 is input
            printf("\nDo you want to play another game of Tic-Tac-Toe? (0 for no, 1 for yes): ");
            scanf("%d", &game);

            if (game != 1 && game != 0) // if input is not 0 or 1
        		printf("\nERROR: Invalid input.\n"); // error is printed

        } while (game != 1 && game != 0); // do while loop for input validation
    }

    // the ending
    system("cls");
    printf("Thank you for your time. Goodbye!\n");
    printf("Press Enter to exit.");
    RestoreOutputWindow(); // to restore down the output window
    getchar(); // to pause the console window
}

// registration function
void registerAccount() 
{
    Account account; // create an instance of Account struct
    char fileUsername[MAX_LENGTH], filePassword[MAX_LENGTH]; // usernames and passwords which already exist in the file
    int fileScore; // scores which already exist in the file
    
	FILE *file = fopen("userdata.txt", "a");
	fclose(file);
	
    file = fopen("userdata.txt", "r"); // opens userdata.txt for reading mode
    printf("Register your account:\n\n");

    printf("Enter username: ");
    fgets(account.username, MAX_LENGTH, stdin); // takes input from user and stores it in username char array
    account.username[strcspn(account.username, "\n")] = 0; // removes \n from the end of the username

    if(file == NULL) // if file does not exist
    { 
        perror("ERROR: "); // error is printed
        exit(0); // program is exited
    }

    // to check if the username already exists
    while(fscanf(file, "%s %s %d", fileUsername, filePassword, &fileScore) != EOF) // scan username, password and score while the EOF is not reached
    { 
        if(strcmp(account.username, fileUsername) == 0) // if the username is already taken
        {
            printf("\nERROR: Username already exists.\n\n"); // error is printed
            fclose(file); // closes userdata.txt file for reading mode
                
            // to ask the user whether to register again or login
            int choice;
            do {
            printf("Do you want to register again or login?\n\n1.Register \n2.Login \n\nEnter your choice: ");
            scanf("%d", &choice);
            getchar(); // clear the newline character from the buffer
            if(choice == 1) 
			{
				system("cls");
                return registerAccount(); // register again
            } 
			else if(choice == 2) 
			{
                system("cls");
				return; // exits function and moves to login function
            } 
			else 
			{
				system("cls");
                printf("\nERROR: Invalid choice.\n\n");
                 
            }
            } while (choice!=1 && choice!=2); // do while loop for input validation
        }
	}
    fclose(file); // closes file

    // if username does not already exist
    file = fopen("userdata.txt", "a"); // opens userdata.txt file for appending
    if(file == NULL) // if file does not exist
    { 
        perror("ERROR: "); // error is printed
        exit(0); // function is exited
    }

    printf("Enter password: ");
    fgets(account.password, MAX_LENGTH, stdin); // takes input from user and stores it in password char array
    account.password[strcspn(account.password, "\n")] = 0; // removes \n character from the end of the string

    fprintf(file, "%s %s 0\n", account.username, account.password); // initial score is set to 0
    system("cls"); // screen is cleared
    printf("Registration successful!\n\n");
    fclose(file); // userdata.txt file for appending is closed
}

// login function
void login() 
{
    Account account; // create an instance of Account struct
    char fileUsername[MAX_LENGTH], filePassword[MAX_LENGTH]; // declaration of variables needed to be compared to login
    int fileScore; // scores stored in userdata.txt file
	do {
    FILE *file = fopen("userdata.txt", "r"); // userdata.txt file is opened for reading mode
    if(file == NULL) // if file does not exist
    { 
        perror("ERROR: "); // error is printed
        printf("Press Enter to Exit.");
        exit(0); // function is exited
    }

    printf("Login to your account:\n\n");

    printf("Enter username: ");
    fgets(account.username, MAX_LENGTH, stdin); // takes input from user and stores it in username char array
    account.username[strcspn(account.username, "\n")] = 0; // removes \n character from the end of the string

    printf("Enter password: ");
    fgets(account.password, MAX_LENGTH, stdin); // takes input from user and stores it in password char array
    account.password[strcspn(account.password, "\n")] = 0; // removes \n character from the end of the string

    // check if username and password match
    while(fscanf(file, "%s %s %d", fileUsername, filePassword, &fileScore) != EOF) // while loop to scan all usernames and passwords stored in userdata.txt
    { 
        if(strcmp(account.username, fileUsername) == 0 && strcmp(account.password, filePassword) == 0) // if both username and password match
        {
            strcpy(loggedInUser, account.username); // stores the username in loggedInUser variable to access it anywhere in the code
            system("cls"); // screen is cleared
             printf("Login successful!\n");
            printf("\nWelcome, %s. Your current score is %d.\n", loggedInUser, fileScore); // prints name and score
            fclose(file); // closes userdata.txt file for reading mode
            return; // returns control to main function
        }
    }
    system("cls");
    fclose(file); // closes userdata.txt file for reading mode
    printf("ERROR: Invalid username or password.\n\n"); // error is printed

	int choice;
	do {
    printf("Do you want to register an account or login again?\n\n1.Register \n2.Login \n\nEnter your choice: ");
    scanf("%d", &choice);
    getchar(); // clear the newline character from the buffer
    if(choice == 1) 
	{
        system("cls");
		return registerAccount(); // register account
    } 
	else if(choice == 2) 
	{
        system("cls");
        break;
    } 
	else 
	{
        system("cls");
		printf("ERROR: Invalid choice.\n\n");
         
    }
    } while (choice!=1 && choice!=2); // do while loop for input validation
} while (1);
}

void updateScore(char username[], int change) // first paramter takes username, second parameter takes change in score
{
    FILE *file = fopen("userdata.txt", "r+"); // opens userdata.txt file for reading and writing mode
    char fileUsername[MAX_LENGTH], filePassword[MAX_LENGTH], tempFile[MAX_LENGTH] = "temp.txt"; // char arrays to store the usernames and passwords stored in file and new txt file
    int fileScore; // stores scores stored in txt file
    FILE *temp = fopen(tempFile, "w"); // opens temp.txt file for writing mode

    if(file == NULL || temp == NULL) // if either file does not exist
	{
        perror("ERROR: "); // error is printed
        exit(0); // program is exited
    }

    while(fscanf(file, "%s %s %d", fileUsername, filePassword, &fileScore) != EOF) // scan username, password and score from file while EOF is not reached
	{
        if(strcmp(username, fileUsername) == 0) // if the usenrame passed as an argumment matches a username stored in file
		{
            fileScore += change; // update the score in file
            userScore = fileScore; // update the score in program
        }
        fprintf(temp, "%s %s %d\n", fileUsername, filePassword, fileScore); // prints every username, password and score from userdata.txt file in the temp.txt file
    }

    fclose(file); // closes userdata.txt file for reading and writing mode
    fclose(temp); // closes temp.txt file for writing mode

    remove("userdata.txt"); // removes the userdata.txt file from the directory or folder
    rename(tempFile, "userdata.txt"); // renames the temp.txt file to userdata.txt for later use

    printf("Your score is now %d.\n", userScore);
}

// function to initialize the board
void initializeBoard()
{
    for (int i = 1; i < SIZE; i++)
    {
        for (int j = 1; j < SIZE; j++)
        {
            board[i][j] = '-';      // initializes each element of 2D array to '-'
        }
    }
}

// function to print the board
void printBoard()
{
    printf("\n\t\t"); // newline and tab to center the board
    for (int i = 1; i < SIZE; i++)
    {
        for (int j = 1; j < SIZE; j++)
        {
            printf("%c ", board[i][j]);  // prints each element of 2D array
        }
        printf("\n\t\t"); // newline and tab to centre the board
    }
}

// function to check if the board is full
bool isBoardFull()
{
    for (int i = 1; i < SIZE; i++)
    {
        for (int j = 1; j < SIZE; j++)
        {
            if (board[i][j] == '-') // if any element of the 2D array is still '-', the board is not full
                return false;
        }
    }
    return true; // otherwise, it is full
}

// function to check if there is a winner
bool checkWinner(char player)
{
    // check rows and columns
    for (int i = 1; i < SIZE; i++)
    {   // if any row is occupied by the same character (X or O), the corresponding player (AI or user) has won
        if (board[i][1] == player && board[i][2] == player && board[i][3] == player)
            return true;
            // if any column is occupied by the same character (X or O), the corresponding player (AI or user) has won
        if (board[1][i] == player && board[2][i] == player && board[3][i] == player)
            return true;
    }
    // check diagonals
    // if the leading diagonal is occupied by the same character (X or O), the corresponding player (AI or user) has won
    if ((board[1][1] == player && board[2][2] == player && board[3][3] == player) ||
        (board[1][3] == player && board[2][2] == player && board[3][1] == player)) // if the other diagonal is occupied by the same character (X or O), the corresponding player (AI or user) has won
        return true;

    return false;  // otherwise, nobody has won and the game continues
}

// function to get user's move
void userMove()
{
    int row, col;
    printf("\nEnter your move (row and column, 1-3): ");
    scanf("%d %d", &row, &col);   // input for user's move

    if (row < 1 || row >= SIZE || col < 1 || col >= SIZE || board[row][col] != '-')
    {
        printf("\nERROR: Invalid move.\n");
        userMove(); // for input validation
    }
    else
        board[row][col] = 'X';  // the corresponding element of the 2D array is changed to X (user's symbol)
}

// Function for AI player's move
void aiMove()
{
    if (!isBoardFull())  // if board is not full
    {	
    	// checking winner move
        for (int i = 1; i < SIZE; i++)
        {
            for (int j = 1; j < SIZE; j++)
            {
                if (board[i][j] == '-')  // if the element of the 2D array is not occupied
                {
                    board[i][j] = 'O';  // it is occupied by the AI
                    if (checkWinner('O')) // function to check if the AI wins by occupying that element
                        return;  // if so, exit the function
                    board[i][j] = '-';  // otherwise, unoccupy that element and continue moving through the other elements
                }
            }
        }

       // if AI cannot have a winning move, check if AI needs to block user's winning move
        for (int i = 1; i < SIZE; i++)
        {
            for (int j = 1; j < SIZE; j++)
            {
                if (board[i][j] == '-')  // if the element of the 2D array is not occupied
                {
                    board[i][j] = 'X';   // it temporarily occupies it with the user's symbol
                    if (checkWinner('X')) // and checks if the user can win by occupying that element
                    {
                        board[i][j] = 'O';  // if so, AI occupies that element
                        return;
                    }
                    board[i][j] = '-';   // otherwise, leave it as is
                }
            }
        }

        // If neither winning nor blocking move possible, make a random move
        int row, col;
        do
        {
            row = rand() % SIZE +1;  // rand function to get a random row between 1 and 3
            col = rand() % SIZE +1;  // rand function to get a random column between 1 and 3
        } while (board[row][col] != '-'); // do while loop to make sure the element corresponding to that row and column are not occupied

        board[row][col] = 'O';  // occupy that element with AI's symbol (O)
    }
    else    // if board is full
        return;  // exit the function
}

// function to maximize the size of the window
void MaximizeOutputWindow(void)
{
    HWND consoleWindow = GetConsoleWindow(); // this gets the value Windows uses to identify your output window
    ShowWindow(consoleWindow, SW_MAXIMIZE);  // this mimics clicking on its' maximize button
}

// function to decrease the size of the ouput window
void RestoreOutputWindow(void)
{
    HWND consoleWindow = GetConsoleWindow(); //  this gets the value windows uses to identify your output window
    ShowWindow(consoleWindow, SW_RESTORE);   // clicks on its maximize for a second time, which puts it back to normal
}
