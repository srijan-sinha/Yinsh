#include "Board.h"

Board::Board () {

}

Board::Board (int size) {
	
	boardSize = size;
	initBoard(boardSize);
}

void Board::initBoard (int size) {
	
	int ** tempBoard = new int*[size+1];

	tempBoard[0] = new int[1];
	
	for (int i = 1; i < size + 1; i++) {
		tempBoard[i] = new int[6*i];
	}

	tempBoard[0][0] = 0;

	for (int i = 1; i < size + 1; i++) {
		for (int j = 0; j < 6*i; j++) {
			tempBoard[i][j] = 0;
		}
	}

	board = tempBoard;
}

int Board::getBoardSize () {
	return boardSize;
}

int Board::getNumRings () {
	return numRings;
}

int Board::getNumOppRings () {
	return numOppRings;
}

int Board::getNumDiscs () {
	return numDiscs;
}

int Board::getNumOppDiscs () {
	return numOppDiscs;
}

void Board::addRing (int colour, int hexagonNum, int position) {
	
	if(board[hexagonNum][position] == 0)
		board[hexagonNum][position] = colour;
	else{
		cout << "Error! Location already filled! Hexagon number: " <<  hexagonNum << " Point number: " << position << endl;
		cout << "Above error printed in Board.cpp: addRing." << endl;
	}
}

void Board::moveRing (int hexagon1, int position1, int hexagon2, int position2) {
	
}

void Board::removeRow (int hexagon1, int position1, int hexagon2, int position2) {

}

void Board::removeRing (int hexagonNum, int position) {
	
	if(board[hexagonNum][position] == 1 || board[hexgaonNum][position] == -1)
		board[hexagonNum][position] == 0;
	else
		cout << "Error! Ring not found for deletion! Hexagon number: " <<  hexagonNum << " Point number: " << position << endl;
		cout << "Above error printed in Board.cpp: removeRing." << endl;
	}
}

bool Board::checkBorder(int hexagonNum, int position, int bound) {
	if(hexagonNum != boardSize)
		return false;
	int low = boardSize * bound;
	int high = boardSize * (bound + 2);
	if(bound != 5) {
		if((position >= low) && (position <= high))
			return true;

		if((bound == 4) && (position == 0))
			return true;
		return false;
	}
	else {
		if(position >= low)
			return true;
		
		high = boardSize * 1;
		
		if((position >= 0) && (positon <= high))
			return true;
		return false;
	}
}

bool Board::hasNextUp(int hexagonNum, int position) {
	return checkBorder(hexagonNum, position, 5);
}

bool Board::hasNextDown(int hexagonNum, int position) {
	return checkBorder(hexagonNum, position, 2);
}

bool Board::hasNextUpRight(int hexagonNum, int position) {
	return checkBorder(hexagonNum, position, 0);
}

bool Board::hasNextUpLeft(int hexagonNum, int position) {
	return checkBorder(hexagonNum, position, 4);
}

bool Board::hasNextDownRight(int hexagonNum, int position) {
	return checkBorder(hexagonNum, position, 1);
}

bool Board::hasNextDownLeft(int hexagonNum, int position) {
	return checkBorder(hexagonNum, position, 3);
}

