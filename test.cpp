#include<iostream>
#include<string.h>
using namespace std;

bool check (int v, int l, int r) {
	if(abs(v) > 5 || abs(l) > 5 || abs(r) > 5)
		return false;
	if ((abs(v) == 5 && abs(l) == 5) || (abs(l) == 5 && abs(r) == 5) || (abs(r) == 5 && abs(v) == 5))
		return false;

	return true;
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

	int *** board = tempBoard;


	for(int v = -boardSize; v<0; v++)
	{
		for(int l = 0 - v - boardSize; l<=boardSize; l++)
		{
			int r = -v-l;
			if (check(v,l,r))
			{
				cout<<board[v+boardSize][l+boardSize][r+boardSize]<<" ";
				// cout<<v<<l<<r<<" ";
			}
			else 
				cout<<" ";
		}
		cout<<endl;
	}


	for(int v = 0; v<boardSize; v++)
	{
		for(int l = -boardSize; l<boardSize-v; l++)
		{
			int r = -v-l;
			if (check(v,l,r))
			{
				cout<<board[v+boardSize][l+boardSize][r+boardSize]<<" ";
				// cout<<v<<l<<r<<" ";
			}
			else
				cout<<" ";
		}
		cout<<endl;
	}
	return 0;
}