#include "Board.h"

Board::Board () {

}

Board::Board (int size) {

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
	else
		cout << "Error! Location already filled! Hexagon number: " <<  hexagonNum << " Point number: " << position << endl;
		cout << "Above error printed in Board.cpp: addRing." << endl;
}

void Board::moveRing (int hexagon1, int position1, int hexagon2, int position2) {
	
}

void Board::removeRow (int hexagon1, int position1, int hexagon2, int position2) {

}

void Board::removeRing (int hexagonNum, int position);