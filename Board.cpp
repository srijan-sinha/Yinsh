//////////////////////////////

// Updation of ringV, ringL, ringR has to be done in undo functions.

//////////////////////////////

//////////////////////////////

// moveRingMoves ki jagah addRingMoves call kiya hai har jagah.

//////////////////////////////

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

//checked
void Board::convertTo (int hexagonNum, int position, int& v, int& l, int& r) 
{
	int segment = 0;

	if(hexagonNum == 0) 
	{ 
		v = 0; l = 0; r = 0; 
	}
	else 
	{
		segment = position / hexagonNum;
		
		if(segment == 0) { v = position % hexagonNum; l = hexagonNum - (position % hexagonNum); r = -1 * hexagonNum; }
		else if(segment == 1) { v = hexagonNum; l = -1 * (position % hexagonNum); r = -1 * (hexagonNum - (position % hexagonNum)); }
		else if(segment == 2) { v = hexagonNum - (position % hexagonNum); l = -1 * hexagonNum; r = position % hexagonNum; }
		else if(segment == 3) { v = -1 * (position % hexagonNum); l = -1 * (hexagonNum - (position % hexagonNum)); r = hexagonNum; }
		else if(segment == 4) { v = -1 * hexagonNum; l = position % hexagonNum; r = hexagonNum - (position % hexagonNum); }
		else if(segment == 5) { v = -1 * (hexagonNum - (position % hexagonNum)); l = hexagonNum; r = -1 * (position % hexagonNum); }
	}
}

//checked
void Board::convertBack (int v, int l, int r, int& hexagonNum, int& position) {
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

//checked
void Board::addRing (int colour, int hexagonNum, int position) 
{
	
	int v, l, r = 0;
	convertTo(hexagonNum, position, v, l, r);
	if(board[v + boardSize][l + boardSize][r + boardSize] == 0) 
	{
		board[v + boardSize][l + boardSize][r + boardSize] = colour;
		
		if(colour == 1)
		{
			numRings++;
			ringV.push_back(v);
			ringL.push_back(l);
			ringR.push_back(r);
		}
		else
		{
			numOppRings++;
			ringV_opp.push_back(v);
			ringL_opp.push_back(l);
			ringR_opp.push_back(r);
		}
		
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

//checked
void Board::moveRing (int hexagon1, int position1, int hexagon2, int position2) 
{
	int v1, l1, r1, v2, l2, r2 = 0;
	convertTo(hexagon1, position1, v1, l1, r1);
	convertTo(hexagon2, position2, v2, l2, r2);

	if(board[v2 + boardSize][l2 + boardSize][r2 + boardSize] == 0) 
	{
		board[v2 + boardSize][l2 + boardSize][r2 + boardSize] = board[v1 + boardSize][l1 + boardSize][r1 + boardSize];
		
		if (board[v1 + boardSize][l1 + boardSize][r1 + boardSize] == 1) 
		{
			board[v1 + boardSize][l1 + boardSize][r1 + boardSize] = 2;
			numDiscs++;
			for(int i=0;i<ringV.size();i++)
			{
				if(ringV.at(i) == v1 && ringL.at(i) == l1)
				{
					ringV.at(i) = v2;
					ringL.at(i) = l2;
					ringR.at(i) = r2;
					break;
				}
			}
		}
		else 
		{
			board[v1 + boardSize][l1 + boardSize][r1 + boardSize] = -2;
			numOppDiscs++;
			for(int i=0;i<ringV_opp.size();i++)
			{
				if(ringV_opp.at(i) == v1 && ringL_opp.at(i) == l1)
				{
					ringV_opp.at(i) = v2;
					ringL_opp.at(i) = l2;
					ringR_opp.at(i) = r2;
					break;
				}
			}
		}
		//flip all the markers
		if (v1 == v2)
		{
			int v = v1;
			bool correct = true;
			int l_start = min(l1,l2) ,l_end = max(l1,l2);
			
			if (correct)
			{
				for(int i=l_start+1; i<l_end; i++) 
				{
					if(board[v + boardSize][i + boardSize][-v-i + boardSize] == 2) 
					{
						numDiscs--;
						numOppDiscs++;
					}
					else if (board[v + boardSize][i + boardSize][-v-i + boardSize] == -2) 
					{
						numOppDiscs--;
						numDiscs++;
					}
					board[v + boardSize][i + boardSize][-v-i + boardSize] = -board[v + boardSize][i + boardSize][-v-i + boardSize];
				}
			}
		}
		else if (l1 == l2)
		{
			int l = l1;
			bool correct = true;
			int v_start = min(v1,v2) ,v_end = max(v1,v2);

			if (correct)
			{
				for(int i=v_start+1; i<v_end; i++) {
					if(board[i + boardSize][l + boardSize][-l-i + boardSize] == 2) {
						numDiscs--;
						numOppDiscs++;
					}
					else if (board[i + boardSize][l + boardSize][-l-i + boardSize] == -2){
						numOppDiscs--;
						numDiscs++;
					}
					board[i + boardSize][l + boardSize][-l-i + boardSize] = -board[i + boardSize][l + boardSize][-l-i + boardSize];
				}
			}
		}
		else if (r1 == r2)
		{
			int r = r1;
			bool correct = true;
			int l_start = min(l1,l2) ,l_end = max(l1,l2);

			if (correct)
			{
				for(int i=l_start+1; i<l_end; i++) {
					if(board[-r-i + boardSize][i + boardSize][r + boardSize] == 2) {
						numDiscs--;
						numOppDiscs++;
					}
					else if (board[-r-i + boardSize][i + boardSize][r + boardSize] == -2) {
						numOppDiscs--;
						numDiscs++;
					}
					board[-r-i + boardSize][i + boardSize][r + boardSize] = -board[-r-i + boardSize][i + boardSize][r + boardSize];
				}
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

	int v1, l1, r1, v2, l2, r2 = 0;
	convertTo(hexagon1, position1, v1, l1, r1);
	convertTo(hexagon2, position2, v2, l2, r2);

	if(board[v2 + boardSize][l2 + boardSize][r2 + boardSize] == 1 || board[v2 + boardSize][l2 + boardSize][r2 + boardSize] == -1) 
	{
		if(board[v1 + boardSize][l1 + boardSize][r1 + boardSize] == 2)
			numDiscs--;
		else(board[v1 + boardSize][l1 + boardSize][r1 + boardSize] == -2)
			numOppDiscs--;

		board[v1 + boardSize][l1 + boardSize][r1 + boardSize] = board[v2 + boardSize][l2 + boardSize][r2 + boardSize];
		
		board[v2 + boardSize][l2 + boardSize][r2 + boardSize] = 0;
		
		if (v1 == v2)
		{
			int v = v1;
			bool correct = true;
			int l_start = min(l1,l2) ,l_end = max(l1,l2);

			if (correct)
			{
				for(int i=l_start+1; i<l_end; i++) {
					if(board[v + boardSize][i + boardSize][-v-i + boardSize] == 2) {
						numDiscs--;
						numOppDiscs++;
					}
					else(board[v + boardSize][i + boardSize][-v-i + boardSize] == -2) {
						numOppDiscs--;
						numDiscs++;
					}
					board[v + boardSize][i + boardSize][-v-i + boardSize] = -board[v + boardSize][i + boardSize][-v-i + boardSize];
				}
			}
		}
		else if (l1 == l2)
		{
			int l = l1;
			bool correct = true;
			int v_start = min(v1,v2) ,v_end = max(v1,v2);

			if (correct)
			{
				for(int i=v_start+1; i<v_end; i++) {
					if(board[i + boardSize][l + boardSize][-l-i + boardSize] == 2) {
						numDiscs--;
						numOppDiscs++;
					}
					else if (board[i + boardSize][l + boardSize][-l-i + boardSize] == -2){
						numOppDiscs--;
						numDiscs++;
					}
					board[i + boardSize][l + boardSize][-l-i + boardSize] = -board[i + boardSize][l + boardSize][-l-i + boardSize];
				}
			}
		}
		else if (r1 == r2)
		{
			int r = r1;
			bool correct = true;
			int l_start = min(l1,l2) ,l_end = max(l1,l2);

			if (correct)
			{
				for(int i=l_start+1; i<l_end; i++) {
					if(board[-r-i + boardSize][i + boardSize][v + boardSize] == 2) {
						numDiscs--;
						numOppDiscs++;
					}
					else(board[-r-i + boardSize][i + boardSize][v + boardSize] == -2) {
						numOppDiscs--;
						numDiscs++;
					}
					board[-r-i + boardSize][i + boardSize][v + boardSize] = -board[-r-i + boardSize][i + boardSize][v + boardSize];
				}
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

//checked
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

//checked
void Board::removeRing (int hexagonNum, int position) {
	
	int v, l, r = 0;
	convertTo(hexagonNum, position, v, l, r);
	if(board[v + boardSize][l + boardSize][r + boardSize] == 1 || board[v + boardSize][l + boardSize][r + boardSize] == -1) {
		if(board[v + boardSize][l + boardSize][r + boardSize] == 1) {
			numRings--;
			ringsScored++;
			for(int i=0;i<ringV.size();i++)
			{
				if(ringV.at(i) == v && ringL.at(i) == l)
				{
					ringV.erase(ringV.begin() + i,ringV.begin() + i+1);
					ringL.erase(ringL.begin() + i,ringL.begin() + i+1);
					ringR.erase(ringR.begin() + i,ringR.begin() + i+1);
					break;
				}
			}
		}
		else 
		{
			numOppRings--;
			oppRingsScored++;
			for(int i=0;i<ringV_opp.size();i++)
			{
				if(ringV_opp.at(i) == v && ringL_opp.at(i) == l)
				{
					ringV_opp.erase(ringV_opp.begin() + i,ringV_opp.begin() + i+1);
					ringL_opp.erase(ringL_opp.begin() + i,ringL_opp.begin() + i+1);
					ringR_opp.erase(ringR_opp.begin() + i,ringR_opp.begin() + i+1);
					break;
				}
			}
		}
		board[v + boardSize][l + boardSize][r + boardSize] = 0;
	
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
		if(colour == 1) {
			numRings++;
			ringsScored--;
		}
		else {
			numOppRings++;
			oppRingsScored--;
		}
	}
}

vector<string> Board::generateMoveList(int perspective) 
{
	
	vector<string> moves = new vector();
	int v = 0;
	int l = 0;
	int r = 0;
	int v1,l1,r1,v2,l2,r2;
	bool check_row = row_detected(v1,l1,r1,v2,l2,r2,perspective);
	if (perspective == 1)
	{
		if (ringsScored == 0 && numRings < maxRings)
		{
			moves = addRingMoves(moves);
		}
		else
		{
			string empty = "";
			moves = uptoMoveRingMoves(empty, perspective);
			for(int i = 0; i < moves.size(); i++) {
				replace(i, afterMoveRingMoves(moves.at(i), perspective));
			}

		}
		// else if (!check_row)
		// {
		// 	for(int i=0;i<ringV.size();i++)
		// 	{
		// 		v = ringV.at(i);
		// 		l = ringL.at(i);
		// 		r = ringR.at(j);
		// 		moves = addRingMoves(moves,v,l,r,perspective, ringV, ringL, ringR);
		// 	}
			
		// }
		// else if (check_row)
		// {
		// 	int h1,p1,h2,p2;
		// 	convertBack(v1,l1,r1,h1,p1);
		// 	convertBack(v2,l2,r2,h2,p2);
		// 	//command to remove the row
		// 	s += "RS" + h1 + " " + p1;
		// 	s += "RE" + h2 + " " + p2;
		// 	//command to remove the ring
		// 	for(int i=0;i<ringV.size();i++)
		// 	{
		// 		int h,p;
		// 		convertBack(ringV.at(i),ringL.at(i),ringR.at(i),h,p);
		// 		s += "X" + h + " " + p;
		// 		// moves.push_back(s);
		// 		for(int i=0;i<ringV.size();i++)
		// 		{
		// 			v = ringV.at(i);
		// 			l = ringL.at(i);
		// 			r = ringR.at(j);
		// 			moves = addRingMoves(moves,v,l,r,perspective, ringV, ringL, ringR);
		// 		}	
		// 		for(int j=0;j<moves.size();j++)
		// 		{
		// 			moves.at(j) = s + moves.at(j);
		// 		}	
		// 	}
		// }
		
	}
	else if (perspective == -1)
	{
		if (oppRingsScored == 0 && numOppRings < maxRings)
		{
			moves = addRingMoves(moves);
		}
		else if (!check_row)
		{
			for(int i=0;i<ringV_opp.size();i++)
			{
				v = ringV_opp.at(i);
				l = ringL_opp.at(i);
				r = ringR_opp.at(j);
				moves = addRingMoves(moves,v,l,r,perspective, ringV_opp, ringL_opp, ringR_opp);
			}
			
		}
		else if (check_row)
		{
			int h1,p1,h2,p2;
			convertBack(v1,l1,r1,h1,p1);
			convertBack(v2,l2,r2,h2,p2);
			//command to remove the row
			s += "RS" + h1 + " " + p1;
			s += "RE" + h2 + " " + p2;
			//command to remove the ring
			for(int i=0;i<ringV_opp.size();i++)
			{
				int h,p;
				convertBack(ringV_opp.at(i),ringL_opp.at(i),ringR_opp.at(i),h,p);
				s += "X" + h + " " + p;
				// moves.push_back(s);
				for(int i=0;i<ringV_opp.size();i++)
				{
					v = ringV_opp.at(i);
					l = ringL_opp.at(i);
					r = ringR_opp.at(j);
					moves = addRingMoves(moves,v,l,r,perspective, ringV, ringL, ringR);
				}	
				for(int j=0;j<moves.size();j++)
				{
					moves.at(j) = s + moves.at(j);
				}	
			}
		}
	}
	return moves;
	
}

vector<string> Board::uptoMoveRingMoves (string s, int perspective) {
	vector< vector<int> > start;
	vector< vector<int> > end;
	vector <string> allMoves;
	int h1, p1, h2, p2;
	row_detected_modified(start, end, perspective);
	if(start.size() != 0) {
		for(int i = 0; i < start.size(); i++) {
			convertBack(start.at(i).at(0), start.at(i).at(1), start.at(i).at(2), h1, p1);
			convertBack(end.at(i).at(0), end.at(i).at(1), end.at(i).at(2), h2, p2);
		} 
	}

vector<string> Board::addRingMoves (vector<string> moves) 
{

	int r = 0;
	int hexagonNum = 0;
	int position = 0;
	for(int v = -1 * boardSize; v < boardSize + 1; v++) {
		for(int l = -1 * boardSize; l < boardSize + 1; l++) {
			r = -1 * v + (-1 * l);
			if(check(v, l, r)) {
				if(board[v + boardSize][l + boardSize][r + boardSize] == 0) {
					convertBack(v, l, r, hexagonNum, position);
					string s = "P " + hexagonNum + " " + position;
					moves.push_back(s);
				}
			}
		}
	}
	return moves;
}

vector<string> Board::moveRingMoves (vector<string> moves, int v, int l, int r,int perspective, vector<int> ringV_local, vector<int> ringL_local, vector<int> ringR_local) 
{
	int l_temp,r_temp,v_temp;
	//in v
	int i = 1;
	bool marker = false;
	while(true)
	{
		//move up
		v_temp = v;
		l_temp = l + i;
		r_temp = r - i;
		i++;
		if (!check(v_temp,l_temp,r_temp))
			break;
		if (board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == 1 || board[v + boardSize][l_temp + boardSize][r_temp + boardSize] == -1)
			break;
		if (board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == 2 || board[v + boardSize][l_temp + boardSize][r_temp + boardSize] == -2)
		{
			marker = true;
			continue;
		}
		int hexagonNum1,hexagonNum2,position1,position2;
		convertBack(v, l, r, hexagonNum1, position1);
		string s = "S " + hexagonNum1 + " " + position1;
		convertBack(v_temp, l_temp, r_temp, hexagonNum2, position2);
		s += "M" + hexagonNum2 + " " + position2;
		vector<int> v = row_detect(hexagonNum1,position1,hexagonNum2,position2,perspective);
		if (v.size() != 0)
		{
			//command to remove the row
			s += "RS" + v.at(0) + " " + v.at(1);
			s += "RE" + v.at(2) + " " + v.at(3);
			//command to remove the ring
			for(int i=0;i<ringV_local.size();i++)
			{
				int h,p;
				convertBack(ringV_local.at(i),ringL_local.at(i),ringR_local.at(i),h,p);
				s += "X" + h + " " + p;
				moves.push_back(s);		
			}

		}
		else
		{
			moves.push_back(s);
		}
		if (marker)
			break;
	}

	i = 1;
	marker = false;
	while(true)
	{
		//move down
		v_temp = v;
		l_temp = l - i;
		r_temp = r + i;
		i++;
		if (!check(v_temp,l_temp,r_temp))
			break;
		if (board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == 1 || board[v + boardSize][l_temp + boardSize][r_temp + boardSize] == -1)
			break;
		if (board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == 2 || board[v + boardSize][l_temp + boardSize][r_temp + boardSize] == -2)
		{
			marker = true;
			continue;
		}
		int hexagonNum1,hexagonNum2,position1,position2;
		convertBack(v, l, r, hexagonNum1, position1);
		string s = "S " + hexagonNum1 + " " + position1;
		convertBack(v_temp, l_temp, r_temp, hexagonNum2, position2);
		s += "M" + hexagonNum2 + " " + position2;
		vector<int> v = row_detect(hexagonNum1,position1,hexagonNum2,position2,perspective);
		if (v.size() != 0)
		{
			//command to remove the row
			s += "RS" + v.at(0) + " " + v.at(1);
			s += "RE" + v.at(2) + " " + v.at(3);
			//command to remove the ring
			for(int i=0;i<ringV_local.size();i++)
			{
				int h,p;
				convertBack(ringV_local.at(i),ringL_local.at(i),ringR_local.at(i),h,p);
				s += "X" + h + " " + p;
				moves.push_back(s);		
			}

		}
		else
		{
			moves.push_back(s);
		}
		if (marker)
			break;
	}

	//in l
	i = 1;
	marker = false;
	while(true)
	{
		//move up
		v_temp = v + i;
		l_temp = l;
		r_temp = r - i;
		i++;
		if (!check(v_temp,l_temp,r_temp))
			break;
		if (board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == 1 || board[v + boardSize][l_temp + boardSize][r_temp + boardSize] == -1)
			break;
		if (board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == 2 || board[v + boardSize][l_temp + boardSize][r_temp + boardSize] == -2)
		{
			marker = true;
			continue;
		}
		int hexagonNum1,hexagonNum2,position1,position2;
		convertBack(v, l, r, hexagonNum1, position1);
		string s = "S " + hexagonNum1 + " " + position1;
		convertBack(v_temp, l_temp, r_temp, hexagonNum2, position2);
		s += "M" + hexagonNum2 + " " + position2;
		vector<int> v = row_detect(hexagonNum1,position1,hexagonNum2,position2,perspective);
		if (v.size() != 0)
		{
			//command to remove the row
			s += "RS" + v.at(0) + " " + v.at(1);
			s += "RE" + v.at(2) + " " + v.at(3);
			//command to remove the ring
			for(int i=0;i<ringV_local.size();i++)
			{
				int h,p;
				convertBack(ringV_local.at(i),ringL_local.at(i),ringR_local.at(i),h,p);
				s += "X" + h + " " + p;
				moves.push_back(s);		
			}

		}
		else
		{
			moves.push_back(s);
		}
		if (marker)
			break;
	}

	i = 1;
	marker = false;
	while(true)
	{
		//move up
		v_temp = v - i;
		l_temp = l;
		r_temp = r + i;
		i++;
		if (!check(v_temp,l_temp,r_temp))
			break;
		if (board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == 1 || board[v + boardSize][l_temp + boardSize][r_temp + boardSize] == -1)
			break;
		if (board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == 2 || board[v + boardSize][l_temp + boardSize][r_temp + boardSize] == -2)
		{
			marker = true;
			continue;
		}
		int hexagonNum1,hexagonNum2,position1,position2;
		convertBack(v, l, r, hexagonNum1, position1);
		string s = "S " + hexagonNum1 + " " + position1;
		convertBack(v_temp, l_temp, r_temp, hexagonNum2, position2);
		s += "M" + hexagonNum2 + " " + position2;
		vector<int> v = row_detect(hexagonNum1,position1,hexagonNum2,position2,perspective);
		if (v.size() != 0)
		{
			//command to remove the row
			s += "RS" + v.at(0) + " " + v.at(1);
			s += "RE" + v.at(2) + " " + v.at(3);
			//command to remove the ring
			for(int i=0;i<ringV_local.size();i++)
			{
				int h,p;
				convertBack(ringV_local.at(i),ringL_local.at(i),ringR_local.at(i),h,p);
				s += "X" + h + " " + p;
				moves.push_back(s);		
			}

		}
		else
		{
			moves.push_back(s);
		}
		if (marker)
			break;
	}

	//in r
	i = 1;
	marker = false;
	while(true)
	{
		//move up
		v_temp = v - i;
		l_temp = l + i;
		r_temp = r;
		i++;
		if (!check(v_temp,l_temp,r_temp))
			break;
		if (board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == 1 || board[v + boardSize][l_temp + boardSize][r_temp + boardSize] == -1)
			break;
		if (board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == 2 || board[v + boardSize][l_temp + boardSize][r_temp + boardSize] == -2)
		{
			marker = true;
			continue;
		}
		int hexagonNum1,hexagonNum2,position1,position2;
		convertBack(v, l, r, hexagonNum1, position1);
		string s = "S " + hexagonNum1 + " " + position1;
		convertBack(v_temp, l_temp, r_temp, hexagonNum2, position2);
		s += "M" + hexagonNum2 + " " + position2;
		vector<int> v = row_detect(hexagonNum1,position1,hexagonNum2,position2,perspective);
		if (v.size() != 0)
		{
			//command to remove the row
			s += "RS" + v.at(0) + " " + v.at(1);
			s += "RE" + v.at(2) + " " + v.at(3);
			//command to remove the ring
			for(int i=0;i<ringV_local.size();i++)
			{
				int h,p;
				convertBack(ringV_local.at(i),ringL_local.at(i),ringR_local.at(i),h,p);
				s += "X" + h + " " + p;
				moves.push_back(s);		
			}

		}
		else
		{
			moves.push_back(s);
		}
		if (marker)
			break;
	}

	i = 1;
	marker = false;
	while(true)
	{
		//move up
		v_temp = v + i;
		l_temp = l - i;
		r_temp = r;
		i++;
		if (!check(v_temp,l_temp,r_temp))
			break;
		if (board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == 1 || board[v + boardSize][l_temp + boardSize][r_temp + boardSize] == -1)
			break;
		if (board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == 2 || board[v + boardSize][l_temp + boardSize][r_temp + boardSize] == -2)
		{
			marker = true;
			continue;
		}
		int hexagonNum1,hexagonNum2,position1,position2;
		convertBack(v, l, r, hexagonNum1, position1);
		string s = "S " + hexagonNum1 + " " + position1;
		convertBack(v_temp, l_temp, r_temp, hexagonNum2, position2);
		s += "M" + hexagonNum2 + " " + position2;
		vector<int> v = row_detect(hexagonNum1,position1,hexagonNum2,position2,perspective);
		if (v.size() != 0)
		{
			//command to remove the row
			s += "RS" + v.at(0) + " " + v.at(1);
			s += "RE" + v.at(2) + " " + v.at(3);
			//command to remove the ring
			for(int i=0;i<ringV_local.size();i++)
			{
				int h,p;
				convertBack(ringV_local.at(i),ringL_local.at(i),ringR_local.at(i),h,p);
				s += "X" + h + " " + p;
				moves.push_back(s);		
			}

		}
		else
		{
			moves.push_back(s);
		}
		if (marker)
			break;
	}

	return moves;
}

vector<int> Board::row_detect(int hexagon1, int position1, int hexagon2, int position2, int perspective)
{
	int v1, l1, r1, v2, l2, r2 = 0;
	convertTo(hexagon1, position1, v1, l1, r1);
	convertTo(hexagon2, position2, v2, l2, r2);
	vector<int> v;
	if (v1 == v2)
	{
		int v = v1;
		int l_start = min(l1,l2) ,l_end = max(l1,l2);
		int count,v_temp,l_temp,r_temp,v_up,l_up,r_up;
		int count_vert = 0;
		for(int i=l_start+1; i<=l_end; i++)
		{
			count = 0;
			v_temp = v;
			l_temp = i;
			r_temp = -v-i;
			if (check(v_temp,l_temp,r_temp))
			{
				//check along left axis;
				nextUpLeft(v_temp,l_temp,r_temp);
				while(board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == perspective*(2))
				{
					count++;
					nextUpLeft(v_temp,l_temp,r_temp);
				}
				v_up = v_temp;
				l_up = l_temp;
				r_up = r_temp;
				v_temp = v;
				l_temp = i;
				r_temp = -v-i;
				nextDownLeft(v_temp,l_temp,r_temp);
				while(board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == perspective*(2))
				{
					count++;
					nextDownLeft(v_temp,l_temp,r_temp);
				}
				if (count >= sequenceLength-1)
				{
					int h1,p1,h2,p2;
					convertBack(v_up,l_up,r_up,h1,p1);
					convertBack(v_temp,l_temp,r_temp,h2,p2);
					v.push_back(h1);
					v.push_back(p1);
					v.push_back(h2);
					v.push_back(p2);
					
					return v;
				}


				v_temp = v;
				l_temp = i;
				r_temp = -v-i;


				//check along right axis;
				nextUpRight(v_temp,l_temp,r_temp);
				while(board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == perspective*(2))
				{
					count++;
					nextUpRight(v_temp,l_temp,r_temp);
				}
				v_up = v_temp;
				l_up = l_temp;
				r_up = r_temp;
				v_temp = v;
				l_temp = i;
				r_temp = -v-i;
				nextDownRight(v_temp,l_temp,r_temp);
				while(board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == perspective*(2))
				{
					count++;
					nextDownRight(v_temp,l_temp,r_temp);
				}
				if (count >= sequenceLength-1)
				{
					int h1,p1,h2,p2;
					convertBack(v_up,l_up,r_up,h1,p1);
					convertBack(v_temp,l_temp,r_temp,h2,p2);
					v.push_back(h1);
					v.push_back(p1);
					v.push_back(h2);
					v.push_back(p2);
					
					return v;
				}


				//check vertical row
				v_temp = v;
				l_temp = i;
				r_temp = -v-i;

				if(board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == perspective*(-2))
					count_vert++;
				
			}

		}
		if (count_vert >= sequenceLength-1)
		{
			int h1,p1,h2,p2;
			convertBack(v,l_start,-v-l_start,h1,p1);
			convertBack(v,l_end,-v-l_end,h2,p2);
			v.push_back(h1);
			v.push_back(p1);
			v.push_back(h2);
			v.push_back(p2);
			
			return v;
		}
		
	}
	else if (l1 == l2)
	{
		int l = l1;
		int v_start = min(v1,v2) ,v_end = max(v1,v2);
		int count_left = 0;
		for(int i=v_start+1; i<=v_end; i++)
		{
			count = 0;
			v_temp = i;
			l_temp = l;
			r_temp = -l-i;
			if (check(v_temp,l_temp,r_temp))
			{
				//check along left axis;
				nextUp(v_temp,l_temp,r_temp);
				while(board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == perspective*(2))
				{
					count++;
					nextUp(v_temp,l_temp,r_temp);
				}
				v_up = v_temp;
				l_up = l_temp;
				r_up = r_temp;
				v_temp = i;
				l_temp = l;
				r_temp = -l-i;
				nextDown(v_temp,l_temp,r_temp);
				while(board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == perspective*(2))
				{
					count++;
					nextDown(v_temp,l_temp,r_temp);
				}
				if (count >= sequenceLength-1)
				{
					int h1,p1,h2,p2;
					convertBack(v_up,l_up,r_up,h1,p1);
					convertBack(v_temp,l_temp,r_temp,h2,p2);
					v.push_back(h1);
					v.push_back(p1);
					v.push_back(h2);
					v.push_back(p2);
					
					return v;
				}


				v_temp = i;
				l_temp = l;
				r_temp = -l-i;


				//check along right axis;
				nextUpRight(v_temp,l_temp,r_temp);
				while(board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == perspective*(2))
				{
					count++;
					nextUpRight(v_temp,l_temp,r_temp);
				}
				v_up = v_temp;
				l_up = l_temp;
				r_up = r_temp;
				v_temp = i;
				l_temp = l;
				r_temp = -l-i;
				nextDownRight(v_temp,l_temp,r_temp);
				while(board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == perspective*(2))
				{
					count++;
					nextDownRight(v_temp,l_temp,r_temp);
				}
				if (count >= sequenceLength-1)
				{
					int h1,p1,h2,p2;
					convertBack(v_up,l_up,r_up,h1,p1);
					convertBack(v_temp,l_temp,r_temp,h2,p2);
					v.push_back(h1);
					v.push_back(p1);
					v.push_back(h2);
					v.push_back(p2);
					
					return v;
				}


				//check left axis row
				v_temp = i;
				l_temp = l;
				r_temp = -l-i;

				if(board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == perspective*(-2))
					count_left++;
				
			}
		}	
		if (count_left >= sequenceLength-1)
		{
			int h1,p1,h2,p2;
			convertBack(v_start,l,-v_start-l,h1,p1);
			convertBack(v_end,l,-v_end-l,h2,p2);
			v.push_back(h1);
			v.push_back(p1);
			v.push_back(h2);
			v.push_back(p2);
			
			return v;
		}	
	}
	else if (r1 == r2)
	{
		int r = r1;
		int l_start = min(l1,l2) ,l_end = max(l1,l2);
		int count_right = 0;
		for(int i=l_start+1; i<=l_end; i++)
		{
			count = 0;
			v_temp = -r-i;
			l_temp = i;
			r_temp = r;
			if (check(v_temp,l_temp,r_temp))
			{
				//check along left axis;
				nextUpLeft(v_temp,l_temp,r_temp);
				while(board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == perspective*(2))
				{
					count++;
					nextUpLeft(v_temp,l_temp,r_temp);
				}
				v_up = v_temp;
				l_up = l_temp;
				r_up = r_temp;
				v_temp = -r-i;
				l_temp = i;
				r_temp = r;
				nextDownLeft(v_temp,l_temp,r_temp);
				while(board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == perspective*(2))
				{
					count++;
					nextDownLeft(v_temp,l_temp,r_temp);
				}
				if (count >= sequenceLength-1)
				{
					int h1,p1,h2,p2;
					convertBack(v_up,l_up,r_up,h1,p1);
					convertBack(v_temp,l_temp,r_temp,h2,p2);
					v.push_back(h1);
					v.push_back(p1);
					v.push_back(h2);
					v.push_back(p2);
					
					return v;
				}


				v_temp = -r-i;
				l_temp = i;
				r_temp = r;


				//check along right axis;
				nextUp(v_temp,l_temp,r_temp);
				while(board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == perspective*(2))
				{
					count++;
					nextUp(v_temp,l_temp,r_temp);
				}
				v_up = v_temp;
				l_up = l_temp;
				r_up = r_temp;
				v_temp = -r-i;
				l_temp = i;
				r_temp = r;
				nextDown(v_temp,l_temp,r_temp);
				while(board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == perspective*(2))
				{
					count++;
					nextDown(v_temp,l_temp,r_temp);
				}
				if (count >= sequenceLength-1)
				{
					int h1,p1,h2,p2;
					convertBack(v_up,l_up,r_up,h1,p1);
					convertBack(v_temp,l_temp,r_temp,h2,p2);
					v.push_back(h1);
					v.push_back(p1);
					v.push_back(h2);
					v.push_back(p2);
					
					return v;
				}


				//check right axis row
				v_temp = -r-i;
				l_temp = i;
				r_temp = r;

				if(board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == perspective*(-2))
					count_right++;
				
			}
		}
		if (count_right >= sequenceLength-1)
		{
			int h1,p1,h2,p2;
			convertBack(-r-l_start,l_start,r,h1,p1);
			convertBack(-r-l_end,l_end,r,h2,p2);
			v.push_back(h1);
			v.push_back(p1);
			v.push_back(h2);
			v.push_back(p2);
			
			return v;
		}
	}
	else
	{
		cout << "Error! Given points (" <<  hexagon1 << "," << position1 << ") and (" <<  hexagon2 << "," << position2 << ") are not on same line" << endl;
		cout << "Above error printed in Board.cpp: Row_detect" << endl;	
	}

}

//checked
bool Board::row_detected(int& v1, int& l1, int& r1, int& v2, int& l2, int& r2, int perspective)
{
	for(int v = -boardSize;v<boardSize;v++)
	{
		for(int l = -boardSize;l<boardSize;l++)
		{
			int r = -v-l;
			int v_temp,l_temp,r_temp,count=0;
			int v_up,l_up,r_up;
			if(check(v,l,r))
			{
				//check for vertical row;
				count = 0;
				v_temp = v;
				l_temp = l;
				r_temp = r;
				if (check(v_temp,l_temp,r_temp))
				{
					while(board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == perspective*2)
					{
						count++;
						nextUp(v_temp,l_temp,r_temp);
					}
				}
				v_up = v_temp;
				l_up = l_temp;
				r_up = r_temp;
				v_temp = v;
				l_temp = l;
				r_temp = r;
				nextDown(v_temp,l_temp,r_temp);
				// cout<<v_temp<<l_temp<<r_temp<<endl;
				if (check(v_temp,l_temp,r_temp))
				{	
					while(board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == perspective*2)
					{
						count++;
						nextDown(v_temp,l_temp,r_temp);
					}
				}
				if (count >= sequenceLength)
				{
					cout<<v<<l<<r<<endl;
					cout<<count<<endl;
					nextDown(v_up,l_up,r_up);
					nextUp(v_temp,l_temp,r_temp);
					v1 = v_temp;
					l1 = l_temp;
					r1 = r_temp;
					v2 = v_up;
					l2 = l_up;
					r2 = r_up;
					return true;
				}

				//check for left row;
				count = 0;
				v_temp = v;
				l_temp = l;
				r_temp = r;
				if (check(v_temp,l_temp,r_temp))
				{
					while(board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == perspective*2)
					{
						count++;
						nextUpLeft(v_temp,l_temp,r_temp);
					}
				}
				v_up = v_temp;
				l_up = l_temp;
				r_up = r_temp;
				v_temp = v;
				l_temp = l;
				r_temp = r;
				if (check(v_temp,l_temp,r_temp))
				{
					while(board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == perspective*2)
					{
						count++;
						nextDownLeft(v_temp,l_temp,r_temp);
					}
				}
				if (count >= sequenceLength)
				{
					nextDownLeft(v_up,l_up,r_up);
					nextUpLeft(v_temp,l_temp,r_temp);
					v1 = v_temp;
					l1 = l_temp;
					r1 = r_temp;
					v2 = v_up;
					l2 = l_up;
					r2 = r_up;
					return true;
				}

				//check for right row;
				count = 0;
				v_temp = v;
				l_temp = l;
				r_temp = r;
				if (check(v_temp,l_temp,r_temp))
				{
					while(board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == perspective*2)
					{
						count++;
						nextUpRight(v_temp,l_temp,r_temp);
					}
				}
				v_up = v_temp;
				l_up = l_temp;
				r_up = r_temp;
				v_temp = v;
				l_temp = l;
				r_temp = r;
				if (check(v_temp,l_temp,r_temp))
				{
					while(board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == perspective*2)
					{
						count++;
						nextDownRight(v_temp,l_temp,r_temp);
					}
				}
				if (count >= sequenceLength)
				{
					nextDownRight(v_up,l_up,r_up);
					nextUpRight(v_temp,l_temp,r_temp);
					
					v1 = v_temp;
					l1 = l_temp;
					r1 = r_temp;
					v2 = v_up;
					l2 = l_up;
					r2 = r_up;
					return true;
				}
			}

		}
	}
	return false;
}

void Board::row_detected_modified(vector< vector<int> > &start, vector< vector<int> > &end, int perspective)
{
	for(int v = -boardSize;v<boardSize;v++)
	{
		for(int l = -boardSize;l<boardSize;l++)
		{
			int r = -v-l;
			int v_temp,l_temp,r_temp,count=0;
			int v_up,l_up,r_up;
			if(check(v,l,r))
			{
				//check for vertical row;
				count = 0;
				v_temp = v;
				l_temp = l;
				r_temp = r;
				if (check(v_temp,l_temp,r_temp))
				{
					while(board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == perspective*2)
					{
						count++;
						nextUp(v_temp,l_temp,r_temp);
						if(!check(v_temp,l_temp,r_temp))
							break;
						if (count==sequenceLength)
							break;
					}
				}
				if (count >= sequenceLength)
				{
					nextDown(v_temp,l_temp,r_temp);
					vector<int> v1;
					v1.push_back(v);
					v1.push_back(l);
					v1.push_back(r);
					start.push_back(v1);
					vector<int> v2;
					v2.push_back(v_temp);
					v2.push_back(l_temp);
					v2.push_back(r_temp);
					end.push_back(v2);
					
				}

				//check for left row;
				count = 0;
				v_temp = v;
				l_temp = l;
				r_temp = r;
				if (check(v_temp,l_temp,r_temp))
				{
					while(board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == perspective*2)
					{
						count++;
						nextUpLeft(v_temp,l_temp,r_temp);
						if(!check(v_temp,l_temp,r_temp))
							break;
						if (count==sequenceLength)
							break;
					}
				}
				
				if (count >= sequenceLength)
				{
					nextDownLeft(v_temp,l_temp,r_temp);
					vector<int> v1;
					v1.push_back(v);
					v1.push_back(l);
					v1.push_back(r);
					start.push_back(v1);
					vector<int> v2;
					v2.push_back(v_temp);
					v2.push_back(l_temp);
					v2.push_back(r_temp);
					end.push_back(v2);
					
				}

				//check for right row;
				count = 0;
				v_temp = v;
				l_temp = l;
				r_temp = r;
				if (check(v_temp,l_temp,r_temp))
				{
					while(board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == perspective*2)
					{
						count++;
						nextUpRight(v_temp,l_temp,r_temp);
						if(!check(v_temp,l_temp,r_temp))
							break;
						if (count==sequenceLength)
							break;
					}
				}
				if (count >= sequenceLength)
				{
					nextDownRight(v_temp,l_temp,r_temp);
					vector<int> v1;
					v1.push_back(v);
					v1.push_back(l);
					v1.push_back(r);
					start.push_back(v1);
					vector<int> v2;
					v2.push_back(v_temp);
					v2.push_back(l_temp);
					v2.push_back(r_temp);
					end.push_back(v2);
					
				}
			}

		}
	}
	// return false;
}

//all checked from here
bool Board::check (int v, int l, int r) {
	if(abs(v) > boardSize || abs(l) > boardSize || abs(r) > boardSize)
		return false;
	if ((abs(v) == boardSize && abs(l) == boardSize) || (abs(l) == boardSize && abs(r) == boardSize) || (abs(r) == boardSize && abs(v) == boardSize))
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

void Board::print_board()
{
	int j = 0;
	for(int v = -boardSize; v<0; v++)
	{
		for(int i = 0; i<boardSize*2 - j; i++)
			cout<<" ";
		j++;
		for(int l = 0 - v - boardSize; l<=boardSize; l++)
		{
			int r = -v-l;
			if (check(v,l,r))
			{
				if (board[v+boardSize][l+boardSize][r+boardSize] == -1)
					cout<<"a ";
				else if (board[v+boardSize][l+boardSize][r+boardSize] == -2)
					cout<<"b ";
				else
					cout<<board[v+boardSize][l+boardSize][r+boardSize]<<" ";

			}
			else 
				cout<<"  ";
		}
		cout<<endl;
	}
	
	for(int v = 0; v<=boardSize; v++)
	{
		for(int i = 0; i<boardSize*2 - j; i++)
			cout<<" ";
		j--;
		for(int l = -boardSize; l<=boardSize-v; l++)
		{
			int r = -v-l;
			if (check(v,l,r))
			{
				if (board[v+boardSize][l+boardSize][r+boardSize] == -1)
					cout<<"a ";
				else if (board[v+boardSize][l+boardSize][r+boardSize] == -2)
					cout<<"b ";
				else
					cout<<board[v+boardSize][l+boardSize][r+boardSize]<<" ";
			}
			else
				cout<<"  ";
		}
		cout<<endl;
	}
}