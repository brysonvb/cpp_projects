#pragma once
#include <iostream>
#include "Board.h"
using namespace std;

class AI
{
public:
	int minimax(Board board, bool isMaximizing, int& aiChoice);
};