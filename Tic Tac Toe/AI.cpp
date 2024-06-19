#include "AI.h"
#include <vector>
using namespace std;

int AI::minimax(Board board, bool isMaximizing, int& aiChoice)
{
	if (board.checkWin('X'))
		return -1;
	else if (board.checkWin('O'))
		return 1;
	else if (board.checkDraw())
		return 0;

	
	vector<int> scores, moves;
	if (isMaximizing)
	{
		for (int i = 1; i <= 9; i++)
		{
			Board newBoard = board;
			if (newBoard.makeMove(i, 'O'))
			{
				scores.push_back(minimax(newBoard, !isMaximizing, aiChoice));
				moves.push_back(i);
			}
		}
	}
	else
	{
		for (int i = 1; i <= 9; i++)
		{
			Board newBoard = board;
			if (newBoard.makeMove(i, 'X'))
			{
				scores.push_back(minimax(newBoard, !isMaximizing, aiChoice));
				moves.push_back(i);
			}
		}
	}

	int maxMinElement; 
	if (isMaximizing)
	{
		maxMinElement = -2; // values in scores can either be -1, 0, or -1 so -2 is less than all of them
		for (int i = 0; i < scores.size(); i++)
		{
			if (scores[i] > maxMinElement)
			{
				maxMinElement = scores[i];
				aiChoice = moves[i];
			}
		}
	}
	else
	{
		maxMinElement = 2; // values in scores can either be -1, 0, or 1, so 2 is greater than all of them
		for (int i = 0; i < scores.size(); i++)
		{
			if (scores[i] < maxMinElement)
			{
				maxMinElement = scores[i];
				aiChoice = moves[i];
			}
		}
	}
	return maxMinElement;
}