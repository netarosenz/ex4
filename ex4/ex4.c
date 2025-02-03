/******************
Name: Neta Rosenzweig
ID: 323885582
Assignment: ex.4
*******************/
#include <stdio.h>
#include <string.h>
#define NUM_OF_HUMAN_PYRAMID_ROWS 5
#define NUM_OF_HUMAN_PYRAMID_COLUMNS 5
#define MAX_SIZE_OF_BOARD 20
#define ASCII_TAB 128
#define MAX_CROSSWORD_SIZE 30
#define MAX_SLOTS 100
#define MAX_WORD_LENGTH 15
#define MAX_WORDS 100

//Struct for task 4
typedef struct {
    char queens;
    char region;
} Cell;

//Struct for task 5
typedef struct {
    int row;
    int column;
    int length;
    char direction;
} Slot;

void task1_robot_paths();
void task2_human_pyramid();
void task3_parenthesis_validator();
void task4_queens_battle();
int placeQueenInRow(Cell board[MAX_SIZE_OF_BOARD][MAX_SIZE_OF_BOARD], int size, int row);
void task5_crossword_generator();

int main()
{
    int task = -1;
    do
    {
        printf("Choose an option:\n"
               "1. Robot Paths\n"
               "2. The Human Pyramid\n"
               "3. Parenthesis Validation\n"
               "4. Queens Battle\n"
               "5. Crossword Generator\n"
               "6. Exit\n");

        if (scanf("%d", &task))
        {
            switch (task)
            {
            case 6:
                printf("Goodbye!\n");
                break;
            case 1:
                task1_robot_paths();
                break;
            case 2:
                task2_human_pyramid();
                break;
            case 3:
                task3_parenthesis_validator();
                break;
            case 4:
                task4_queens_battle();
                break;
            case 5:
                task5_crossword_generator();
                break;
            default:
                printf("Please choose a task number from the list.\n");
                break;
            }
        }
        else
        {
            scanf("%*s");
        }

    } while (task != 6);
}
//Recursive function to calculate the number of paths to (0,0)
int pathBack(int column, int row) {
    //Defining the limits of the grid
    //If the robot goes out of grid limits, there are no paths
    if (column < 0 || row < 0) {
        return 0;
    }
    //If the robot reaches (0,0), there is exactly 1 path
    if (column == 0 && row == 0) {
        return 1;
    }
    //Sum the number of paths by moving left and moving down
    return pathBack(column - 1, row) + pathBack(column, row - 1);
}
//Function to solve task 1
void task1_robot_paths() {
    int column;
    int row;
    printf("Please enter the coordinates of the robot (column, row):\n");
    scanf("%d %d", &column, &row);
    if (column < 0 || row < 0) {
        printf("The total number of paths the robot can take to reach home is: 0\n");
    }
    else {
        //Calling the recursive function "pathBack" to calculate the total paths and print it
        printf("The total number of paths the robot can take to reach home is: %d\n", pathBack(column, row));
    }
}
//Recursive function to calculate the total weight load on each cheerleader
float calculateSumWeight(int row, int column, float weights[NUM_OF_HUMAN_PYRAMID_ROWS][NUM_OF_HUMAN_PYRAMID_COLUMNS]) {
    //The limits of the array
    if (row < 0 || column < 0) {
        return 0;
    }
    //The base case
    if (row == 0 && column == 0) {
        return weights[0][0];
    }
    //The leftmost person in each row only supports those to their right and above
    if(column == 0) {
        return weights[row][column] + 0.5 * calculateSumWeight(row - 1, column, weights);
    }
    //The rightmost person in each row only supports those to their left and above
    if(row == column) {
        return weights[row][column] + 0.5 * calculateSumWeight(row - 1, column - 1, weights);
    }
    //Calculating the weight each side
    float weightLeft = calculateSumWeight(row - 1, column - 1, weights);
    float weightRight = calculateSumWeight(row - 1, column, weights);
    //The recursive function returns the value it calculated
    return weights[row][column] + 0.5 * (weightLeft + weightRight);
}
//Function to solve task 2
void task2_human_pyramid() {
    //An array that stores the values of the weights entered by the user
    float weights[NUM_OF_HUMAN_PYRAMID_ROWS][NUM_OF_HUMAN_PYRAMID_COLUMNS] ={0};
    printf("Please enter the weights of the cheerleaders:\n");
    //Loop for rows
    for(int i = 0; i < NUM_OF_HUMAN_PYRAMID_ROWS; i++) {
        //Loop ror columns
        for(int j = 0; j <= i; j++) {
            //Read the specific value according row and column
            scanf("%f", &weights[i][j]);
            //Weight can't be negative
            if(weights[i][j] < 0) {
                printf("Negative weights are not supported.\n");
                return;
            }
        }
    }
    printf("The total weight on each cheerleader is:\n");
    //Loop for rows
    for(int i = 0; i < NUM_OF_HUMAN_PYRAMID_ROWS; i++) {
        //Loop ror columns
        for(int j = 0; j <= i; j++) {
            //Calling the recursive function
            float totalWeight = calculateSumWeight(i, j, weights);
            printf("%.2f ", totalWeight);
        }
        printf("\n");
    }
}
//Function to check if the char is parenthesis
int isParenthesis(char parenthesis) {
    switch (parenthesis) {
        case '(':
        case '[':
        case '{':
        case '<':
        case ')':
        case ']':
        case '}':
        case '>':
            return 1;
        //If the char isn't parenthesis the check "failed"
        default:
            return 0;
    }
}
//Function that find the match for each type of parenthesis
char matchParenthesis(char openParen) {
    switch (openParen) {
        case '(':
            return ')';
        case '[':
            return ']';
        case '{':
            return '}';
        case '<':
            return '>';
        default:
            return '\0';
    }
}
//Recursive function to check if the parenthesis in the string are balanced
int isClosed(char expectedCloser) {
    char currentChar;
    //Read a single char from the input and store it
    int result = scanf("%c", &currentChar);
    //If it's the end of the input or newline
    if(result != 1 || currentChar == '\n') {
        //Not expecting for any more closing parentheses
        return expectedCloser == '\0';
    }
    //If found expected closing parenthesis
    if(currentChar == expectedCloser) {
        //Found the closing parenthesis we expected for
        return 1;
    }
    //If the char isn't a parenthesis, skip on it
    if(!isParenthesis(currentChar)) {
        //If it's not a parenthesis, ignore and keep checking the other chars
        return isClosed(expectedCloser);
    }
    //Find matching closing parenthesis
    char closer = matchParenthesis(currentChar);
    //If this is a closing parenthesis
    if(closer == '\0') {
        //If this closing parenthesis matches that we expected
        if(currentChar == expectedCloser) {
            //There is a match
            return 1;
        }
        //Invalid closing parenthesis found
        //Skip rest of line
        scanf("%*[^\n]");
        //Skip newline
        scanf("%*c");
        //Invalid closing parenthesis
        return 0;
    }
    //Check that the parentheses are properly closed
    return isClosed(closer) && isClosed(expectedCloser);
}
//Function to solve task 3
void task3_parenthesis_validator() {
    printf("Please enter a term for validation:\n");
    //Skip newline
    scanf("%*c");
    //Check if balanced, starting with no expected closer
    if(isClosed('\0')) {
        printf("The parentheses are balanced correctly.\n");
    }
    //If the isn't balanced, print a message
    else {
        printf("The parentheses are not balanced correctly.\n");
    }
}
//Function that check if there is a queen in the rows
int isXInTheRow(Cell board[MAX_SIZE_OF_BOARD][MAX_SIZE_OF_BOARD], int size, int row, int col) {
    //All columns in the row checked and there is no queen in this row
    if (col >= size) {
        //No queen in this row
        return 1;
    }
    //The row is not available
    if (board[row][col].queens == 'X') {
        //There is queen in this row
        return 0;
    }
    //If there is no queen in this column, move to the next column
    return isXInTheRow(board, size, row, col + 1);
}
//Function that check if there is a queen in the columns
int isXInTheColumn(Cell board[MAX_SIZE_OF_BOARD][MAX_SIZE_OF_BOARD], int size, int row, int col) {
    //All rows in the column checked and there is no queen in this column
    if (row >= size) {
        //No queen in this column
        return 1;
    }
    //The column is not available
    if (board[row][col].queens == 'X') {
        return 0;
    }
    //If there is no queen in this row, move to the next row
    return isXInTheColumn(board, size, row + 1, col);
}
//Function that check if there is a queen that threatening on another optional queen in the diagonals
int isXInTheDiagonals(Cell board[MAX_SIZE_OF_BOARD][MAX_SIZE_OF_BOARD], int size, int row, int col) {
    //Check upper left
    if (row - 1 >= 0 && col - 1 >= 0 && board[row - 1][col - 1].queens == 'X') {
        return 0;
    }
    //Check upper right
    if (row - 1 >= 0 && col + 1 < size && board[row - 1][col + 1].queens == 'X') {
        return 0;
    }
    //Check down left
    if (row + 1 < size && col - 1 >= 0 && board[row + 1][col - 1].queens == 'X') {
        return 0;
    }
    //Check down right
    if (row + 1 < size && col + 1 < size && board[row + 1][col + 1].queens == 'X') {
        return 0;
    }
    //There is no queens that threatening on another optional queen in the diagonals
    return 1;
}
//Function that check if there is a queen in the regions that the user inputed
int isXInTheRegion(Cell board[MAX_SIZE_OF_BOARD][MAX_SIZE_OF_BOARD], int size, int row, int col, char regionChar) {
    //Check all the rows
    if (row >= size) {
        //No queens in this region
        return 1;
    }
    //Check all the columns in the row
    if (col >= size) {
        //Continue to the next row
        return isXInTheRegion(board, size, row + 1, 0, regionChar);
    }
    //Check if the cell belongs to a region
    if(board[row][col].region == regionChar) {
        if(board[row][col].queens == 'X') {
            //There is another queen in this region
            return 0;
        }
    }
    //Continue checking the next column
    return isXInTheRegion(board, size, row, col + 1, regionChar);
}
//Function that checks if a queen can be placed in a specific column
int placeQueenInColumn(Cell board[MAX_SIZE_OF_BOARD][MAX_SIZE_OF_BOARD], int size, int row, int col) {
    //No available columns in the row
    if (col >= size) {
        //There is queen in this row
        return 0;
    }
    //Check if possible to place a queen according to the conditions: row, column, diagonals, region
    if (isXInTheRow(board, size, row, 0) &&
        isXInTheColumn(board, size, 0, col) &&
        isXInTheDiagonals(board, size, row, col)&&
        isXInTheRegion(board, size, 0, 0, board[row][col].region)) {
        //If all conditions are happen, place a queen in the current cell
        board[row][col].queens = 'X';
        //Move to the next row and try to place a queen
        if (placeQueenInRow(board, size, row + 1)) {
            //Solution found
            return 1;
        }
        //If there is no solution, remove the queen and backtrack
        board[row][col].queens = '*';
        }
    //Move to check the next column
    return placeQueenInColumn(board, size, row, col + 1);
}
//Function that remove a queen from its place on a specific row during the backtracking
int removeQueenFromRow(Cell board[MAX_SIZE_OF_BOARD][MAX_SIZE_OF_BOARD], int size, int row, int col) {
    //If there is no queen to remove in the row
    if (col >= size) {
        //No removing
        return 0;
    }
    //If there is a queen in this column to remove
    if (board[row][col].queens == 'X') {
        //delete X and place *
        board[row][col].queens = '*';
        //The queen removed
        return 1;
    }
    //Move to check the next column
    return removeQueenFromRow(board, size, row, col + 1);
}
//Function that place the queens row by row according to the conditions
int placeQueenInRow(Cell board[MAX_SIZE_OF_BOARD][MAX_SIZE_OF_BOARD], int size, int row) {
    //If all the queens placed in the right places in all the rows
    if (row >= size) {
        //There is solution
        return 1;
    }
    //Try to place a queen in this row, starting from column 0
    return placeQueenInColumn(board, size, row, 0);
}
//Function that print the total board
void printQueensSolution(Cell board[MAX_SIZE_OF_BOARD][MAX_SIZE_OF_BOARD], int size) {
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            printf("%c ", board[row][col].queens);
            }
        printf("\n");
    }
}
//Function that decide if there is or there isn't solution for the puzzle
int solveThePuzzle(Cell board[MAX_SIZE_OF_BOARD][MAX_SIZE_OF_BOARD], int size) {
    //Check if there is solution by the function 'placeQueenInRow' from the first row
    if (placeQueenInRow(board, size, 0)) {
        //If there is solution, print it by the function 'printSolution'
        printf("Solution:\n");
        printQueensSolution(board, size);
        //Sign that there is solution
        return 1;
    }
    //If there is no solution, let the user know
    printf("This puzzle cannot be solved.\n");
    //Sign that there is no solution
    return 0;
}
//Function to initialize the board
void initializeBoard(Cell board[MAX_SIZE_OF_BOARD][MAX_SIZE_OF_BOARD],int size,int row,int col) {
    //Check all the rows
    if(row >= size) {
        //All the rows checked
        return;
    }
    //Empty cell presented bo *
    board[row][col].queens = '*';
    //Check all the columns
    if(col >= size) {
        //Move to the first column in the next row
        initializeBoard(board, size, row+1, 0);
    }
    else {
        //Move to the next column
        initializeBoard(board, size, row, col+1);
    }
}
//Function to solve task 4
void task4_queens_battle() {
    int size;
    printf("Please enter the board dimensions:\n");
    //Read the size
    scanf("%d", &size);
    //Check the board dimensions
    if (size <= 0 || size > MAX_SIZE_OF_BOARD) {
        return;
    }
    Cell board[MAX_SIZE_OF_BOARD][MAX_SIZE_OF_BOARD] = {0};
    //Initializing the board
    initializeBoard(board, size, 0, 0);
    //Input for the regions
    printf("Please enter a %d*%d puzzle board:\n", size, size);
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            //Read the cell for the regions
            scanf(" %c", &board[row][col].region);
        }
    }
    //Call to the function 'solveThePuzzle' and start the checks for the solution
    solveThePuzzle(board, size);
}
//Recursive function to place word in the crossword
int placeWordOnGrid(char word[MAX_WORD_LENGTH + 1], Slot currentSlot,
    char grid[MAX_CROSSWORD_SIZE][MAX_CROSSWORD_SIZE], int charPlace) {
    //Base case: If we finished to place all the letters in the word
    if (charPlace == currentSlot.length) {
        return 1;
    }
    //Store the real char in the grid
    char realChar = grid[currentSlot.row][currentSlot.column];
    //Place the current letter of the word in the current cell in the grid
    grid[currentSlot.row][currentSlot.column] = word[charPlace];
    //If the direction is horizontal, move to the next column
    if(currentSlot.direction == 'H') {
        currentSlot.column++;
    }
    //The direction is vertical, move to the next row
    else {
        currentSlot.row++;
    }
    //Recursive call to place the next letter in the current word
    if(placeWordOnGrid(word, currentSlot, grid, charPlace + 1)) {
        //Word has placed
        return 1;
    }
    //Backtracking: remove the slot and backtrack according the direction
    if(currentSlot.direction == 'H') {
        //backtrack for horizontal
        currentSlot.column--;
    }
    else {
        //backtrack for vertical
        currentSlot.row--;
    }
    //initialize the grid for '#'
    grid[currentSlot.row][currentSlot.column] = '#';
    grid[currentSlot.row][currentSlot.column] = realChar;
    //Can't place the word
    return 0;
}
//Recursive function that remove words from the grid
int removeWordFromGrid(char word[MAX_WORD_LENGTH + 1], Slot currentSlot,
    char grid[MAX_CROSSWORD_SIZE][MAX_CROSSWORD_SIZE], char charPlace) {
    //Base case: if we finished to remove all the words from the grid
    if (charPlace == currentSlot.length) {
        return 1;
    }
    //Remove the current letter from the grid
    grid[currentSlot.row][currentSlot.column] = '#';
    //Move to the next cell of the grid according the direction
    if(currentSlot.direction == 'H') {
        //Horizontal
        currentSlot.column++;
    }
    else {
        //Vertical
        currentSlot.row++;
    }
    //Recursive call to remove the next letter
    return removeWordFromGrid(word, currentSlot, grid, charPlace + 1);
}
//Function that print the crossword
void printTheCrossword(int size, char grid[MAX_CROSSWORD_SIZE][MAX_CROSSWORD_SIZE]) {
    //Loop for each row of the grid
    for(int i = 0; i < size; i++) {
        //Loop for each column of the grid
        for(int j = 0; j < size; j++) {
            //Print the current cell by the format
            printf("| %c ", grid[i][j]);
        }
        //Ending row
        printf("|\n");
        }
    }
//Function that check if it's possible to place a word in slot
int properSlot(char word[MAX_WORD_LENGTH + 1], Slot currentSlot, char grid[MAX_CROSSWORD_SIZE][MAX_CROSSWORD_SIZE]) {
    //Start of the row
    int row = currentSlot.row;
    //Start of the column
    int column = currentSlot.column;
    //Loop for each letter in the current word
    for(int i = 0; i < currentSlot.length; i++) {
        //If the cell isn't empty or if isn't proper to the current letter
        if(grid[row][column] != '#' && grid[row][column] != word[i]) {
            //Can't place the word
            return 0;
        }
        //Move to the next cell in the slot according the direction
        if(currentSlot.direction == 'H') {
            //Horizontal
            column++;
        }
        else {
            //Vertical
            row++;
        }
    }
    //Possible to place the word
    return 1;
}
//Function that trying to solve the crossword by backtracking
int solveTheCrossword(int size, int numOfSlots, int numOfWords, char dictionary[MAX_WORDS][MAX_WORD_LENGTH +1],
    Slot slots[MAX_SLOTS], char grid[MAX_CROSSWORD_SIZE][MAX_CROSSWORD_SIZE], int slotIndex, int wordIndex,
    int wordUsed[MAX_WORDS]) {
    //Base case: if we finished to fill all the slots
    if(slotIndex == numOfSlots) {
        //The crossword solved
        return 1;
    }
    //Base case: if we checked all the words and they are no proper
    if(wordIndex == numOfWords) {
        //No solution for the crossword
        return 0;
    }
    //The current slot
    Slot currentSlot = slots[slotIndex];
    //If the word fits to the current slot and we didn't use it yet
    if(!wordUsed[wordIndex] && (int)strlen(dictionary[wordIndex]) == currentSlot.length &&
        properSlot(dictionary[wordIndex], currentSlot, grid)) {
        //The word placed
        wordUsed[wordIndex] = 1;
        //The current place of the word
        placeWordOnGrid(dictionary[wordIndex], currentSlot, grid, 0);
        //Recursive call to the next slot
        if(solveTheCrossword(size, numOfSlots, numOfWords, dictionary, slots, grid,slotIndex +1, 0, wordUsed)) {
            //There is solution
            return 1;
        }
        //Backtracking: remove the word if there is no solution
        removeWordFromGrid(dictionary[wordIndex], currentSlot, grid, 0);
        //Unmark the word
        wordUsed[wordIndex] =0;
    }
    //Move to the next word in the dictionary
    return solveTheCrossword(size, numOfSlots, numOfWords, dictionary, slots, grid, slotIndex, wordIndex + 1,
        wordUsed);
}
//Function to solve task 5
void task5_crossword_generator() {
    //The size of the crossword grid
    int size;
    //The number of the slots in the crossword
    int numOfSlots;
    //The number of the words in the dictionary
    int numOfWords;
    //Array for the words in the dictionary. the +1 is for the null char at the end
    char dictionary[MAX_WORDS][MAX_WORD_LENGTH + 1];
    //Array for the slots in the grid
    Slot slots[MAX_SLOTS];
    //Array for the grid
    char grid[MAX_CROSSWORD_SIZE][MAX_CROSSWORD_SIZE];
    //Array that help us to track the used words
    int wordUsed[MAX_WORDS] = {0};
    printf("Please enter the dimensions of the crossword grid:\n");
    //Read the size of the crossword grid
    scanf("%d", &size);
    //Loop for initialize the grid
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            grid[i][j] = '#';
        }
    }
    printf("Please enter the number of slots in the crossword:\n");
    //Read the number of the slots in the crossword
    scanf("%d", &numOfSlots);
    printf("Please enter the details for each slot (Row, Column, Length, Direction):\n");
    //Check all the slots according the input
    for(int i = 0; i < numOfSlots; i++) {
        //Read the details of the slot
        scanf("%d %d %d %c", &slots[i].row, &slots[i].column, &slots[i].length, &slots[i].direction);
        }
    printf("Please enter the number of words in the dictionary:\n");
    //Read the number of the words in the dictionary
    scanf("%d", &numOfWords);
    //Check that there is enough words in the dictionary to solve the crossword
    while(numOfWords < numOfSlots) {
        printf("The dictionary must contain at least %d words. Please enter a valid dictionary size:\n",
            numOfSlots);
        scanf("%d", &numOfWords);
    }
    printf("Please enter the words for the dictionary:\n");
    //Loop for all the words in the dictionary
    for(int i = 0; i < numOfWords; i++) {
        //Read the words that inputed and store them in the proper cell
        scanf("%s", dictionary[i]);
    }
    //Crossword solution
    if(solveTheCrossword(size, numOfSlots, numOfWords, dictionary, slots, grid, 0, 0, wordUsed)) {
        //Print the solution
        printTheCrossword(size, grid);
    }
    else {
        //The solution failed
        printf("This crossword cannot be solved.\n");
    }
}




