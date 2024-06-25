#include <iostream>
#include <string>
#include <ctime>
#include <conio.h> // getch
#include <fstream>
using namespace std;

const int GRIDSIZE = 15;

void generateNeighborArray(int(&neighbors)[GRIDSIZE][GRIDSIZE], char grid[GRIDSIZE][GRIDSIZE]);
void displayGrid(const char grid[GRIDSIZE][GRIDSIZE]);
void initializeGrid(char(&grid)[GRIDSIZE][GRIDSIZE]);
void saveFile(const char grid[GRIDSIZE][GRIDSIZE]);
void readFile(char(&grid)[GRIDSIZE][GRIDSIZE]);

int main()
{
	char grid[GRIDSIZE][GRIDSIZE];
	char userInput = ' ';
	int gen = 1;

	ifstream textFile;
	textFile.open("saveFile.txt");

	cout << "Welcome to Conway's Game of Life!" << endl << endl;
	if (textFile)
	{
		cout << "Would you like to start from your most recent save state? (y/n) ";
		while (userInput != 'Y' && userInput != 'y' && userInput != 'N' && userInput != 'n')
			userInput = _getch();

		if (userInput == 'Y' || userInput == 'y')
			readFile(grid);
		else
			initializeGrid(grid);
		cout << endl;
	}
	else
	{
		cout << "You currently have no previous save state. Start the simulation to create one!" << endl << endl;
		initializeGrid(grid);
	}

	cout << "Initial state:" << endl;
	displayGrid(grid);
			
	cout << "Press spacebar to start the simulation...";
	userInput = _getch();
	while (userInput != ' ')
		userInput = _getch();
	cout << endl << endl;


	int neighbors[GRIDSIZE][GRIDSIZE];

	while (userInput != 'q' && userInput != 'Q')
	{
		cout << "Generation " << gen << ":" << endl;
		displayGrid(grid);
		cout << endl;

		cout << "Press spacebar to continue to Generation " << gen + 1 << ", or \'q\' to quit... ";
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

	saveFile(grid);
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
	}

	// top left corner
	if (grid[0][1] == '*')
		neighbors[0][0] += 1;
	if (grid[1][1] == '*')
		neighbors[0][0] += 1;
	if (grid[1][0] == '*')
		neighbors[0][0] += 1;
	neighbors[0][0] += 1;

	// top right corner
	if (grid[0][GRIDSIZE - 2] == '*')
		neighbors[0][GRIDSIZE - 1] += 1;
	if (grid[1][GRIDSIZE - 1] == '*')
		neighbors[0][GRIDSIZE - 1] += 1;
	if (grid[1][GRIDSIZE - 2] == '*')
		neighbors[0][GRIDSIZE - 1] += 1;
	neighbors[0][GRIDSIZE - 1] += 1;

	// bottom left corner
	if (grid[GRIDSIZE - 2][0] == '*')
		neighbors[GRIDSIZE - 1][0] += 1;
	if (grid[GRIDSIZE - 2][1] == '*')
		neighbors[GRIDSIZE - 1][0] += 1;
	if (grid[GRIDSIZE - 1][1] == '*')
		neighbors[GRIDSIZE - 1][0] += 1;
	neighbors[GRIDSIZE - 1][0] += 1;

	// bottom right corner
	if (grid[GRIDSIZE - 1][GRIDSIZE - 2] == '*')
		neighbors[GRIDSIZE - 1][GRIDSIZE - 1] += 1;
	if (grid[GRIDSIZE - 2][GRIDSIZE - 2] == '*')
		neighbors[GRIDSIZE - 1][GRIDSIZE - 1] += 1;
	if (grid[GRIDSIZE - 2][GRIDSIZE - 1] == '*')
		neighbors[GRIDSIZE - 1][GRIDSIZE - 1] += 1;
	neighbors[GRIDSIZE - 1][GRIDSIZE - 1] += 1;

	for (int i = 0; i < GRIDSIZE; i++)
		for (int j = 0; j < GRIDSIZE; j++)
			if (grid[i][j] == '*')
				neighbors[i][j] -= 1;
}

void displayGrid(const char grid[GRIDSIZE][GRIDSIZE])
{
	for (int i = 0; i < GRIDSIZE; i++)
	{
		for (int j = 0; j < GRIDSIZE; j++)
			cout << grid[i][j] << "\t";
		cout << endl;
	}
}

void initializeGrid(char(&grid)[GRIDSIZE][GRIDSIZE])
{
	srand(time(0));

	for (int i = 0; i < GRIDSIZE; i++)
	{
		for (int j = 0; j < GRIDSIZE; j++)
			grid[i][j] = (rand() % 2 == 0) ? ' ' : '*';
	}
}

void saveFile(const char grid[GRIDSIZE][GRIDSIZE])
{
	ofstream output("saveFile.txt");

	for (int i = 0; i < GRIDSIZE; i++)
	{
		for (int j = 0; j < GRIDSIZE; j++)
		{
			if (grid[i][j] == ' ')
				output << "s" << " ";
			else
				output << grid[i][j] << " ";
		}
		output << endl;
	}
}

void readFile(char(&grid)[GRIDSIZE][GRIDSIZE])
{
	ifstream input("saveFile.txt");

	for (int i = 0; i < GRIDSIZE; i++)
	{
		for (int j = 0; j < GRIDSIZE; j++)
		{
			input >> grid[i][j];
			if (grid[i][j] == 's')
				grid[i][j] = ' ';
		}
	}
}