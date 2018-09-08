

















//////////////////////////////


// Major logical flaw, we need to set board[v + boardSize][l + boardSize][r + boardSize] etc.


//////////////////////////////




























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

void Board::convertTo(int& hexagonNum, int& position, int& v, int& l, int& r) {
	
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

void Board::convertBack(int& v, int& l, int& r, int& hexagonNum, int& position) {
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

void Board::addRing (int colour, int hexagonNum, int position) 
{
	
	int v, l, r = 0;
	convertTo(hexagonNum, position, v, l, r);

	if(board[v][l][r] == 0) 
	{
		board[v][l][r] = colour;
		if(colour == 1)
			numRings++;
		else
			numOppRings++;
	}
	else
	{
		cout << "Error! Location already filled! Hexagon number: " <<  hexagonNum << " Point number: " << position << endl;
		cout << "Above error printed in Board.cpp: addRing." << endl;
	}
}

void Board::moveRing (int hexagon1, int position1, int hexagon2, int position2) 
{
	//we dont check if the func is called by our player or opponent player
	//i.e opponent cannot move our ring and vice-versa
	int v1, l1, r1, v2, l2, r2 = 0;
	convertTo(hexagon1, position1, v1, l1, r1);
	convertTo(hexagon2, position2, v2, l2, r2);
	if(board[v2][l2][r2] == 0) 
	{
		//change the ring and add the initial marker
		board[v2][l2][r2] = board[v1][l1][r1];
		if (board[v1][l1][r1] == 1)
			board[v1][l1][r1] = 2;
		else
			board[v1][l1][r1] = -2;
		//flip all the markers
		if (v1 == v2)
		{
			int v = v1;
			bool correct = true;
			//check if valid row is being removed
			int l_start = min(l1,l2) ,l_end = max(l1,l2);
			for(int i=l_start+1; i<l_end; i++)
			{
				if (board[v][i][-v-i] == 1 || board[v][i][-v-i] == -1)
				{
					cout<<"Error! there is a ring between the given 2 points"<<endl;
					cout<< "Above error printed in Board.cpp: moveRing." << endl;
					correct = false;	
					break;
				}
			}
			if (correct)
			{
				//flip the row
				for(int i=l_start+1; i<l_end; i++)
					board[v][i][-v-i] = -board[v][i][-v-i];
			}
		}
		else if (l1 == l2)
		{
			int l = l1;
			bool correct = true;
			//check if valid row is being removed
			int v_start = min(v1,v2) ,v_end = max(v1,v2);
			for(int i=v_start+1; i<v_end; i++)
			{
				if (board[i][l][-l-i] == 1 || board[i][l][-l-i] != 1)
				{
					cout<<"Error! there is a ring between the given 2 points"<<endl;
					cout<< "Above error printed in Board.cpp: moveRing." << endl;
					correct = false;	
					break;
				}
			}
			if (correct)
			{
				//remove the row
				for(int i=v_start+1; i<v_end; i++)
					board[i][l][-l-i] = -board[i][l][-l-i];
			}
		}
		else if (r1 == r2)
		{
			int r = r1;
			bool correct = true;
			//check if valid row is being removed
			int l_start = min(l1,l2) ,l_end = max(l1,l2);
			for(int i=l_start+1; i<l_end; i++)
			{
				if (board[-r-i][i][r] == 1 || board[-r-i][i][r] == -1)
				{
					cout<<"Error! there is a ring between the given 2 points"<<endl;
					cout<< "Above error printed in Board.cpp: moveRing." << endl;
					correct = false;	
					break;
				}
			}
			if (correct)
			{
				//remove the row
				for(int i=l_start+1; i<l_end; i++)
					board[-r-i][i][v] = -board[-r-i][i][v];
			}
		}
		else
		{
			cout << "Error! Given points (" <<  hexagon1 << "," << position1 << ") and (" <<  hexagon2 << "," << position2 << ") are not on same line" << endl;
			cout << "Above error printed in Board.cpp: moveRing." << endl;
		}
	}
	else
	{
		cout << "Error! Cannot move ring at Hexagon number: " <<  hexagon1 << " Point number: " << position1 << " to a point at Hexagon number: " <<  hexagon2 << " Point number: " << position2 << endl;
		cout << "Above error printed in Board.cpp: moveRing." << endl;
	}

}

void Board::removeRow (int hexagon1, int position1, int hexagon2, int position2) 
{
	int v1, l1, r1, v2, l2, r2 = 0;
	convertTo(hexagon1, position1, v1, l1, r1);
	convertTo(hexagon2, position2, v2, l2, r2);
	if (v1 == v2)
	{
		int v = v1;
		int a = board[v][l1+1][-v-l1-1];
		bool correct = true;
		//check if valid row is being removed
		int l_start = min(l1,l2) ,l_end = max(l1,l2);
		for(int i=l_start+2; i<l_end; i++)
		{
			if (board[v][i][-v-i] != a && (a == 2 || a == -2))
			{
				cout<<"Error! the row to delete does not have all markers or all markers of same player"<<endl;
				cout<< "Above error printed in Board.cpp: removeRow." << endl;
				correct = false;	
				break;
			}
		}
		if (correct)
		{
			//remove the row
			for(int i=l_start+1; i<l_end; i++)
				board[v][i][-v-i] = 0;
		}
	}
	else if (l1 == l2)
	{
		int l = l1;
		int a = board[v1+1][l][-v1-l-1];
		bool correct = true;
		//check if valid row is being removed
		int v_start = min(v1,v2) ,v_end = max(v1,v2);
		for(int i=v_start+2; i<v_end; i++)
		{
			if (board[i][l][-l-i] != a && (a == 2 || a == -2))
			{
				cout<<"Error! the row to delete does not have all markers or all markers of same player"<<endl;
				cout<< "Above error printed in Board.cpp: removeRow." << endl;
				correct = false;	
				break;
			}
		}
		if (correct)
		{
			//remove the row
			for(int i=v_start+1; i<v_end; i++)
				board[i][l][-l-i] = 0;
		}
	}
	else if (r1 == r2)
	{
		int r = r1;
		int a = board[-r-l1-1][l1+1][r];
		bool correct = true;
		//check if valid row is being removed
		int l_start = min(l1,l2) ,l_end = max(l1,l2);
		for(int i=l_start+2; i<l_end; i++)
		{
			if (board[-r-i][i][r] != a && (a == 2 || a == -2))
			{
				cout<<"Error! the row to delete does not have all markers or all markers of same player"<<endl;
				cout<< "Above error printed in Board.cpp: removeRow." << endl;
				correct = false;	
				break;
			}
		}
		if (correct)
		{
			//remove the row
			for(int i=l_start+1; i<l_end; i++)
				board[-r-i][i][v] = 0;
		}
	}
	else
	{
		cout << "Error! Given points (" <<  hexagon1 << "," << position1 << ") and (" <<  hexagon2 << "," << position2 << ") are not on same line" << endl;
		cout << "Above error printed in Board.cpp: removeRow." << endl;	
	}

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
	{
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

void Board::nextUp(int& v, int& l, int& r) {
	l = l + 1;
	r = r - 1;
}

void Board::nextDown(int& v, int& l, int& r) {
	l = l - 1;
	r = r + 1;
}

void Board::nextUpRight(int& v, int& l, int& r) {
	v = v + 1;
	r = r - 1;
}

void Board::nextUpLeft(int& v, int& l, int& r) {
	v = v - 1;
	l = l + 1;
}

void Board::nextDownRight(int& v, int& l, int& r) {
	v = v + 1;
	l = l - 1;
}

void Board::nextDownLeft(int& v, int& l, int& r) {
	v = v - 1;
	r = r + 1;
}