//****************************

// Some points to be kept in mind for modification.

//****************************


//////////////////////////////

// Need to update numDiscs and numOppDiscs in moveRing and undoMoveRing.

//////////////////////////////


//****************************

// Caution :- Need to update numDiscs, num Opp Discs, numRings, numOppRings, ringsScored, oppRingsScored in the undo functions as well.

//****************************


//////////////////////////////

// Updation of ringV, ringL, ringR has to be done in all the functions where rings are added or moved or removed and undo functions as well.

//////////////////////////////


//****************************

// no check required in moveRing, so we can remove the for loop where you check if there is a ring on the path of movement. 
// Otherwise for a full check we also need to see if there is only one set of contiguous discs between start and end points.
// So let's better remove the check than implement a full check. We are allowed to assume that the moves received from the opponent are correct.
// I have commented it out.
// Aur jo flipping ke liye board[][][] = -board[][][] likha hai woh check kar lena ki -1 * board[][][] toh nahi likhna padega.

//****************************


//////////////////////////////

// Similarly for removeRow.

//////////////////////////////

//****************************

// Function implementations remaining in this file
// moveRingMoves full implementation left, generateMoveList half left.
//Major issue :- while generating moveRingMoves, how to check if one or more rows of 5 have been formed and that we need to further specify deletion of markers and ring after that. 

//****************************


#include "Board.h"

Board::Board () {

}

Board::Board (int n, int m, int k, int l) {
	
	boardSize = n;
	maxRings = m;
	SequenceLength = k;
	ringsToWin = l;

	numRings = 0;
	numOppRings = 0;

	ringsScored = 0;
	oppRingsScored = 0;

	numDiscs = 0;
	numOppDiscs = 0;
	
	ringV = new vector();
	ringL = new vector();
	ringR = new vector();

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

int Board::getMaxRings () {
	return maxRings;
}

int Board::getSequenceLength () {
	return sequenceLength;
}

int Board::getRingsToWin () {
	return ringsToWin;
}

int Board::getNumRings () {
	return numRings;
}

int Board::getNumOppRings () {
	return numOppRings;
}

int Board::getRingsScored () {
	return ringsScored;
}

int Board::getOppRingsScored () {
	return oppRingsScored;
}

int Board::getNumDiscs () {
	return numDiscs;
}

int Board::getNumOppDiscs () {
	return numOppDiscs;
}

void Board::convertTo (int& hexagonNum, int& position, int& v, int& l, int& r) {
	
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

void Board::convertBack (int& v, int& l, int& r, int& hexagonNum, int& position) {
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

	if(board[v + boardSize][l + boardSize][r + boardSize] == 0) 
	{
		board[v + boardSize][l + boardSize][r + boardSize] = colour;
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

void Board::undoAddRing(int hexagonNum, int position) {
	int v, l, r = 0;
	convertTo(hexagonNum, position, v, l, r);

	if(board[v + boardSize][l + boardSize][r + boardSize] != 1 || board[v + boardSize][l + boardSize][r + boardSize] != -1) {
		cout << "Error! Ring not found for removal! Hexagon number: " <<  hexagonNum << " Point number: " << position << endl;
		cout << "Above error printed in Board.cpp: undoAddRing." << endl;
	}
	else {
		if(board[v + boardSize][l + boardSize][r + boardSize] == 1)
			numRings--;
		else
			numOppRings--;
		board[v + boardSize][l + boardSize][r + boardSize] == 0;
	}
}

void Board::moveRing (int hexagon1, int position1, int hexagon2, int position2) {
	//we dont check if the func is called by our player or opponent player
	//i.e opponent cannot move our ring and vice-versa
	int v1, l1, r1, v2, l2, r2 = 0;
	convertTo(hexagon1, position1, v1, l1, r1);
	convertTo(hexagon2, position2, v2, l2, r2);

	if(board[v2 + boardSize][l2 + boardSize][r2 + boardSize] == 0) 
	{
		//change the ring and add the initial marker
		board[v2 + boardSize][l2 + boardSize][r2 + boardSize] = board[v1 + boardSize][l1 + boardSize][r1 + boardSize];
		
		if (board[v1 + boardSize][l1 + boardSize][r1 + boardSize] == 1)
			board[v1 + boardSize][l1 + boardSize][r1 + boardSize] = 2;
		else
			board[v1 + boardSize][l1 + boardSize][r1 + boardSize] = -2;
		
		//flip all the markers
		if (v1 == v2)
		{
			int v = v1;
			bool correct = true;
			//check if valid row is being removed
			int l_start = min(l1,l2) ,l_end = max(l1,l2);
			// for(int i=l_start+1; i<l_end; i++)
			// {
			// 	if (board[v][i][-v-i] == 1 || board[v][i][-v-i] == -1)
			// 	{
			// 		cout<<"Error! there is a ring between the given 2 points"<<endl;
			// 		cout<< "Above error printed in Board.cpp: moveRing." << endl;
			// 		correct = false;	
			// 		break;
			// 	}
			// }
			if (correct)
			{
				//flip the row
				for(int i=l_start+1; i<l_end; i++)
					board[v + boardSize][i + boardSize][-v-i + boardSize] = -board[v + boardSize][i + boardSize][-v-i + boardSize];
			}
		}
		else if (l1 == l2)
		{
			int l = l1;
			bool correct = true;
			//check if valid row is being removed
			int v_start = min(v1,v2) ,v_end = max(v1,v2);
			// for(int i=v_start+1; i<v_end; i++)
			// {
			// 	if (board[i][l][-l-i] == 1 || board[i][l][-l-i] != 1)
			// 	{
			// 		cout<<"Error! there is a ring between the given 2 points"<<endl;
			// 		cout<< "Above error printed in Board.cpp: moveRing." << endl;
			// 		correct = false;	
			// 		break;
			// 	}
			// }
			if (correct)
			{
				//flip the row
				for(int i=v_start+1; i<v_end; i++)
					board[i + boardSize][l + boardSize][-l-i + boardSize] = -board[i + boardSize][l + boardSize][-l-i + boardSize];
			}
		}
		else if (r1 == r2)
		{
			int r = r1;
			bool correct = true;
			//check if valid row is being removed
			int l_start = min(l1,l2) ,l_end = max(l1,l2);
			// for(int i=l_start+1; i<l_end; i++)
			// {
			// 	if (board[-r-i][i][r] == 1 || board[-r-i][i][r] == -1)
			// 	{
			// 		cout<<"Error! there is a ring between the given 2 points"<<endl;
			// 		cout<< "Above error printed in Board.cpp: moveRing." << endl;
			// 		correct = false;	
			// 		break;
			// 	}
			// }
			if (correct)
			{
				//flip the row
				for(int i=l_start+1; i<l_end; i++)
					board[-r-i + boardSize][i + boardSize][v + boardSize] = -board[-r-i + boardSize][i + boardSize][v + boardSize];
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

void Board::undoMoveRing(int hexagon1, int position1, int hexagon2, int position2) {
	//we dont check if the func is called by our player or opponent player
	//i.e opponent cannot move our ring and vice-versa
	int v1, l1, r1, v2, l2, r2 = 0;
	convertTo(hexagon1, position1, v1, l1, r1);
	convertTo(hexagon2, position2, v2, l2, r2);

	if(board[v2 + boardSize][l2 + boardSize][r2 + boardSize] == 1 || board[v2 + boardSize][l2 + boardSize][r2 + boardSize] == -1) 
	{
		//change the ring and add the initial marker
		board[v1 + boardSize][l1 + boardSize][r1 + boardSize] = board[v2 + boardSize][l2 + boardSize][r2 + boardSize];
		
		board[v2 + boardSize][l2 + boardSize][r2 + boardSize] = 0;
		
		//flip all the markers
		if (v1 == v2)
		{
			int v = v1;
			bool correct = true;
			//check if valid row is being removed
			int l_start = min(l1,l2) ,l_end = max(l1,l2);
			// for(int i=l_start+1; i<l_end; i++)
			// {
			// 	if (board[v][i][-v-i] == 1 || board[v][i][-v-i] == -1)
			// 	{
			// 		cout<<"Error! there is a ring between the given 2 points"<<endl;
			// 		cout<< "Above error printed in Board.cpp: moveRing." << endl;
			// 		correct = false;	
			// 		break;
			// 	}
			// }
			if (correct)
			{
				//flip the row
				for(int i=l_start+1; i<l_end; i++)
					board[v + boardSize][i + boardSize][-v-i + boardSize] = -board[v + boardSize][i + boardSize][-v-i + boardSize];
			}
		}
		else if (l1 == l2)
		{
			int l = l1;
			bool correct = true;
			//check if valid row is being removed
			int v_start = min(v1,v2) ,v_end = max(v1,v2);
			// for(int i=v_start+1; i<v_end; i++)
			// {
			// 	if (board[i][l][-l-i] == 1 || board[i][l][-l-i] != 1)
			// 	{
			// 		cout<<"Error! there is a ring between the given 2 points"<<endl;
			// 		cout<< "Above error printed in Board.cpp: moveRing." << endl;
			// 		correct = false;	
			// 		break;
			// 	}
			// }
			if (correct)
			{
				//flip the row
				for(int i=v_start+1; i<v_end; i++)
					board[i + boardSize][l + boardSize][-l-i + boardSize] = -board[i + boardSize][l + boardSize][-l-i + boardSize];
			}
		}
		else if (r1 == r2)
		{
			int r = r1;
			bool correct = true;
			//check if valid row is being removed
			int l_start = min(l1,l2) ,l_end = max(l1,l2);
			// for(int i=l_start+1; i<l_end; i++)
			// {
			// 	if (board[-r-i][i][r] == 1 || board[-r-i][i][r] == -1)
			// 	{
			// 		cout<<"Error! there is a ring between the given 2 points"<<endl;
			// 		cout<< "Above error printed in Board.cpp: moveRing." << endl;
			// 		correct = false;	
			// 		break;
			// 	}
			// }
			if (correct)
			{
				//flip the row
				for(int i=l_start+1; i<l_end; i++)
					board[-r-i + boardSize][i + boardSize][v + boardSize] = -board[-r-i + boardSize][i + boardSize][v + boardSize];
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

void Board::removeRow (int hexagon1, int position1, int hexagon2, int position2) {
	int v1, l1, r1, v2, l2, r2 = 0;
	convertTo(hexagon1, position1, v1, l1, r1);
	convertTo(hexagon2, position2, v2, l2, r2);

	if (v1 == v2)
	{
		int v = v1;
		int a = board[v + boardSize][l1 + boardSize][r1 + boardSize];
		bool correct = true;
		//check if valid row is being removed
		int l_start = min(l1,l2) ,l_end = max(l1,l2);
		// for(int i=l_start+1; i<=l_end; i++)
		// {
		// 	if (board[v][i][-v-i] != a && (a == 2 || a == -2))
		// 	{
		// 		cout<<"Error! the row to delete does not have all markers or all markers of same player"<<endl;
		// 		cout<< "Above error printed in Board.cpp: removeRow." << endl;
		// 		correct = false;	
		// 		break;
		// 	}
		// }
		if (correct)
		{
			//remove the row
			for(int i=l_start; i<=l_end; i++)
				board[v + boardSize][i + boardSize][-v-i + boardSize] = 0;
		}
		if(a == 2)
			numDiscs = numDiscs - 5;
		else
			numOppDiscs = numOppDiscs - 5;
	}
	else if (l1 == l2)
	{
		int l = l1;
		int a = board[v1 + boardSize][l + boardSize][-v1-l + boardSize];
		bool correct = true;
		//check if valid row is being removed
		int v_start = min(v1,v2) ,v_end = max(v1,v2);
		// for(int i=v_start+1; i<=v_end; i++)
		// {
		// 	if (board[i][l][-l-i] != a && (a == 2 || a == -2))
		// 	{
		// 		cout<<"Error! the row to delete does not have all markers or all markers of same player"<<endl;
		// 		cout<< "Above error printed in Board.cpp: removeRow." << endl;
		// 		correct = false;	
		// 		break;
		// 	}
		// }
		if (correct)
		{
			//remove the row
			for(int i=v_start; i<=v_end; i++)
				board[i + boardSize][l + boardSize][-l-i + boardSize] = 0;
		}
		if(a == 2)
			numDiscs = numDiscs - 5;
		else
			numOppDiscs = numOppDiscs - 5;
	}
	else if (r1 == r2)
	{
		int r = r1;
		int a = board[-r-l1 + boardSize][l1 + boardSize][r + boardSize];
		bool correct = true;
		//check if valid row is being removed
		int l_start = min(l1,l2) ,l_end = max(l1,l2);
		// for(int i=l_start+1; i<=l_end; i++)
		// {
		// 	if (board[-r-i][i][r] != a && (a == 2 || a == -2))
		// 	{
		// 		cout<<"Error! the row to delete does not have all markers or all markers of same player"<<endl;
		// 		cout<< "Above error printed in Board.cpp: removeRow." << endl;
		// 		correct = false;	
		// 		break;
		// 	}
		// }
		if (correct)
		{
			//remove the row
			for(int i=l_start; i<=l_end; i++)
				board[-r-i + boardSize][i + boardSize][v + boardSize] = 0;
		}
		if(a == 2)
			numDiscs = numDiscs - 5;
		else
			numOppDiscs = numOppDiscs - 5;
	}
	else
	{
		cout << "Error! Given points (" <<  hexagon1 << "," << position1 << ") and (" <<  hexagon2 << "," << position2 << ") are not on same line" << endl;
		cout << "Above error printed in Board.cpp: removeRow." << endl;	
	}

}

void Board::undoRemoveRow(int colour, int hexagon1, int position1, int hexagon2, int position2) {
	int v1, l1, r1, v2, l2, r2 = 0;
	convertTo(hexagon1, position1, v1, l1, r1);
	convertTo(hexagon2, position2, v2, l2, r2);

	if (v1 == v2)
	{
		int v = v1;
		bool correct = true;
		//check if valid row is being removed
		int l_start = min(l1,l2) ,l_end = max(l1,l2);
		// for(int i=l_start+1; i<=l_end; i++)
		// {
		// 	if (board[v][i][-v-i] != a && (a == 2 || a == -2))
		// 	{
		// 		cout<<"Error! the row to delete does not have all markers or all markers of same player"<<endl;
		// 		cout<< "Above error printed in Board.cpp: removeRow." << endl;
		// 		correct = false;	
		// 		break;
		// 	}
		// }
		if (correct)
		{
			//remove the row
			for(int i=l_start; i<=l_end; i++)
				board[v + boardSize][i + boardSize][-v-i + boardSize] = 2 * colour;
		}
		if(colour == 1)
			numDiscs = numDiscs + 5;
		else
			numOppDiscs = numOppDiscs + 5;
	}
	else if (l1 == l2)
	{
		int l = l1;
		bool correct = true;
		//check if valid row is being removed
		int v_start = min(v1,v2) ,v_end = max(v1,v2);
		// for(int i=v_start+1; i<=v_end; i++)
		// {
		// 	if (board[i][l][-l-i] != a && (a == 2 || a == -2))
		// 	{
		// 		cout<<"Error! the row to delete does not have all markers or all markers of same player"<<endl;
		// 		cout<< "Above error printed in Board.cpp: removeRow." << endl;
		// 		correct = false;	
		// 		break;
		// 	}
		// }
		if (correct)
		{
			//remove the row
			for(int i=v_start; i<=v_end; i++)
				board[i + boardSize][l + boardSize][-l-i + boardSize] = 2 * colour;
		}
		if(colour == 1)
			numDiscs = numDiscs + 5;
		else
			numOppDiscs = numOppDiscs + 5;
	}
	else if (r1 == r2)
	{
		int r = r1;
		bool correct = true;
		//check if valid row is being removed
		int l_start = min(l1,l2) ,l_end = max(l1,l2);
		// for(int i=l_start+1; i<=l_end; i++)
		// {
		// 	if (board[-r-i][i][r] != a && (a == 2 || a == -2))
		// 	{
		// 		cout<<"Error! the row to delete does not have all markers or all markers of same player"<<endl;
		// 		cout<< "Above error printed in Board.cpp: removeRow." << endl;
		// 		correct = false;	
		// 		break;
		// 	}
		// }
		if (correct)
		{
			//remove the row
			for(int i=l_start; i<=l_end; i++)
				board[-r-i + boardSize][i + boardSize][v + boardSize] = 2 * colour;
		}
		if(colour == 1)
			numDiscs = numDiscs + 5;
		else
			numOppDiscs = numOppDiscs + 5;
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

	if(board[v + boardSize][l + boardSize][r + boardSize] == 1 || board[v + boardSize][l + boardSize][r + boardSize] == -1) {
		if(board[v + boardSize][l + boardSize][r + boardSize] == 1) {
			numRings--;
			ringsScored++;
		}
		else {
			numOppRings--;
			oppRingsScored++;
		}
		board[v + boardSize][l + boardSize][r + boardSize] == 0;
	}
	else
	{
		cout << "Error! Ring not found for deletion! Hexagon number: " <<  hexagonNum << " Point number: " << position << endl;
		cout << "Above error printed in Board.cpp: removeRing." << endl;
	}
}

void Board::undoRemoveRing(int colour, int hexagonNum, int position) {
	int v, l, r = 0;
	convertTo(hexagonNum, position, v, l, r);

	if(board[v + boardSize][l + boardSize][r + boardSize] != 0) {
		cout << "Error! Empty space not found for ring addition! Hexagon number: " <<  hexagonNum << " Point number: " << position << endl;
		cout << "Above error printed in Board.cpp: undoRemoveRing." << endl;
	}
	else {
		board[v + boardSize][l + boardSize][r + boardSize] = colour;
		if(colour == 1)
			numRings++;
		else
			numOppRings++;
	}
}

vector<string> Board::generateMoveList(int perspective) {
	
	vector<string> moves = new vector();
	int v = 0;
	int l = 0;
	int r = 0;
	if(ringsScored == 0 && numRings < maxRings) {
		addRingMoves(moves);
	}
	else {
		for(int i = 0; i < ringV.size(); i++) {
			v = ringV.at(i);	l = ringL.at(i);	r = ringL.at(i);
			if(board[v + boardSize][l + boardSize][r + boardSize] == perspective)
				moveRingMoves(moves, v, l, r)
		}
	}
}

void Board::addRingMoves (vector<string> moves) {

	int r = 0;
	int hexagonNum = 0;
	int position = 0;
	for(int v = -1 * boardSize; v < boardSize + 1; v++) {
		for(int l = -1 * boardSize; l < boardSize + 1; l++) {
			r = -1 * v + (-1 * l);
			if(check(v, l, r)) {
				if(board[v + boardSize][l + boardSize][r + boardSize] == 0) {
					convertBack(v, l, r, hexagonNum, position);
					string s = "S " + hexagonNum + " " + position;
					moves.push_back(s);
				}
			}
		}
	}
}

void Board::moveRingMoves (vector<string> moves, int v, int l, int r) {

}

bool Board::check (int v, int l, int r) {
	if(abs(v) > boardSize || abs(l) > boardSize || abs(r) > boardSize)
		return false;
	return true;
}

void Board::nextUp(int& v, int& l, int& r) {
	l = l + 1;
	r = r - 1;
}

void Board::nextDown (int& v, int& l, int& r) {
	l = l - 1;
	r = r + 1;
}

void Board::nextUpRight (int& v, int& l, int& r) {
	v = v + 1;
	r = r - 1;
}

void Board::nextUpLeft (int& v, int& l, int& r) {
	v = v - 1;
	l = l + 1;
}

void Board::nextDownRight (int& v, int& l, int& r) {
	v = v + 1;
	l = l - 1;
}

void Board::nextDownLeft (int& v, int& l, int& r) {
	v = v - 1;
	r = r + 1;
}