#include "Board.h"

Board::Board () {

}

Board::Board (int size) {
	
	boardSize = size;
	initBoard(boardSize);
}

void Board::initBoard (int size) {
	
	int *** tempBoard = new int**[2*size+1];

	
	for (int i = 0; i < 2*size + 1; i++) {
		tempBoard[i] = new int*[2*size + 1];
	}

	for (int i = 0; i < 2*size + 1; i++) {
		for (int j = 0; j < 2*size + 1; j++) {
			tempBoard[i][j] = new int[2*size + 1];
		}
	}

	for(int i = 0; i < 2*size + 1; i++) {
		for(int j = 0; j < 2*size + 1; j++) {
			for(int k = 0; k < 2*size + 1; k++) {
				tempBoard[i][j][k] = 0;
			}
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

void Board::convertTo(int hexagonNum, int position, int v, int l, int r) {
	
	int segment = 0;

	if(hexagonNum == 0) { v = 0; l = 0; r = 0; }
	else {
		segment = position / hexagonNum;
		// if(position % hexagonNum == 0) {
		// 	if(segment == 0) { v = 0; l = hexagonNum; r = -1 * hexagonNum; }
		// 	else if(segment == 1) { v = hexagonNum; l = 0; r = -1 * hexagonNum; }
		// 	else if(segment == 2) { v = hexagonNum; l = -1 * hexagonNum; r = 0; }
		// 	else if(segment == 3) { v = 0; l = -1 * hexagonNum; r = hexagonNum; }
		// 	else if(segment == 4) { v = -1 * hexagonNum; l = 0; r = hexagonNum; }
		// 	else if(segment == 5) { v = -1 * hexagonNum; l = hexagonNum; r = 0; }
		// }
		
		if(segment == 0) { v = position % hexagonNum; l = hexagonNum - (position % hexagonNum); r = -1 * hexagonNum; }
		else if(segment == 1) { v = hexagonNum; l = -1 * (position % hexagonNum); r = -1 * (hexagonNum - (position % hexagonNum)); }
		else if(segment == 2) { v = hexagonNum - (position % hexagonNum); l = -1 * hexagonNum; r = position % hexagonNum; }
		else if(segment == 3) { v = -1 * (position % hexagonNum); l = -1 * (hexagonNum - (position % hexagonNum)); r = hexagonNum; }
		else if(segment == 4) { v = -1 * hexagonNum; l = position % hexagonNum; r = hexagonNum - (position % hexagonNum); }
		else if(segment == 5) { v = -1 * (hexagonNum - (position % hexagonNum)); l = hexagonNum; r = -1 * (position % hexagonNum); }
	}
}

void Board::convertBack(int v, int l, int r, int hexagonNum, int position) {
	hexagonNum = max(max(abs(v), abs(l)), ans(r));
	if(v == 0 && l == 0 && r == 0)
		position = 0;
	else {
		if(max == abs(v)) {
			if(v > 0)
				position = 2*hexagonNum + r; 
			else
				position = 4*hexagonNum + l;
		}
		else if(max == abs(r)) {
			if(r > 0)
				position = 3*hexagonNum - v;
			else
				position = v;
		}
		else {
			if(l > 0)
				position = 5*hexagonNum - r;
			else
				position = 3*hexgaonNum - v; 
		}
	}
}

void Board::addRing (int colour, int hexagonNum, int position) {
	
	int v, l, r = 0;
	convertTo(hexagonNum, position, v, l, r);

	if(board[v][l][r] == 0) {
		board[v][l][r] = colour;
		if(colour == 1)
			numRings++;
		else
			numOppRings++;
	}
	else{
		cout << "Error! Location already filled! Hexagon number: " <<  hexagonNum << " Point number: " << position << endl;
		cout << "Above error printed in Board.cpp: addRing." << endl;
	}
}

void Board::moveRing (int hexagon1, int position1, int hexagon2, int position2) {
	
	int v1, l1, r1, v2, l2, r2 = 0;
	convertTo(hexagon1, position1, v1, l1, r1);
	convertTo(hexagon2, position2, v2, l2, r2);

}

void Board::removeRow (int hexagon1, int position1, int hexagon2, int position2) {

}

void Board::removeRing (int hexagonNum, int position) {
	
	int v, l, r = 0;
	convertTo(hexagonNum, position, v, l, r);

	if(board[v][l][r] == 1 || board[v][l][r] == -1) {
		if(board[v][l][r] == 1)
			numRings--;
		else
			numOppRings--;
		board[v][l][r] == 0;
	}
	else
		cout << "Error! Ring not found for deletion! Hexagon number: " <<  hexagonNum << " Point number: " << position << endl;
		cout << "Above error printed in Board.cpp: removeRing." << endl;
	}
}


bool Board::hasNextUp(int v, int l , int r) {
	if(abs(l + 1) > boardSize || abs(r - 1) > boardSize)
		return false;
	return true;
}

bool Board::hasNextDown(int v, int l, int r) {
	if(abs(l - 1) > boardSize || abs(r + 1) > boardSize)
		return false;
	return true;
}

bool Board::hasNextUpRight(int v, int l , int r) {
	if(abs(v + 1) > boardSize || abs(r - 1) > boardSize)
		return false;
	return true;
}

bool Board::hasNextUpLeft(int v, int l , int r) {
	if(abs(v - 1) > boardSize || abs(l + 1) > boardSize)
		return false;
	return true;
}

bool Board::hasNextDownRight(int v, int l , int r) {
	if(abs(v + 1) > boardSize || abs(l - 1) > boardSize)
		return false;
	return true;
}

bool Board::hasNextDownLeft(int v, int l , int r) {
	if(abs(v - 1) > boardSize || abs(r + 1) > boardSize)
		return false;
	return true;
}

void Board::nextUp(int v, int l, int r) {
	l = l + 1;
	r = r - 1;
}

void Board::nextDown(int v, int l, int r) {
	l = l - 1;
	r = r + 1;
}

void Board::nextUpRight(int v, int l, int r) {
	v = v + 1;
	r = r - 1;
}

void Board::nextUpLeft(int v, int l, int r) {
	v = v - 1;
	l = l + 1;
}

void Board::nextDownRight(int v, int l, int r) {
	v = v + 1;
	l = l - 1;
}

void Board::nextDownLeft(int v, int l, int r) {
	v = v - 1;
	r = r + 1;
}