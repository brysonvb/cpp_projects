#include <iostream>
#include <string>
#include <ctime>
#include <conio.h> // getch
using namespace std;

const int GRIDSIZE = 15;

void generateNeighborArray(int(&neighbors)[GRIDSIZE][GRIDSIZE], char grid[GRIDSIZE][GRIDSIZE]);

int main()
{
	char grid[GRIDSIZE][GRIDSIZE];
	int randomNum;
	char userInput;
	int gen = 1;

	srand(time(0));

	cout << "Welcome to Conway's Game of Life!" << endl << endl;
	cout << "Initial state:" << endl;
	for (int i = 0; i < GRIDSIZE; i++)
	{
		for (int j = 0; j < GRIDSIZE; j++)
		{
			grid[i][j] = (rand() % 2 == 0) ? ' ' : '*';
			cout << grid[i][j] << "\t";
		}
		cout << endl;
	}
	cout << "Press spacebar to start the simulation...";
	userInput = _getch();
	while (userInput != ' ')
		userInput = _getch();
	cout << endl << endl;

	int neighbors[GRIDSIZE][GRIDSIZE];

	while (userInput != 'q' && userInput != 'Q')
	{
		cout << "Generation " << gen << ":" << endl;
		for (int i = 0; i < GRIDSIZE; i++)
		{
			for (int j = 0; j < GRIDSIZE; j++)
				cout << grid[i][j] << "\t";
			cout << endl;
		}
		cout << endl;
		cout << "Press spacebar to continue to Generation 2, or \'q\' to quit... ";
		userInput = _getch();
		while (userInput != ' ' && userInput != 'q')
			userInput = _getch();
		cout << endl << endl;
		if (userInput == ' ')
		{
			generateNeighborArray(neighbors, grid);
			for (int i = 0; i < GRIDSIZE; i++)
			{
				for (int j = 0; j < GRIDSIZE; j++)
				{
					if (grid[i][j] == '*')
					{
						if (neighbors[i][j] < 2)
							grid[i][j] = ' ';
						if (neighbors[i][j] > 3)
							grid[i][j] = ' ';
					}
					else
						if (neighbors[i][j] == 3)
							grid[i][j] = '*';
				}
			}
		}
		gen++;
	}
}

void generateNeighborArray(int(&neighbors)[GRIDSIZE][GRIDSIZE], char grid[GRIDSIZE][GRIDSIZE])
{
	for (int i = 0; i < GRIDSIZE; i++)
		for (int j = 0; j < GRIDSIZE; j++)
			neighbors[i][j] = 0;
	for (int i = 1; i < GRIDSIZE - 1; i++)
	{
		for (int j = 1; j < GRIDSIZE - 1; j++)
		{
			for (int k = -1; k < 2; k++)
			{
				if (grid[i - 1][j + k] == '*')
					neighbors[i][j] += 1;
				if (grid[i][j + k] == '*')
					neighbors[i][j] += 1;
				if (grid[i + 1][j + k] == '*')
					neighbors[i][j] += 1;
			}
			if (grid[i][j] == '*')
				neighbors[i][j] -= 1; // neighbors [i][j] was included as a neighbor
		}
	}
	for (int i = 1; i < GRIDSIZE - 1; i++)
	{
		for (int k = -1; k < 2; k++)
		{
			if (grid[0][i + k] == '*')
				neighbors[0][i] += 1;
			if (grid[1][i + k] == '*')
				neighbors[0][i] += 1;
			if (grid[GRIDSIZE - 1][i + k] == '*')
				neighbors[GRIDSIZE - 1][i] += 1;
			if (grid[GRIDSIZE - 2][i + k] == '*')
				neighbors[GRIDSIZE - 1][i] += 1;
			if (grid[i + k][0] == '*')
				neighbors[i][0] += 1;
			if (grid[i + k][1] == '*')
				neighbors[i][0] += 1;
			if (grid[i + k][GRIDSIZE - 1] == '*')
				neighbors[i][GRIDSIZE - 1] += 1;
			if (grid[i + k][GRIDSIZE - 2] == '*')
				neighbors[i][GRIDSIZE - 1] += 1;
		}
		if (neighbors[0][i] == '*')
			neighbors[0][i] -= 1; // neighbors [0][i] was included as a neighbor
		if (neighbors[GRIDSIZE - 1][i] == '*')
			neighbors[GRIDSIZE - 1][i] -= 1; // neighbors [GRIDSIZE - 1][i] was included as a neighbor
		if (neighbors[i][0] == '*')
			neighbors[i][0] -= 1; // neighbors [i][0] was included as a neighbor
		if (neighbors[i][GRIDSIZE - 1] == '*')
			neighbors[i][GRIDSIZE - 1] -= 1; // neighbors [i][GRIDSIZE - 1] was included as a neighbor
	}
}