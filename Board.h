#pragma once
#include <iostream>
using namespace std;

class Board
{
public:
    char grid[3][3];
    
    Board();
    void displayBoard(); // Displays the current state of the board.
    bool makeMove(int position, char player); // Places the player's mark on the board if the position is valid.
    bool isFull(); // Checks if the board is full
    void clearBoard(); // clears the board
    bool checkWin(char player); // Checks if the specified player has won.
    bool checkDraw(); // Checks if the game is a draw.
};