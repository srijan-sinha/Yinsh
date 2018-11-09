#include "createData.h"

createData::createData (int n, int m, int k, int l) {

	boardSize = n;
	maxRings = m;
	sequenceLength = k;
	ringsToWin = l;

}

void createData::initTranslateBoard () {

	// int size = boardSize * (boardSize + 1);
	// size = size / 2;
	// size = size * 6;
	// size++;
	int size = 2*boardSize + 1;
	int depth = 6;

	int *** tempTranslatedBoard = new int**[size];

	for (int i = 0; i < size; i++) {
		tempTranslatedBoard[i] = new int*[size];
	}

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			tempTranslatedBoard[i][j] = new int*[depth];
		}
	}

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			for (int k = 0; k < depth; k++) {
				tempTranslatedBoard[i][j][k] = 0;
			}
		}
	}

	translatedBoard = tempTranslatedBoard;

}

void createData::convertBack (int v, int l, int r, int& hexagonNum, int& position) {
	hexagonNum = max(max(abs(v), abs(l)), abs(r));
	if(v == 0 && l == 0 && r == 0)
		position = 0;
	else {
		if(hexagonNum == abs(v)) {
			if(v > 0)
				position = 2*hexagonNum + r; 
			else
				position = 4*hexagonNum + l;
		}
		else if(hexagonNum == abs(r)) {
			if(r > 0)
				position = 3*hexagonNum - v;
			else
				position = v;
		}
		else {
			if(l > 0)
				position = 5*hexagonNum - r;
			else
				position = 3*hexagonNum - v; 
		}
	}
}

bool createData::check (int v, int l, int r) 
{
	if(abs(v) > boardSize || abs(l) > boardSize || abs(r) > boardSize)
		return false;
	if ((abs(v) == boardSize && abs(l) == boardSize) || (abs(l) == boardSize && abs(r) == boardSize) || (abs(r) == boardSize && abs(v) == boardSize))
		return false;

	return true;
}

void createData::translate (int[][][] board, int turn) {

	int size = boardSize * (boardSize + 1);
	size = size / 2;
	size = size * 6;
	size++;

	// int h = 0;
	// int p = 0;
	int r = 0;

	for (int v = -1 * boardSize; v <= boardSize; v++) {
		for (int l = -1 * boardSize; l <= boardSize; l++) {
			r = (-1 * v) - l;
			if (check(v,l,r) {
				// convertBack(v, l, r, h, p);
				if (board[v + boardSize][l + boardSize][r + boardSize] == 0) {
					continue;
				}
				else if (board[v + boardSize][l + boardSize][r + boardSize] == 1) {
					translatedBoard[v + boardSize][l + boardSize][0] = 1; // Our ring
				}
				else if (board[v + boardSize][l + boardSize][r + boardSize] == 2) {
					translatedBoard[v + boardSize][l + boardSize][2] = 1; // Our disc
				}
				else if (board[v + boardSize][l + boardSize][r + boardSize] == -1) {
					translatedBoard[v + boardSize][l + boardSize][1] = 1; // Opp ring
				}
				else if (board[v + boardSize][l + boardSize][r + boardSize] == -2) {
					translatedBoard[v + boardSize][l + boardSize][3] = 1; // Opp disc
				}
			}
			else {
				translatedBoard[v + boardSize][l + boardSize][4] = 1;
			}

			if(turn == 1) {
				translatedBoard[v + boardSize][l + boardSize][5] = 1;
			}
		}
	}

}

int createData::index(int h, int p) {

	if (h == 0 && p == 0) {
		return 0;
	}
	else {
		return (h * (h-1) * 3) + 1 + p;
	}

}