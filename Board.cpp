//////////////////////////////

// Updation of ringV, ringL, ringR has to be done in undo functions.

//////////////////////////////

//////////////////////////////

// Do chhote chhote functions hain string ke. Woh implement karde. String ke hain. 
// Comment mein likha hai kya karna hai. And unko board.h mein abhi daala nahi hai. Sirf cpp mein hain neeche.

//////////////////////////////

#include "Board.h"

Board::Board () 
{

}

Board::Board (int n, int m, int k, int l) {
	
	boardSize = n;
	maxRings = m;
	sequenceLength = k;
	ringsToWin = l;

	numRings = 0;
	numOppRings = 0;

	ringsScored = 0;
	oppRingsScored = 0;

	numDiscs = 0;
	numOppDiscs = 0;
	
	

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
		cerr << "Error! Location already filled! Hexagon number: " <<  hexagonNum << " Point number: " << position << endl;
		cerr << "Above error printed in Board.cpp: addRing." << endl;
	}
}

void Board::addDisc (int colour, int hexagonNum, int position) 
{
	
	int v, l, r = 0;
	convertTo(hexagonNum, position, v, l, r);
	if(board[v + boardSize][l + boardSize][r + boardSize] == 0) 
	{
		board[v + boardSize][l + boardSize][r + boardSize] = colour*2;
		
		
	}
	else
	{
		cerr << "Error! Location already filled! Hexagon number: " <<  hexagonNum << " Point number: " << position << endl;
		cerr << "Above error printed in Board.cpp: addRing." << endl;
	}
}

//checked
void Board::undoAddRing(int hexagonNum, int position) 
{
	int v, l, r = 0;
	convertTo(hexagonNum, position, v, l, r);
	cerr<<board[v + boardSize][l + boardSize][r + boardSize]<<endl;
	if(board[v + boardSize][l + boardSize][r + boardSize] != 1 && board[v + boardSize][l + boardSize][r + boardSize] != -1) {
		cerr << "Error! Ring not found for removal! Hexagon number: " <<  hexagonNum << " Point number: " << position << endl;
		cerr << "Above error printed in Board.cpp: undoAddRing." << endl;
	}
	else {
		if(board[v + boardSize][l + boardSize][r + boardSize] == 1)
		{
			numRings--;
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
			cerr << "Error! Given points (" <<  hexagon1 << "," << position1 << ") and (" <<  hexagon2 << "," << position2 << ") are not on same line" << endl;
			cerr << "Above error printed in Board.cpp: moveRing." << endl;
		}
	}
	else
	{
		cerr<<"at this point: "<<board[v2 + boardSize][l2 + boardSize][r2 + boardSize]<<endl;
		cerr << "Error! Cannot move ring at Hexagon number: " <<  hexagon1 << " Point number: " << position1 << " to a point at Hexagon number: " <<  hexagon2 << " Point number: " << position2 << endl;
		cerr << "Above error printed in Board.cpp: moveRing." << endl;
	}
}

//checked
void Board::undoMoveRing(int hexagon1, int position1, int hexagon2, int position2) 
{

	int v1, l1, r1, v2, l2, r2 = 0;
	convertTo(hexagon1, position1, v1, l1, r1);
	convertTo(hexagon2, position2, v2, l2, r2);

	if(board[v2 + boardSize][l2 + boardSize][r2 + boardSize] == 1 || board[v2 + boardSize][l2 + boardSize][r2 + boardSize] == -1) 
	{
		if(board[v1 + boardSize][l1 + boardSize][r1 + boardSize] == 2)
		{
			numDiscs--;
			for(int i=0;i<ringV.size();i++)
			{
				if(ringV.at(i) == v2 && ringL.at(i) == l2)
				{
					ringV.at(i) = v1;
					ringL.at(i) = l1;
					ringR.at(i) = r1;
					break;
				}
			}
		}
		else if (board[v1 + boardSize][l1 + boardSize][r1 + boardSize] == -2)
		{
			numOppDiscs--;
			for(int i=0;i<ringV_opp.size();i++)
			{
				if(ringV_opp.at(i) == v2 && ringL_opp.at(i) == l2)
				{
					ringV_opp.at(i) = v1;
					ringL_opp.at(i) = l1;
					ringR_opp.at(i) = r1;
					break;
				}
			}
		}
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
					else if (board[v + boardSize][i + boardSize][-v-i + boardSize] == -2) {
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
					if (board[-r-i + boardSize][i + boardSize][r + boardSize] == 2) {
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
			cerr << "Error! Given points (" <<  hexagon1 << "," << position1 << ") and (" <<  hexagon2 << "," << position2 << ") are not on same line" << endl;
			cerr << "Above error printed in Board.cpp: moveRing." << endl;
		}
	}
	else
	{
		cerr << "Error! Cannot move ring at Hexagon number: " <<  hexagon1 << " Point number: " << position1 << " to a point at Hexagon number: " <<  hexagon2 << " Point number: " << position2 << endl;
		cerr << "Above error printed in Board.cpp: moveRing." << endl;
	}
}

//checked
void Board::removeRow (int hexagon1, int position1, int hexagon2, int position2) 
{
	int v1, l1, r1, v2, l2, r2 = 0;
	convertTo(hexagon1, position1, v1, l1, r1);
	convertTo(hexagon2, position2, v2, l2, r2);

	if (v1 == v2)
	{
		int v = v1;
		int a = board[v + boardSize][l1 + boardSize][r1 + boardSize];
		int l_start = min(l1,l2) ,l_end = max(l1,l2);
		for(int i=l_start; i<=l_end; i++)
			board[v + boardSize][i + boardSize][-v-i + boardSize] = 0;
		if(a == 2)
			numDiscs = numDiscs - 5;
		else
			numOppDiscs = numOppDiscs - 5;
	}
	else if (l1 == l2)
	{
		int l = l1;
		int a = board[v1 + boardSize][l + boardSize][-v1-l + boardSize];
		int v_start = min(v1,v2) ,v_end = max(v1,v2);
		for(int i=v_start; i<=v_end; i++)
			board[i + boardSize][l + boardSize][-l-i + boardSize] = 0;
		if(a == 2)
			numDiscs = numDiscs - 5;
		else
			numOppDiscs = numOppDiscs - 5;
	}
	else if (r1 == r2)
	{
		int r = r1;
		int a = board[-r-l1 + boardSize][l1 + boardSize][r + boardSize];
		int l_start = min(l1,l2) ,l_end = max(l1,l2);
		for(int i=l_start; i<=l_end; i++)
			board[-r-i + boardSize][i + boardSize][r + boardSize] = 0;
		if(a == 2)
			numDiscs = numDiscs - 5;
		else
			numOppDiscs = numOppDiscs - 5;
	}
	else
	{
		cerr << "Error! Given points (" <<  hexagon1 << "," << position1 << ") and (" <<  hexagon2 << "," << position2 << ") are not on same line" << endl;
		cerr << "Above error printed in Board.cpp: removeRow." << endl;	
	}
}


//checked
void Board::undoRemoveRow(int colour, int hexagon1, int position1, int hexagon2, int position2) 
{
	int v1, l1, r1, v2, l2, r2 = 0;
	convertTo(hexagon1, position1, v1, l1, r1);
	convertTo(hexagon2, position2, v2, l2, r2);

	if (v1 == v2)
	{
		int v = v1;
		int l_start = min(l1,l2) ,l_end = max(l1,l2);
		for(int i=l_start; i<=l_end; i++)
			board[v + boardSize][i + boardSize][-v-i + boardSize] = 2 * colour;
		if(colour == 1)
			numDiscs = numDiscs + 5;
		else
			numOppDiscs = numOppDiscs + 5;
	}
	else if (l1 == l2)
	{
		int l = l1;
		int v_start = min(v1,v2) ,v_end = max(v1,v2);
		for(int i=v_start; i<=v_end; i++)
			board[i + boardSize][l + boardSize][-l-i + boardSize] = 2 * colour;
		if(colour == 1)
			numDiscs = numDiscs + 5;
		else
			numOppDiscs = numOppDiscs + 5;
	}
	else if (r1 == r2)
	{
		int r = r1;
		int l_start = min(l1,l2) ,l_end = max(l1,l2);
		for(int i=l_start; i<=l_end; i++)
			board[-r-i + boardSize][i + boardSize][r + boardSize] = 2 * colour;
		if(colour == 1)
			numDiscs = numDiscs + 5;
		else
			numOppDiscs = numOppDiscs + 5;
	}
	else
	{
		cerr << "Error! Given points (" <<  hexagon1 << "," << position1 << ") and (" <<  hexagon2 << "," << position2 << ") are not on same line" << endl;
		cerr << "Above error printed in Board.cpp: removeRow." << endl;	
	}
}

//checked
void Board::removeRing (int hexagonNum, int position) 
{
	
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
		cerr << "Error! Ring not found for deletion! Hexagon number: " <<  hexagonNum << " Point number: " << position << endl;
		cerr << "Above error printed in Board.cpp: removeRing." << endl;
	}
}

//checked
void Board::undoRemoveRing(int colour, int hexagonNum, int position) 
{
	int v, l, r = 0;
	convertTo(hexagonNum, position, v, l, r);

	if(board[v + boardSize][l + boardSize][r + boardSize] != 0) {
		cerr << "Error! Empty space not found for ring addition! Hexagon number: " <<  hexagonNum << " Point number: " << position << endl;
		cerr << "Above error printed in Board.cpp: undoRemoveRing." << endl;
	}
	else {
		board[v + boardSize][l + boardSize][r + boardSize] = colour;
		if(colour == 1) {
			numRings++;
			ringsScored--;
			ringV.push_back(v);
			ringL.push_back(l);
			ringR.push_back(r);
		}
		else {
			numOppRings++;
			oppRingsScored--;
			ringV_opp.push_back(v);
			ringL_opp.push_back(l);
			ringR_opp.push_back(r);
		}
	}
}


vector<string> Board::generateMoveList(int perspective) 
{
	
	vector<string> moves;
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
			moves.push_back(empty);
			moves = fullMoves(moves, perspective);
		}
		
		
	}
	else if (perspective == -1)
	{
		if (oppRingsScored == 0 && numOppRings < maxRings)
		{
			moves = addRingMoves(moves);
		}
		else
		{
			string empty = "";
			moves.push_back(empty);
			moves = fullMoves(moves, perspective);
		}
		
	}
	return moves;
	
}


vector<string> Board::fullMoves(vector<string> moves, int perspective) {

	bool flag = true;
	vector<string> allMoves;
	for(int i = 0; i < moves.size(); i++) 
	{
		string t = end_part(moves.at(i));
		executeCommand(t,perspective);
		cerr<<moves.at(i)<<endl;
		allMoves = append(allMoves, fullMove(moves.at(i), perspective));
		undoCommand(t,perspective);
		
	}
	return allMoves;
}

vector<string> Board::fullMove(string s, int perspective) 
{ 

	vector < vector<int> > start;
	vector < vector<int> > end;
	row_detected_modified(start, end, perspective);
	if(contains(s, 'M') && (lastLiteral(s) == 2 || lastLiteral(s) == 3)) 
	{ // 
		cerr<<"case 1"<<endl;
		vector<string> additionalMoves;
		if((perspective == 1 && ringsScored == ringsToWin) || (perspective == -1 && oppRingsScored == ringsToWin)) {
			additionalMoves.push_back(s);
			return additionalMoves;
		}
		if(start.size() != 0) 
		{
			int h1, p1, h2, p2 = 0;
			vector<string> deleteRowMoves;
			for(int i = 0; i < start.size(); i++) {
				convertBack(start.at(i).at(0), start.at(i).at(1), start.at(i).at(2), h1, p1);
				convertBack(end.at(i).at(0), end.at(i).at(1), end.at(i).at(2), h2, p2);
				deleteRowMoves.push_back(s + " " + "RS " + to_string(h1) + " "+ to_string(p1) + " RE "+ to_string(h2) + " " + to_string(p2));
			}
			additionalMoves = fullMoves(deleteRowMoves, perspective);
			// for(int i = 0; i < additionalMoves.size(); i++) {
			// 	additionalMoves.at(i) = s + " " + additionalMoves.at(i);
			// }
		}
		else 
		{
			additionalMoves.push_back(s);
		}
		return additionalMoves;
	}
	else if(contains(s, 'M') && lastLiteral(s) == 1) 
	{
		cerr<<"case 2"<<endl;
		vector<string> deleteRingMove;
		vector<string> additionalMoves;
		int h, p;
		if(perspective == 1) {
			for(int i = 0; i < ringV.size(); i++) {
				convertBack(ringV.at(i), ringL.at(i), ringR.at(i), h, p);
				deleteRingMove.push_back(s + " X " + to_string(h) + " " + to_string(p));
			}
		}
		else {
			for(int i = 0; i < ringV_opp.size(); i++) {
				convertBack(ringV_opp.at(i), ringL_opp.at(i), ringR_opp.at(i), h, p);
				deleteRingMove.push_back(s + " X " + to_string(h) + " " + to_string(p));
			}
		}
		additionalMoves = fullMoves(deleteRingMove, perspective);
		// for(int i = 0; i < additionalMoves.size(); i++) {
		// 	additionalMoves.at(i) = s + " " + additionalMoves.at(i);
		// }
		return additionalMoves;
	}
	else if(!(contains(s, 'M')) && (lastLiteral(s) == 2 || lastLiteral(s) == 4) ) 
	{ 
		cerr<<"case 3"<<endl;
		vector<string> additionalMoves;
		if((perspective == 1 && ringsScored == ringsToWin) || (perspective == -1 && oppRingsScored == ringsToWin)) {
			additionalMoves.push_back(s);
			return additionalMoves;
		}

		if(start.size() == 0) 
		{
			vector<string> ringMove;
			if (perspective == 1)
				ringMove = moveRingMoves(ringMove,perspective,ringV, ringL, ringR);
			else
				ringMove = moveRingMoves(ringMove,perspective,ringV_opp, ringL_opp, ringR_opp);
			
			additionalMoves = fullMoves(ringMove, perspective);
			for(int i = 0; i < additionalMoves.size(); i++) {
				additionalMoves.at(i) = s + " " + additionalMoves.at(i);
			}
		}
		else 
		{
			int h1, p1, h2, p2 = 0;
			vector<string> deleteRowMoves;
			for(int i = 0; i < start.size(); i++) {
				convertBack(start.at(i).at(0), start.at(i).at(1), start.at(i).at(2), h1, p1);
				convertBack(end.at(i).at(0), end.at(i).at(1), end.at(i).at(2), h2, p2);
				deleteRowMoves.push_back("RS " + to_string(h1) + " "+ to_string(p1) + " RE "+ to_string(h2) + " " + to_string(p2));
			}
			additionalMoves = fullMoves(deleteRowMoves, perspective);
			for(int i = 0; i < additionalMoves.size(); i++) {
				additionalMoves.at(i) = s + " " + additionalMoves.at(i);
			}
		}
		return additionalMoves;
	}
	else if(!(contains(s, 'M')) && lastLiteral(s) == 1)
	{
cerr<<"case 4"<<endl;
		vector<string> deleteRingMove;
		vector<string> additionalMoves;
		int h, p;
		if(perspective == 1) 
		{
			for(int i = 0; i < ringV.size(); i++) {
				convertBack(ringV.at(i), ringL.at(i), ringR.at(i), h, p);
				deleteRingMove.push_back("X " + to_string(h) + " " + to_string(p));
			}
		}
		else 
		{
			for(int i = 0; i < ringV_opp.size(); i++) {
				convertBack(ringV_opp.at(i), ringL_opp.at(i), ringR_opp.at(i), h, p);
				deleteRingMove.push_back("X " + to_string(h) + " " + to_string(p));
			}
		}
		additionalMoves = fullMoves(deleteRingMove, perspective);
		for(int i = 0; i < additionalMoves.size(); i++) {
			additionalMoves.at(i) = s + " " + additionalMoves.at(i);
		}
		return additionalMoves;
	}
	else 
	{
		cerr<<"case 5"<<endl;
		vector<string> additionalMoves;
		additionalMoves.push_back(s);
		return additionalMoves;
		cerr << "Error! Code should not go into else!" << endl;
		cerr << "Error printed in fullMove" << endl;
	}
}

//checked
string Board::end_part(string s)
{
	int i = s.size()-1;
	int count = 0;
	while(true)
	{
		if (s.size() == 0)
			return "";
		if(s.at(i) == ' ')
			count++;
		i--;
		if (count == 2)
			break;
	}
	if(s.at(i) == 'E')
	{
		count = 0;
		while(true)
		{
			if(s.at(i) == ' ')
				count++;
			i--;
			if (count == 3)
				break;
		}
		i--;
		return s.substr(i,s.size() - i);
	}
	else if (s.at(i) == 'X')
		return s.substr(i,s.size() - i);
	else if (s.at(i) == 'M')
	{
		count = 0;
		while(true)
		{
			if(s.at(i) == ' ')
				count++;
			i--;
			if (count == 3)
				break;
		}
		return s.substr(i,s.size() - i);
	}
	else
		return "";
}


//checked
int Board::lastLiteral(string s) 
{
	// cerr<<"fullMOve"<<endl;
	int i = s.size()-1;
	int count = 0;
	while(true)
	{
		if (s.size() == 0)
			break;
		if(s.at(i) == ' ')
			count++;
		i--;
		if (count == 2)
			break;
	}
	if (s.size() == 0)
		return 4;
	if(s.at(i) == 'E')
		return 1;
	else if (s.at(i) == 'X')
		return 2;
	else if (s.at(i) == 'M')
		return 3;
	else
		return 4;
	//returns 1 -> RE, 2 -> X, 3 -> M 4 -> nothing
}

//checked
bool Board::contains(string s, char sub) 
{

	for (int i = 0; i < s.size(); ++i)
	{
		if (s.at(i) == sub)
			return true;
	}
	return false;
	//returns true if sub is contained in s. sub always has size 1. 
}

//checked
vector<string> Board::append(vector<string> A, vector<string> B)
{
	A.insert(A.end(), B.begin(), B.end());
	return A;
}


//checked
vector<string> Board::addRingMoves (vector<string> moves) 
{

	int r = 0;
	int hexagonNum = 0;
	int position = 0;
	for(int v = -1 * boardSize; v < boardSize + 1; v++) {
		for(int l = -1 * boardSize; l < boardSize + 1; l++) {
			r = -v-l;
			if(check(v, l, r)) {
				if(board[v + boardSize][l + boardSize][r + boardSize] == 0) {
					convertBack(v, l, r, hexagonNum, position);
					string s = "P " + to_string(hexagonNum) + " " + to_string(position);
					moves.push_back(s);
				}
			}
		}
	}
	return moves;
}

//checked
vector<string> Board::moveRingMoves (vector<string> moves, int perspective, vector<int> ringV_local, vector<int> ringL_local, vector<int> ringR_local) 
{
	for(int j=0;j<ringV_local.size();j++)
	{
		int v = ringV_local.at(j);
		int l = ringL_local.at(j);
		int r = ringR_local.at(j);
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
			if (board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == 1 || board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == -1)
				break;
			if (board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == 2 || board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == -2)
			{
				marker = true;
				continue;
			}
			else
			{	
				int hexagonNum1,hexagonNum2,position1,position2;
				convertBack(v, l, r, hexagonNum1, position1);
				string s = "S " + to_string(hexagonNum1) + " " + to_string(position1);
				convertBack(v_temp, l_temp, r_temp, hexagonNum2, position2);
				s += " M " + to_string(hexagonNum2) + " " + to_string(position2);
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
			if (board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == 1 || board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == -1)
				break;
			if (board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == 2 || board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == -2)
			{
				marker = true;
				continue;
			}
			int hexagonNum1,hexagonNum2,position1,position2;
			convertBack(v, l, r, hexagonNum1, position1);
			string s = "S " + to_string(hexagonNum1) + " " + to_string(position1);
			convertBack(v_temp, l_temp, r_temp, hexagonNum2, position2);
			s += " M " + to_string(hexagonNum2) + " " + to_string(position2);
			moves.push_back(s);
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
			if (board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == 1 || board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == -1)
				break;
			if (board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == 2 || board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == -2)
			{
				cerr<<"yaha jana he"<<endl;
				marker = true;
				continue;
			}
			else
			{
				int hexagonNum1,hexagonNum2,position1,position2;
				convertBack(v, l, r, hexagonNum1, position1);
				string s = "S " + to_string(hexagonNum1) + " " + to_string(position1);
				convertBack(v_temp, l_temp, r_temp, hexagonNum2, position2);
				s += " M " + to_string(hexagonNum2) + " " + to_string(position2);
				moves.push_back(s);
				if(hexagonNum1 == 4 && position1 == 14 && hexagonNum2 == 2 && position2 == 6)
				{
					cerr<<"found here"<<endl;
					cerr<<board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize]<<endl;
				}
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
			if (board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == 1 || board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == -1)
				break;
			if (board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == 2 || board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == -2)
			{
				marker = true;
				continue;
			}
			else
			{
				int hexagonNum1,hexagonNum2,position1,position2;
				convertBack(v, l, r, hexagonNum1, position1);
				string s = "S " + to_string(hexagonNum1) + " " + to_string(position1);
				convertBack(v_temp, l_temp, r_temp, hexagonNum2, position2);
				s += " M " + to_string(hexagonNum2) + " " + to_string(position2);
				moves.push_back(s);
				if(hexagonNum1 == 4 && position1 == 14 && hexagonNum2 == 2 && position2 == 6)
				{
					cerr<<"found here"<<endl;
					cerr<<board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize]<<endl;
				}
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
			if (board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == 1 || board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == -1)
				break;
			if (board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == 2 || board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == -2)
			{
				marker = true;
				continue;
			}
			else
			{
				int hexagonNum1,hexagonNum2,position1,position2;
				convertBack(v, l, r, hexagonNum1, position1);
				string s = "S " + to_string(hexagonNum1) + " " + to_string(position1);
				convertBack(v_temp, l_temp, r_temp, hexagonNum2, position2);
				s += " M " + to_string(hexagonNum2) + " " + to_string(position2);
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
			if (board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == 1 || board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == -1)
				break;
			if (board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == 2 || board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == -2)
			{
				marker = true;
				continue;
			}
			else
			{
				int hexagonNum1,hexagonNum2,position1,position2;
				convertBack(v, l, r, hexagonNum1, position1);
				string s = "S " + to_string(hexagonNum1) + " " + to_string(position1);
				convertBack(v_temp, l_temp, r_temp, hexagonNum2, position2);
				s += " M " + to_string(hexagonNum2) + " " + to_string(position2);
				moves.push_back(s);
			}
			if (marker)
				break;
		}
	
	}
	
	return moves;
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
				while(board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == perspective*2)
				{
					count++;
					nextUp(v_temp,l_temp,r_temp);
					if(!check(v_temp,l_temp,r_temp))
						break;

				}
				v_up = v_temp;
				l_up = l_temp;
				r_up = r_temp;
				v_temp = v;
				l_temp = l;
				r_temp = r;
				while(board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == perspective*2)
				{
					count++;
					nextDown(v_temp,l_temp,r_temp);
					if(!check(v_temp,l_temp,r_temp))
						break;
				}

				if (count >= sequenceLength)
				{
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
				while(board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == perspective*2)
				{
					count++;
					nextUpLeft(v_temp,l_temp,r_temp);
					if(!check(v_temp,l_temp,r_temp))
						break;
				}
				v_up = v_temp;
				l_up = l_temp;
				r_up = r_temp;
				v_temp = v;
				l_temp = l;
				r_temp = r;
				while(board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == perspective*2)
				{
					count++;
					nextDownRight(v_temp,l_temp,r_temp);
					if(!check(v_temp,l_temp,r_temp))
						break;
				}
				if (count >= sequenceLength)
				{
					nextDownRight(v_up,l_up,r_up);
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
				while(board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == perspective*2)
				{
					count++;
					nextUpRight(v_temp,l_temp,r_temp);
					if(!check(v_temp,l_temp,r_temp))
						break;
				}
				v_up = v_temp;
				l_up = l_temp;
				r_up = r_temp;
				v_temp = v;
				l_temp = l;
				r_temp = r;
				while(board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == perspective*2)
				{
					count++;
					nextDownLeft(v_temp,l_temp,r_temp);
					if(!check(v_temp,l_temp,r_temp))
						break;
				}
				if (count >= sequenceLength)
				{
					nextDownLeft(v_up,l_up,r_up);
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



//checked
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
			}

		}
	}
	// return false;
}


//all checked from here
bool Board::check (int v, int l, int r) 
{
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

void Board::executeCommand (string command,int perspective) 
{
	int i=0;
	cerr<<"command received for execution: "<<command<<endl;
	cerr << command.size()<<endl;
	while(i<command.size())
	{
		cerr<<i<<endl;
		cerr<<command.at(i)<<endl;
		
		if(command.at(i) == 'P')
		{
			int h,p;
			i++;
			i++;
			int j = i,count = 0;
			while(i<command.size())
			{
				if (command.at(i) == ' ')
					break;
				i++;
				count++;
			}
			h = stoi(command.substr(j,count));
			i++;
			j = i;
			count = 0;
			while(i<command.size())
			{
				if (command.at(i) == ' ')
					break;
				i++;
				count++;
			}
			// cerr<<"here again"<<endl;
			p = stoi(command.substr(j,count));
			i++;
			//call the func to add a ring
			addRing(perspective,h,p);
		}
		else if (command.at(i) == 'S')
		{
			int h1,p1,h2,p2;
			i++;
			i++;
			int j = i,count = 0;
			while(i<command.size())
			{
				if (command.at(i) == ' ')
					break;
				i++;
				count++;
			}
			h1 = stoi(command.substr(j,count));
			i++;
			j = i;
			count = 0;
			while(i<command.size())
			{
				if (command.at(i) == ' ')
					break;
				i++;
				count++;
			}
			p1 = stoi(command.substr(j,count));
			i++;
			if (command.at(i) == 'M')
			{
				i++;
				i++;
				j = i;
				count = 0;
				while(i<command.size())
				{
					if (command.at(i) == ' ')
						break;
					i++;
					count++;
				}
				h2 = stoi(command.substr(j,count));
				i++;
				j = i;
				count = 0;
				while(i<command.size())
				{
					if (command.at(i) == ' ')
						break;
					i++;
					count++;
				}
				p2 = stoi(command.substr(j,count));
				i++;
				
				//call the func for move the ring 
				moveRing(h1,p1,h2,p2);	
			}
			else
			{
				cerr<<"ERROR!!! in parser"<<endl;
			}

		}
		else if (command.substr(i,2) == "RS")
		{
			i=i+2;
			int h1,p1,h2,p2;
			i++;
			int j = i,count = 0;
			while(i<command.size())
			{
				if (command.at(i) == ' ')
					break;
				i++;
				count++;
			}
			h1 = stoi(command.substr(j,count));
			i++;
			j = i;
			count = 0;
			while(i<command.size())
			{
				if (command.at(i) == ' ')
					break;
				i++;
				count++;
			}
			p1 = stoi(command.substr(j,count));
			i++;

			if (command.substr(i,2) == "RE")
			{
				i=i+2;
				i++;
				j = i;
				count = 0;
				while(i<command.size())
				{
					if (command.at(i) == ' ')
						break;
					i++;
					count++;
				}
				h2 = stoi(command.substr(j,count));
				i++;
				j = i;
				count = 0;
				while(i<command.size())
				{
					if (command.at(i) == ' ')
						break;
					i++;
					count++;
				}
				p2 = stoi(command.substr(j,count));
				i++;
				
				//call the func to remove the row
				// cerr<<"removing row"<<endl;
				removeRow(h1,p1,h2,p2);

				
			}
			else
			{
				cerr<<"ERROR!!!! in parser"<<endl;
			}
		}
		else if (command.at(i) == 'X')
		{
			int h3,p3;
			i++;
			i++;
			int j = i,count = 0;
			while(i<command.size())
			{
				if (command.at(i) == ' ')
					break;
				i++;
				count++;
			}
			h3 = stoi(command.substr(j,count));
			i++;
			j = i;
			count = 0;
			while(i<command.size())
			{
				if (command.at(i) == ' ')
					break;
				i++;
				count++;
			}
			p3 = stoi(command.substr(j,count));
			i++;
			removeRing(h3,p3);
		
		}
		else
		{
			i++;
		}
	}

}

void Board::undoCommand (string command,int perspective) 
{
	cerr<<"command received for undo: "<<command<<endl;
	int i=0;
	while(i<command.size())
	{
		if(command.at(i) == 'P')
		{
			int h,p;
			i++;
			i++;
			int j = i,count = 0;
			while(i<command.size())
			{
				if (command.at(i) == ' ')
					break;
				i++;
				count++;
			}
			h = stoi(command.substr(j,count));
			i++;
			j = i;
			count = 0;
			while(i<command.size())
			{
				if (command.at(i) == ' ')
					break;
				i++;
				count++;
			}
			// cerr<<"here again"<<endl;
			p = stoi(command.substr(j,count));
			i++;
			//call the func to add a ring
			undoAddRing(h,p);
		}
		else if (command.at(i) == 'S')
		{
			int h1,p1,h2,p2;
			i++;
			i++;
			int j = i,count = 0;
			while(i<command.size())
			{
				if (command.at(i) == ' ')
					break;
				i++;
				count++;
			}
			h1 = stoi(command.substr(j,count));
			i++;
			j = i;
			count = 0;
			while(i<command.size())
			{
				if (command.at(i) == ' ')
					break;
				i++;
				count++;
			}
			p1 = stoi(command.substr(j,count));
			i++;
			if (command.at(i) == 'M')
			{
				i++;
				i++;
				j = i;
				count = 0;
				while(i<command.size())
				{
					if (command.at(i) == ' ')
						break;
					i++;
					count++;
				}
				h2 = stoi(command.substr(j,count));
				i++;
				j = i;
				count = 0;
				while(i<command.size())
				{
					if (command.at(i) == ' ')
						break;
					i++;
					count++;
				}
				p2 = stoi(command.substr(j,count));
				i++;
				
				//call the func for move the ring 	
				// cerr<<"call undo move ring func"<<endl;
				undoMoveRing(h1,p1,h2,p2);

			}
			else
			{
				cerr<<"ERROR!!! in parser"<<endl;
			}

		}
		else if (command.substr(i,2) == "RS")
		{
			i=i+2;
			int h1,p1,h2,p2;
			i++;
			int j = i,count = 0;
			while(i<command.size())
			{
				if (command.at(i) == ' ')
					break;
				i++;
				count++;
			}
			h1 = stoi(command.substr(j,count));
			i++;
			j = i;
			count = 0;
			while(i<command.size())
			{
				if (command.at(i) == ' ')
					break;
				i++;
				count++;
			}
			p1 = stoi(command.substr(j,count));
			i++;

			if (command.substr(i,2) == "RE")
			{
				i=i+2;
				i++;
				j = i;

				count = 0;
				while(i<command.size())
				{
					if (command.at(i) == ' ')
						break;
					i++;
					count++;
				}
				h2 = stoi(command.substr(j,count));
				i++;
				j = i;
				count = 0;
				while(i<command.size())
				{
					if (command.at(i) == ' ')
						break;
					i++;
					count++;
				}
				p2 = stoi(command.substr(j,count));
				i++;
				

					//call the func to remove the row
					undoRemoveRow(perspective,h1,p1,h2,p2);
					
			}

			else
			{
				cerr<<"ERROR!!!! in parser"<<endl;
			}

		}
		else if (command.at(i) == 'X')
		{
			int h3,p3;
			i++;
			i++;
			int j = i,count = 0;
			while(i<command.size())
			{
				if (command.at(i) == ' ')
					break;
				i++;
				count++;
			}
			h3 = stoi(command.substr(j,count));
			i++;
			j = i;
			count = 0;
			while(i<command.size())
			{
				if (command.at(i) == ' ')
					break;
				i++;
				count++;
			}
			p3 = stoi(command.substr(j,count));
			i++;
			undoRemoveRing(perspective,h3,p3);
		
		}
		else
		{
			i++;
		}
	}
}


void Board::print_board()
{
	int j = 0;
	for(int v = -boardSize; v<0; v++)
	{
		for(int i = 0; i<boardSize*2 - j; i++)
			cerr<<" ";
		j++;
		for(int l = 0 - v - boardSize; l<=boardSize; l++)
		{
			int r = -v-l;
			if (check(v,l,r))
			{
				if (board[v+boardSize][l+boardSize][r+boardSize] == -1)
					cerr<<"a ";
				else if (board[v+boardSize][l+boardSize][r+boardSize] == -2)
					cerr<<"b ";
				else if (board[v+boardSize][l+boardSize][r+boardSize] == 0)
					cerr<<"_ ";
				else
					cerr<<board[v+boardSize][l+boardSize][r+boardSize]<<" ";

			}
			else 
				cerr<<"  ";
		}
		cerr<<endl;
	}
	
	for(int v = 0; v<=boardSize; v++)
	{
		for(int i = 0; i<boardSize*2 - j; i++)
			cerr<<" ";
		j--;
		for(int l = -boardSize; l<=boardSize-v; l++)
		{
			int r = -v-l;
			if (check(v,l,r))
			{
				if (board[v+boardSize][l+boardSize][r+boardSize] == -1)
					cerr<<"a ";
				else if (board[v+boardSize][l+boardSize][r+boardSize] == -2)
					cerr<<"b ";
				else if (board[v+boardSize][l+boardSize][r+boardSize] == 0)
					cerr<<"_ ";
				else
					cerr<<board[v+boardSize][l+boardSize][r+boardSize]<<" ";
			}
			else
				cerr<<"  ";
		}
		cerr<<endl;
	}
}
