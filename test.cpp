#include<iostream>
#include<string.h>
using namespace std;
int boardSize = 5;
int*** board;
int numRings=0,numOppRings=0;

bool check (int v, int l, int r) {
	if(abs(v) > 5 || abs(l) > 5 || abs(r) > 5)
		return false;
	if ((abs(v) == 5 && abs(l) == 5) || (abs(l) == 5 && abs(r) == 5) || (abs(r) == 5 && abs(v) == 5))
		return false;

	return true;
}

void print_board()
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
				else if (board[v+boardSize][l+boardSize][r+boardSize] == 0)
					cout<<"_ ";
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
				else if (board[v+boardSize][l+boardSize][r+boardSize] == 0)
					cout<<"_ ";
				else
					cout<<board[v+boardSize][l+boardSize][r+boardSize]<<" ";
			}
			else
				cout<<"  ";
		}
		cout<<endl;
	}
}


void convertTo (int hexagonNum, int position, int& v, int& l, int& r) 
{
	
	int segment = 0;

	if(hexagonNum == 0) 
	{ 
		v = 0; l = 0; r = 0; 
	}
	else 
	{
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

void convertBack (int v, int l, int r, int& hexagonNum, int& position) 
{
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


void addRing (int colour, int hexagonNum, int position) 
{
	
	int v, l, r = 0;
	convertTo(hexagonNum, position, v, l, r);
	cout<<v<<" "<<l<<" "<<r<<endl;
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

int main()
{
	int size = 5;
	int boardSize = 5;
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

	print_board();
	addRing(1,3,5);
	cout<<endl;
	print_board();
	addRing(-1,0,0);
	cout<<endl;
	print_board();
	addRing(1,5,17);
	cout<<endl;
	print_board();

	return 0;
}