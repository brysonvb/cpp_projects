#include "Board.h"

Board::Board()
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            grid[i][j] = ' ';
}


void Board::displayBoard()
{
    for (int i = 0; i < 3; i++)
    {
        cout << " ";
        for (int j = 0; j < 3; j++)
        {
            if (j != 2)
                cout << grid[i][j] << " | ";
            else
                cout << grid[i][j];
        }
        if (i != 2)
            cout << endl << "---+---+---" << endl;
    }
    cout << endl << endl;
}

bool Board::makeMove(int position, char player)
{
    int row = position / 3;
    int column = position % 3 - 1;
    if (grid[row][column] == ' ')
    {
        grid[row][column] = player;
        return true;
    }
    else
        return false;
}

bool Board::isFull()
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i][j] == ' ')
                return false;
    return true;
}

void Board::clearBoard()
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            grid[i][j] = ' ';
}

bool Board::checkWin(char player)
{
    for (int i = 0; i < 3; i++) // check rows and columns
    {
        if ((grid[i][0] == player && grid[i][1] == player && grid[i][2] == player) || (grid[0][i] == player && grid[1][i] == player && grid[2][i] == player))
            return true;
    }

    if (grid[0][0] == player && grid[1][1] == player && grid[2][2] == player) // check diagonal from top left to bottom right
        return true;
    if (grid[0][2] == player && grid[1][1] == player && grid[2][0] == player) // check diagonal from top right to bottom left
        return true;
    return false;
}

bool Board::checkDraw()
{
    if (isFull() && !(checkWin('X')) && !(checkWin('O')))
        return true;
    return false;
}