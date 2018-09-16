#include<iostream>
#include<string.h>
#include<bits/stdc++.h>
using namespace std;


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

void undoAddRing(int hexagonNum, int position) 
{
	int v, l, r = 0;
	convertTo(hexagonNum, position, v, l, r);
	cout<<board[v + boardSize][l + boardSize][r + boardSize]<<endl;
	if(board[v + boardSize][l + boardSize][r + boardSize] != 1 && board[v + boardSize][l + boardSize][r + boardSize] != -1) {
		cout << "Error! Ring not found for removal! Hexagon number: " <<  hexagonNum << " Point number: " << position << endl;
		cout << "Above error printed in Board.cpp: undoAddRing." << endl;
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

void moveRing (int hexagon1, int position1, int hexagon2, int position2) 
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

void undoMoveRing(int hexagon1, int position1, int hexagon2, int position2) 
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


void removeRing (int hexagonNum, int position) {
	
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

void undoRemoveRing(int colour, int hexagonNum, int position) {
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


void removeRow (int hexagon1, int position1, int hexagon2, int position2) 
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
		cout << "Error! Given points (" <<  hexagon1 << "," << position1 << ") and (" <<  hexagon2 << "," << position2 << ") are not on same line" << endl;
		cout << "Above error printed in Board.cpp: removeRow." << endl;	
	}
}

void undoRemoveRow(int colour, int hexagon1, int position1, int hexagon2, int position2) {
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
		cout << "Error! Given points (" <<  hexagon1 << "," << position1 << ") and (" <<  hexagon2 << "," << position2 << ") are not on same line" << endl;
		cout << "Above error printed in Board.cpp: removeRow." << endl;	
	}
}


void print_ring_vectors()
{
	cout<<"rings of gamer"<<endl;
	for(int i=0;i<ringV.size();i++)
	{
		cout<<ringV.at(i)<<" "<<ringL.at(i)<<" "<<ringR.at(i)<<endl;
	}
	cout<<"rings of opp"<<endl;
	for(int i=0;i<ringV_opp.size();i++)
	{
		cout<<ringV_opp.at(i)<<" "<<ringL_opp.at(i)<<" "<<ringR_opp.at(i)<<endl;
	}
}

void nextUp(int& v, int& l, int& r) {
	l = l + 1;
	r = r - 1;
}

void nextDown (int& v, int& l, int& r) {
	l = l - 1;
	r = r + 1;
}

void nextUpRight (int& v, int& l, int& r) {
	v = v + 1;
	r = r - 1;
}

void nextUpLeft (int& v, int& l, int& r) {
	v = v - 1;
	l = l + 1;
}

void nextDownRight (int& v, int& l, int& r) {
	v = v + 1;
	l = l - 1;
}

void nextDownLeft (int& v, int& l, int& r) {
	v = v - 1;
	r = r + 1;
}


bool row_detected(int& v1, int& l1, int& r1, int& v2, int& l2, int& r2, int perspective)
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


// vector<int> row_detect(int hexagon1, int position1, int hexagon2, int position2, int perspective)
// {
// 	int v1, l1, r1, v2, l2, r2 = 0;
// 	convertTo(hexagon1, position1, v1, l1, r1);
// 	convertTo(hexagon2, position2, v2, l2, r2);
// 	vector<int> v;
// 	if (v1 == v2)
// 	{
// 		int v = v1;
// 		int l_start = min(l1,l2) ,l_end = max(l1,l2);
// 		int count,v_temp,l_temp,r_temp,v_up,l_up,r_up;
// 		int count_vert = 0;
// 		for(int i=l_start+1; i<=l_end; i++)
// 		{
// 			count = 0;
// 			v_temp = v;
// 			l_temp = i;
// 			r_temp = -v-i;
// 			if (check(v_temp,l_temp,r_temp))
// 			{
// 				//check along left axis;
// 				nextUpLeft(v_temp,l_temp,r_temp);
// 				while(board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == perspective*(2))
// 				{
// 					count++;
// 					nextUpLeft(v_temp,l_temp,r_temp);
// 				}
// 				v_up = v_temp;
// 				l_up = l_temp;
// 				r_up = r_temp;
// 				v_temp = v;
// 				l_temp = i;
// 				r_temp = -v-i;
// 				nextDownLeft(v_temp,l_temp,r_temp);
// 				while(board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == perspective*(2))
// 				{
// 					count++;
// 					nextDownLeft(v_temp,l_temp,r_temp);
// 				}
// 				if (count >= sequenceLength-1)
// 				{
// 					int h1,p1,h2,p2;
// 					convertBack(v_up,l_up,r_up,h1,p1);
// 					convertBack(v_temp,l_temp,r_temp,h2,p2);
// 					v.push_back(h1);
// 					v.push_back(p1);
// 					v.push_back(h2);
// 					v.push_back(p2);
					
// 					return v;
// 				}


// 				v_temp = v;
// 				l_temp = i;
// 				r_temp = -v-i;


// 				//check along right axis;
// 				nextUpRight(v_temp,l_temp,r_temp);
// 				while(board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == perspective*(2))
// 				{
// 					count++;
// 					nextUpRight(v_temp,l_temp,r_temp);
// 				}
// 				v_up = v_temp;
// 				l_up = l_temp;
// 				r_up = r_temp;
// 				v_temp = v;
// 				l_temp = i;
// 				r_temp = -v-i;
// 				nextDownRight(v_temp,l_temp,r_temp);
// 				while(board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == perspective*(2))
// 				{
// 					count++;
// 					nextDownRight(v_temp,l_temp,r_temp);
// 				}
// 				if (count >= sequenceLength-1)
// 				{
// 					int h1,p1,h2,p2;
// 					convertBack(v_up,l_up,r_up,h1,p1);
// 					convertBack(v_temp,l_temp,r_temp,h2,p2);
// 					v.push_back(h1);
// 					v.push_back(p1);
// 					v.push_back(h2);
// 					v.push_back(p2);
					
// 					return v;
// 				}


// 				//check vertical row
// 				v_temp = v;
// 				l_temp = i;
// 				r_temp = -v-i;

// 				if(board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == perspective*(-2))
// 					count_vert++;
				
// 			}

// 		}
// 		if (count_vert >= sequenceLength-1)
// 		{
// 			int h1,p1,h2,p2;
// 			convertBack(v,l_start,-v-l_start,h1,p1);
// 			convertBack(v,l_end,-v-l_end,h2,p2);
// 			v.push_back(h1);
// 			v.push_back(p1);
// 			v.push_back(h2);
// 			v.push_back(p2);
			
// 			return v;
// 		}
		
// 	}
// 	else if (l1 == l2)
// 	{
// 		int l = l1;
// 		int v_start = min(v1,v2) ,v_end = max(v1,v2);
// 		int count_left = 0;
// 		for(int i=v_start+1; i<=v_end; i++)
// 		{
// 			count = 0;
// 			v_temp = i;
// 			l_temp = l;
// 			r_temp = -l-i;
// 			if (check(v_temp,l_temp,r_temp))
// 			{
// 				//check along left axis;
// 				nextUp(v_temp,l_temp,r_temp);
// 				while(board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == perspective*(2))
// 				{
// 					count++;
// 					nextUp(v_temp,l_temp,r_temp);
// 				}
// 				v_up = v_temp;
// 				l_up = l_temp;
// 				r_up = r_temp;
// 				v_temp = i;
// 				l_temp = l;
// 				r_temp = -l-i;
// 				nextDown(v_temp,l_temp,r_temp);
// 				while(board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == perspective*(2))
// 				{
// 					count++;
// 					nextDown(v_temp,l_temp,r_temp);
// 				}
// 				if (count >= sequenceLength-1)
// 				{
// 					int h1,p1,h2,p2;
// 					convertBack(v_up,l_up,r_up,h1,p1);
// 					convertBack(v_temp,l_temp,r_temp,h2,p2);
// 					v.push_back(h1);
// 					v.push_back(p1);
// 					v.push_back(h2);
// 					v.push_back(p2);
					
// 					return v;
// 				}


// 				v_temp = i;
// 				l_temp = l;
// 				r_temp = -l-i;


// 				//check along right axis;
// 				nextUpRight(v_temp,l_temp,r_temp);
// 				while(board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == perspective*(2))
// 				{
// 					count++;
// 					nextUpRight(v_temp,l_temp,r_temp);
// 				}
// 				v_up = v_temp;
// 				l_up = l_temp;
// 				r_up = r_temp;
// 				v_temp = i;
// 				l_temp = l;
// 				r_temp = -l-i;
// 				nextDownRight(v_temp,l_temp,r_temp);
// 				while(board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == perspective*(2))
// 				{
// 					count++;
// 					nextDownRight(v_temp,l_temp,r_temp);
// 				}
// 				if (count >= sequenceLength-1)
// 				{
// 					int h1,p1,h2,p2;
// 					convertBack(v_up,l_up,r_up,h1,p1);
// 					convertBack(v_temp,l_temp,r_temp,h2,p2);
// 					v.push_back(h1);
// 					v.push_back(p1);
// 					v.push_back(h2);
// 					v.push_back(p2);
					
// 					return v;
// 				}


// 				//check left axis row
// 				v_temp = i;
// 				l_temp = l;
// 				r_temp = -l-i;

// 				if(board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == perspective*(-2))
// 					count_left++;
				
// 			}
// 		}	
// 		if (count_left >= sequenceLength-1)
// 		{
// 			int h1,p1,h2,p2;
// 			convertBack(v_start,l,-v_start-l,h1,p1);
// 			convertBack(v_end,l,-v_end-l,h2,p2);
// 			v.push_back(h1);
// 			v.push_back(p1);
// 			v.push_back(h2);
// 			v.push_back(p2);
			
// 			return v;
// 		}	
// 	}
// 	else if (r1 == r2)
// 	{
// 		int r = r1;
// 		int l_start = min(l1,l2) ,l_end = max(l1,l2);
// 		int count_right = 0;
// 		for(int i=l_start+1; i<=l_end; i++)
// 		{
// 			count = 0;
// 			v_temp = -r-i;
// 			l_temp = i;
// 			r_temp = r;
// 			if (check(v_temp,l_temp,r_temp))
// 			{
// 				//check along left axis;
// 				nextUpLeft(v_temp,l_temp,r_temp);
// 				while(board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == perspective*(2))
// 				{
// 					count++;
// 					nextUpLeft(v_temp,l_temp,r_temp);
// 				}
// 				v_up = v_temp;
// 				l_up = l_temp;
// 				r_up = r_temp;
// 				v_temp = -r-i;
// 				l_temp = i;
// 				r_temp = r;
// 				nextDownLeft(v_temp,l_temp,r_temp);
// 				while(board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == perspective*(2))
// 				{
// 					count++;
// 					nextDownLeft(v_temp,l_temp,r_temp);
// 				}
// 				if (count >= sequenceLength-1)
// 				{
// 					int h1,p1,h2,p2;
// 					convertBack(v_up,l_up,r_up,h1,p1);
// 					convertBack(v_temp,l_temp,r_temp,h2,p2);
// 					v.push_back(h1);
// 					v.push_back(p1);
// 					v.push_back(h2);
// 					v.push_back(p2);
					
// 					return v;
// 				}


// 				v_temp = -r-i;
// 				l_temp = i;
// 				r_temp = r;


// 				//check along right axis;
// 				nextUp(v_temp,l_temp,r_temp);
// 				while(board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == perspective*(2))
// 				{
// 					count++;
// 					nextUp(v_temp,l_temp,r_temp);
// 				}
// 				v_up = v_temp;
// 				l_up = l_temp;
// 				r_up = r_temp;
// 				v_temp = -r-i;
// 				l_temp = i;
// 				r_temp = r;
// 				nextDown(v_temp,l_temp,r_temp);
// 				while(board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == perspective*(2))
// 				{
// 					count++;
// 					nextDown(v_temp,l_temp,r_temp);
// 				}
// 				if (count >= sequenceLength-1)
// 				{
// 					int h1,p1,h2,p2;
// 					convertBack(v_up,l_up,r_up,h1,p1);
// 					convertBack(v_temp,l_temp,r_temp,h2,p2);
// 					v.push_back(h1);
// 					v.push_back(p1);
// 					v.push_back(h2);
// 					v.push_back(p2);
					
// 					return v;
// 				}


// 				//check right axis row
// 				v_temp = -r-i;
// 				l_temp = i;
// 				r_temp = r;

// 				if(board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == perspective*(-2))
// 					count_right++;
				
// 			}
// 		}
// 		if (count_right >= sequenceLength-1)
// 		{
// 			int h1,p1,h2,p2;
// 			convertBack(-r-l_start,l_start,r,h1,p1);
// 			convertBack(-r-l_end,l_end,r,h2,p2);
// 			v.push_back(h1);
// 			v.push_back(p1);
// 			v.push_back(h2);
// 			v.push_back(p2);
			
// 			return v;
// 		}
// 	}
// 	else
// 	{
// 		cout << "Error! Given points (" <<  hexagon1 << "," << position1 << ") and (" <<  hexagon2 << "," << position2 << ") are not on same line" << endl;
// 		cout << "Above error printed in Board.cpp: Row_detect" << endl;	
// 	}

// }


void row_detected_modified(vector< vector<int> > &start, vector< vector<int> > &end, int perspective)
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

void executeCommand (string command,int perspective) 
{
	cout<<"command received: "<<command<<endl;
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
			cout<<"here again"<<endl;
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
				cout<<"ERROR!!! in parser"<<endl;
			}

		}
		else if (command.substr(i,2) == "RS")
		{
			i=i+2;
			int h1,p1,h2,p2,h3,p3;
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
				if (command.at(i) == 'X')
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

					//call the func to remove the row
					removeRow(h1,p1,h2,p2);
					removeRing(h3,p3);
				}
				else
				{
					cout<<"ERROR!!!!! in parser"<<endl;
				}
			}
			else
			{
				cout<<"ERROR!!!! in parser"<<endl;
			}
		}
	}
}

void undoCommand (string command,int perspective) 
{
	cout<<"command received: "<<command<<endl;
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
			cout<<"here again"<<endl;
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
				undoMoveRing(h1,p1,h2,p2);
			}
			else
			{
				cout<<"ERROR!!! in parser"<<endl;
			}

		}
		else if (command.substr(i,2) == "RS")
		{
			i=i+2;
			int h1,p1,h2,p2,h3,p3;
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
				if (command.at(i) == 'X')
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

					//call the func to remove the row
					undoRemoveRow(perspective,h1,p1,h2,p2);
					undoRemoveRing(perspective,h3,p3);
				}
				else
				{
					cout<<"ERROR!!!!! in parser"<<endl;
				}
			}
			else
			{
				cout<<"ERROR!!!! in parser"<<endl;
			}
		}
	}
}


vector<string> append(vector<string> A, vector<string> B)
{
	A.insert(A.end(), B.begin(), B.end());
	return A;
}

int lastLiteral(string s) 
{
	int i = s.size()-1;
	int count = 0;
	while(true)
	{
		if(s.at(i) == ' ')
			count++;
		i--;
		if (count == 2)
			break;
	}
	if(s.at(i) == 'E')
		return 1;
	else if (s.at(i) == 'X')
		return 2;
	else
		return 3;
	//returns 1 -> RE, 2 -> X, 3 -> M
}


bool contains(string s, char sub) 
{
	for (int i = 0; i < s.size(); ++i)
	{
		if (s.at(i) == sub)
			return true;
	}
	return false;
	//returns true if sub is contained in s. sub always has size 1. 
}

string end_part(string s)
{
	int i = s.size()-1;
	int count = 0;
	while(true)
	{
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

vector<string> addRingMoves (vector<string> moves) 
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

vector<string> moveRingMoves (vector<string> moves, int perspective, vector<int> ringV_local, vector<int> ringL_local, vector<int> ringR_local) 
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
			if (board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == 1 || board[v + boardSize][l_temp + boardSize][r_temp + boardSize] == -1)
				break;
			if (board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == 2 || board[v + boardSize][l_temp + boardSize][r_temp + boardSize] == -2)
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
			if (board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == 1 || board[v + boardSize][l_temp + boardSize][r_temp + boardSize] == -1)
				break;
			if (board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == 2 || board[v + boardSize][l_temp + boardSize][r_temp + boardSize] == -2)
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
			string s = "S " + to_string(hexagonNum1) + " " + to_string(position1);
			convertBack(v_temp, l_temp, r_temp, hexagonNum2, position2);
			s += " M " + to_string(hexagonNum2) + " " + to_string(position2);
			moves.push_back(s);
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
			string s = "S " + to_string(hexagonNum1) + " " + to_string(position1);
			convertBack(v_temp, l_temp, r_temp, hexagonNum2, position2);
			s += " M " + to_string(hexagonNum2) + " " + to_string(position2);
			moves.push_back(s);
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
			string s = "S " + to_string(hexagonNum1) + " " + to_string(position1);
			convertBack(v_temp, l_temp, r_temp, hexagonNum2, position2);
			s += " M " + to_string(hexagonNum2) + " " + to_string(position2);
			moves.push_back(s);
			if (marker)
				break;
		}
	
	}
	
	return moves;
}


vector<string> fullMoves(vector<string> moves, int perspective) {

	bool flag = true;
	vector<string> allMoves;
	for(int i = 0; i < moves.size(); i++) 
	{
		string t = end_part(moves.at(i));
		executeCommand(t,perspective);
		append(allMoves, fullMove(moves.at(i), perspective));
		undoCommand(t,perspective);
	}
}


vector<string> fullMove(string s, int perspective) 
{ 
	vector < vector<int> > start;
	vector < vector<int> > end;
	row_detected_modified(start, end, perspective);
	if(contains(s, 'M') && (lastLiteral(s) == 2 || lastLiteral(s) == 3)) 
	{ // 
		vector<string> additionalMoves;
		if((perspective == 1 && ringsScored == ringsToWin) || (perspective == -1 && oppRingsScored == ringsToWin)) {
			additionalMoves.push_back(s);
			return additionalMoves;
		}
		if(start.size() != 0) {
			int h1, p1, h2, p2 = 0;
			vector<string> deleteRowMoves;
			for(int i = 0; i < start.size(); i++) {
				convertBack(start.at(i).at(0), start.at(i).at(1), start.at(i).at(2), h1, p1);
				convertBack(end.at(i).at(0), end.at(i).at(1), end.at(i).at(2), h2, p2);
				deleteRowMoves.push_back("RS " + to_string(h1) + " "+ to_string(p1) + " RE "+ to_string(h2) + " " + to_string(p2));
			}
			// additionalMoves = fullMoves(deleteRowMoves, perspective);
			for(int i = 0; i < additionalMoves.size(); i++) {
				additionalMoves.at(i) = s + " " + additionalMoves.at(i);
			}
		}
		else {
			additionalMoves.push_back(s);
		}
		return additionalMoves;
	}
	else if(contains(s, 'M') && lastLiteral(s) == 1) {
		vector<string> deleteRingMove;
		vector<string> additionalMoves;
		int h, p;
		if(perspective == 1) {
			for(int i = 0; i < ringV.size(); i++) {
				convertBack(ringV.at(i), ringL.at(i), ringR.at(i), h, p);
				deleteRingMove.push_back("X" + to_string(h) + " " + to_string(p));
			}
		}
		else {
			for(int i = 0; i < ringV_opp.size(); i++) {
				convertBack(ringV_opp.at(i), ringL_opp.at(i), ringR_opp.at(i), h, p);
				deleteRingMove.push_back("X" + to_string(h) + " " + to_string(p));
			}
		}
		additionalMoves = fullMoves(deleteRingMove, perspective);
		for(int i = 0; i < additionalMoves.size(); i++) {
			additionalMoves.at(i) = s + " " + additionalMoves.at(i);
		}
		return additionalMoves;
	}
	else if(!(contains(s, 'M')) && (lastLiteral(s) == 2 || lastLiteral(s) == 4) ) 
	{ 
		
		vector<string> additionalMoves;
		if((perspective == 1 && ringsScored == ringsToWin) || (perspective == -1 && oppRingsScored == ringsToWin)) {
			additionalMoves.push_back(s);
			return additionalMoves;
		}

		if(start.size() == 0) 
		{
			vector<string> ringMove;
			if (perspective == 1)
				ringMove = moveRingMoves(ringMove, perspective, ringV, ringL, ringR);
			else
				ringMove = moveRingMoves(ringMove, perspective, ringV_opp, ringL_opp, ringR_opp);
				
			additionalMoves = fullMoves(ringMove, perspective);
			for(int i = 0; i < additionalMoves.size(); i++) {
				additionalMoves.at(i) = s + " " + additionalMoves.at(i);
			}
		}
		else {
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
	else if(!(contains(s, 'M')) && lastLiteral(s) == 1){
		vector<string> deleteRingMove;
		vector<string> additionalMoves;
		int h, p;
		if(perspective == 1) {
			for(int i = 0; i < ringV.size(); i++) {
				convertBack(ringV.at(i), ringL.at(i), ringR.at(i), h, p);
				deleteRingMove.push_back("X" + to_string(h) + " " + to_string(p));
			}
		}
		else {
			for(int i = 0; i < ringV_opp.size(); i++) {
				convertBack(ringV_opp.at(i), ringL_opp.at(i), ringR_opp.at(i), h, p);
				deleteRingMove.push_back("X" + to_string(h) + " " + to_string(p));
			}
		}
		additionalMoves = fullMoves(deleteRingMove, perspective);
		for(int i = 0; i < additionalMoves.size(); i++) {
			additionalMoves.at(i) = s + " " + additionalMoves.at(i);
		}
		return additionalMoves;
	}
	else {
		vector<string> additionalMoves;
		additionalMoves.push_back(s);
		return additionalMoves;
		cout << "Error! Code should not go into else!" << endl;
		cout << "Error printed in fullMove" << endl;
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

	addRing(1,0,0);
	cout<<endl;
	print_board();

	moveRing(0,0,3,0);
	cout<<endl;
	print_board();

	moveRing(3,0,1,3);
	cout<<endl;
	print_board();


	vector<string> m;
	m = addRingMoves(m);
	for(int i=0;i<m.size();i++)
	{
		cout<<m.at(i)<<endl;
	}
	cout<<m.size()<<endl;

	print_ring_vectors();

	vector<string> n;
	n = moveRingMoves(n,1,ringV,ringL,ringR);
	for(int i=0;i<n.size();i++)
	{
		cout<<n.at(i)<<endl;
	}
	cout<<n.size()<<endl;

	vector<string> o;
	o = fullMove("",1);
	for(int i=0;i<o.size();i++)
	{
		cout<<o.at(i)<<endl;
	}
	cout<<o.size()<<endl;

// vector<string> moveRingMoves (vector<string> moves, int perspective, vector<int> ringV_local, vector<int> ringL_local, vector<int> ringR_local) 


	// undoAddRing(0,0);
	// cout<<endl;
	// print_board();


	// addRing(1,5,14);
	// cout<<endl;
	// print_board();

	// addRing(1,5,16);
	// cout<<endl;
	// print_board();

	// addRing(-1,5,17);
	// cout<<endl;
	// print_board();

	// moveRing(5,14,4,12);
	// cout<<endl;
	// print_board();

	// undoMoveRing(5,14,4,12);
	// cout<<endl;
	// print_board();

	// moveRing(5,14,4,12);
	// cout<<endl;
	// print_board();

	// moveRing(4,12,4,13);
	// cout<<endl;
	// print_board();

	// moveRing(4,13,4,14);
	// cout<<endl;
	// print_board();

	// moveRing(4,14,4,15);
	// cout<<endl;
	// print_board();

	// //check row_detect()
	// //check remove row
	// //for last move check the row_detected
	
	// moveRing(4,15,4,16);
	// cout<<endl;
	// print_board();

	// vector< vector<int> > s,e;
	// row_detected_modified(s,e,1);
	// for(int i=0;i<s.size();i++)
	// {
	// 	for(int j=0;j<3;j++)
	// 	{
	// 		cout<<s.at(i).at(j);
	// 	}
	// 	cout<<" ";
	// 	for(int j=0;j<3;j++)
	// 	{
	// 		cout<<e.at(i).at(j);
	// 	}
	// 	cout<<endl;
	// }
	// cout<<"row_detected_modified completed"<<endl;
	// int v1,l1,r1,v2,l2,r2;
	// cout<<row_detected(v1,l1,r1,v2,l2,r2,1)<<endl;
	// cout<<v1<<l1<<r1<<" "<<v2<<l2<<r2<<endl;

	// moveRing(5,17,3,9);
	// cout<<endl;
	// print_board();


	// moveRing(5,16,3,10);
	// cout<<endl;
	// print_board();

	// removeRow(5,14,4,15);
	// cout<<endl;
	// print_board();

	// removeRing(4,16);
	// cout<<endl;
	// print_board();

	// undoRemoveRing(1,4,16);
	// cout<<endl;
	// print_board();

	// vector<string> m;
	// m = addRingMoves(m);
	// for(int i=0;i<m.size();i++)
	// {
	// 	cout<<m.at(i)<<endl;
	// }
	// cout<<m.size()<<endl;


 //    vector<string> a,b,c;
 //    a.push_back("0");
 //    a.push_back("1");
 //    b.push_back("2");
 //    c = append(a,b);
 //    cout<<endl;
 //    for (int i = 0; i < c.size(); ++i)
 //    {
 //    	cout<<c.at(i)<<" ";
 //    }
 //    cout<<endl;

 //    cout<<lastLiteral("S 67 7 M 44 5")<<endl;
	// cout<<contains("S 67 7 M 44 5",'X')<<endl;
	// cout<<end_part("RS 45 5 RE 5 6")<<endl;
	// // undoRemoveRow(1,5,14,4,15);
	// cout<<endl;
	// print_board();

//TESTCASE 1	
	// int v,l,r;
	// convertTo(3,0,v,l,r);
	// cout<<v<<l<<r<<endl;
	// int h,p;
	// convertBack(0,1,-1,h,p);
	// cout<<h<<p<<endl;
	

	// addRing(1,3,5);
	// cout<<endl;
	// print_board();
	
	// addRing(-1,0,0);
	// cout<<endl;
	// print_board();
	
	// addRing(1,5,17);
	// cout<<endl;
	// print_board();
	
	// addRing(-1,4,23);
	// cout<<endl;
	// print_board();

	// addRing(-1,1,3);
	// cout<<endl;
	// print_board();
	
	// moveRing(3,5,3,3);
	// cout<<endl;
	// print_board();
	
	// moveRing(3,3,3,6);
	// cout<<endl;
	// print_board();
	
	// moveRing(4,23,5,1);
	// cout<<endl;
	// print_board();
	
	// moveRing(5,1,4,22);
	// cout<<endl;
	// print_board();
	
	// moveRing(5,17,4,14);
	// cout<<endl;
	// print_board();

	// moveRing(4,14,3,11);
	// cout<<endl;
	// print_board();

	// moveRing(3,11,2,8);
	// cout<<endl;
	// print_board();

	// moveRing(2,8,2,9);
	// cout<<endl;
	// print_board();
	
	// vector<int> row;
	// row = row_detect(2,9,2,10,1);
	// cout<<endl;
	// cout<<"4444444444444444444"<<endl;
	// for(int i=0;i<row.size();i++)
	// 	cout<<row.at(i)<<" ";
	// cout<<endl;
	// print_board();
	

	// // moveRing(2,9,2,10);
	// // cout<<endl;
	// // print_board();

	// moveRing(0,0,1,0);
	// cout<<endl;
	// print_board();
	
	// moveRing(1,0,2,0);
	// cout<<endl;
	// print_board();
	
	// moveRing(2,0,3,0);
	// cout<<endl;
	// print_board();
	
	// moveRing(3,0,4,0);
	// cout<<endl;
	// print_board();

	// moveRing(4,0,4,1);
	// cout<<endl;
	// print_board();
	
	// moveRing(1,3,2,6);
	// cout<<endl;
	// print_board();
	
	// cout<<"numRings: "<<numRings<<" numOppRings: "<<numOppRings<<" numDiscs: "<<numDiscs<<" numOppDiscs: "<<numOppDiscs<<endl;

	// print_ring_vectors();
	
	// // removeRing(5,17);
	// // cout<<endl;
	// // print_board();
	
	// cout<<"numRings: "<<numRings<<" numOppRings: "<<numOppRings<<" numDiscs: "<<numDiscs<<" numOppDiscs: "<<numOppDiscs<<endl;
	
	// print_ring_vectors();
	
	// cout<<endl;
	// // int v=0,l=0,r=0;
	// // nextUp(v,l,r);
	// // cout<<v<<l<<r<<endl;

	// // int v1,l1,r1,v2,l2,r2;
	// // cout<<row_detected(v1,l1,r1,v2,l2,r2,1)<<endl;
	// // cout<<v1<<l1<<r1<<" "<<v2<<l2<<r2<<endl;
	// // cout<<row_detected(v1,l1,r1,v2,l2,r2,-1)<<endl;
	// // cout<<v1<<l1<<r1<<" "<<v2<<l2<<r2<<endl;
	// cout<<endl;
	// vector< vector<int> > s,e;
	// row_detected_modified(s,e,-1);
	// for(int i=0;i<s.size();i++)
	// {
	// 	for(int j=0;j<3;j++)
	// 	{
	// 		cout<<s.at(i).at(j);
	// 	}
	// 	cout<<" ";
	// 	for(int j=0;j<3;j++)
	// 	{
	// 		cout<<e.at(i).at(j);
	// 	}
	// 	cout<<endl;
	// }

	return 0;
}