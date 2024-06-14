#include "Game.h"
#include "AI.h"

void Game::playGame()
{
	char keepPlaying = 'y';
	int playerChoice;
	bool validPlay;
	bool xWin, oWin, draw;
	while (keepPlaying == 'y' || keepPlaying == 'Y')
	{
		cout << endl << endl;
		cout << "=========================" << endl;
		cout << " Welcome to Tic Tac Toe! " << endl;
		cout << "=========================" << endl;

		cout << "You are \'X\' and the AI is \'O\'" << endl;
		cout << "To make a move, enter a number between 1 and 9 corresponding to the board position:" << endl;

		cout << " 1 | 2 | 3 " << endl;
		cout << "---+---+---" << endl;
		cout << " 4 | 5 | 6 " << endl;
		cout << "---+---+---" << endl;
		cout << " 7 | 8 | 9 " << endl << endl;

		xWin = oWin = draw = false;
		board.clearBoard();
		int aiChoice, num;
		bool randomBool;
		AI bot;
		while (!xWin && !oWin && !draw)
		{
			validPlay = false;
			board.displayBoard();
			while (!validPlay)
			{
				cout << "Your turn (X). Enter the position number: ";
				cin >> playerChoice;
				if (board.makeMove(playerChoice, 'X'))
					validPlay = true;
				else
					cout << "Invalid move! Please enter a number between 1 and 9 that corresponds to an empty position." << endl;
			}

			num = bot.minimax(board, true, aiChoice);
			randomBool = board.makeMove(aiChoice, 'O');

			xWin = board.checkWin('X');
			oWin = board.checkWin('O');
			draw = board.checkDraw();
		}
		cout << "=========================" << endl;
		cout << "        Game Over!       " << endl;
		cout << "=========================" << endl;
		if (xWin)
			cout << "You win! Congratulations!" << endl;
		else if (oWin)
			cout << "You lose! Better luck next time." << endl;
		else if (draw)
			cout << "It's a draw!" << endl;
		cout << endl << "Would you like to play again? (Y/N) ";
		cin >> keepPlaying;
	}
}