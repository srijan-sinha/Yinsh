#include<iostream>
#include<string.h>
#include<bits/stdc++.h>
using namespace std;
int boardSize = 5;
int*** board;
int numRings=0,numOppRings=0;
int numDiscs,numOppDiscs;
int ringsScored,oppRingsScored;
vector<int> ringV,ringR,ringL,ringV_opp,ringR_opp,ringL_opp;
int sequenceLength = 5;

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

vector<int> row_detect(int hexagon1, int position1, int hexagon2, int position2, int perspective)
{
	int v1, l1, r1, v2, l2, r2 = 0;
	convertTo(hexagon1, position1, v1, l1, r1);
	convertTo(hexagon2, position2, v2, l2, r2);
	int count,v_temp,l_temp,r_temp,v_up,l_up,r_up;
		
	vector<int> vect;
	if (v1 == v2)
	{
		int v = v1;
		int l_start = min(l1,l2) ,l_end = max(l1,l2);
		for(int i=l_start; i<=l_end; i++)
		{
			count = 0;
			v_temp = v;
			l_temp = i;
			r_temp = -v-i;

				cout<<"checking for the point "<<v_temp<<" "<<l_temp<<" "<<r_temp<<endl;
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
					cout<<"up coordi: "<<v_up<<l_up<<r_up<<endl;
					convertBack(v_temp,l_temp,r_temp,h2,p2);
					cout<<"up coordi: "<<v_temp<<l_temp<<r_temp<<endl;
					vect.push_back(h1);
					vect.push_back(p1);
					vect.push_back(h2);
					vect.push_back(p2);
					
					return vect;
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
					vect.push_back(h1);
					vect.push_back(p1);
					vect.push_back(h2);
					vect.push_back(p2);
					
					return vect;
				}

				v_temp = v;
				l_temp = i;
				r_temp = -v-i;
				int h,p;
				convertBack(v,i,-v-i,h,p);

				
				cout<<"checking for the point "<<v_temp<<" "<<l_temp<<" "<<r_temp<<endl;
				cout<<board[v+boardSize][i+boardSize][-v-i+boardSize]<<endl;
				//check vertical row
				

				nextUp(v_temp,l_temp,r_temp);
				cout<<"checking for the point "<<v_temp<<" "<<l_temp<<" "<<r_temp<<endl;
				cout<<board[v_temp+boardSize][l_temp+boardSize][r_temp+boardSize]<<endl;
				while(board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == perspective*(2))
				{
					count++;
					nextUp(v_temp,l_temp,r_temp);
				}
				v_up = v_temp;
				l_up = l_temp;
				r_up = r_temp;
				v_temp = v;
				l_temp = i;
				r_temp = -v-i;
				nextDown(v_temp,l_temp,r_temp);
				if (check(v_temp,l_temp,r_temp))
				{
					while(board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == perspective*(2))
					{
						count++;
						nextDown(v_temp,l_temp,r_temp);
						if(check(v_temp,l_temp,r_temp))
							break;
					}
				}	
				cout<<count<<endl;
				if (count >= sequenceLength-1)
				{
					nextUp(v_temp,l_temp,r_temp);
					nextDown(v_up,l_up,r_up);
				
					int h1,p1,h2,p2;
					convertBack(v_up,l_up,r_up,h1,p1);
					convertBack(v_temp,l_temp,r_temp,h2,p2);
					vect.push_back(h1);
					vect.push_back(p1);
					vect.push_back(h2);
					vect.push_back(p2);
					
					return vect;
				}
				
			}

		}
		
		
	}
	else if (l1 == l2)
	{
		int l = l1;
		int v_start = min(v1,v2) ,v_end = max(v1,v2);
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
					vect.push_back(h1);
					vect.push_back(p1);
					vect.push_back(h2);
					vect.push_back(p2);
					
					return vect;
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
					vect.push_back(h1);
					vect.push_back(p1);
					vect.push_back(h2);
					vect.push_back(p2);
					
					return vect;
				}


				//check left axis row
				v_temp = i;
				l_temp = l;
				r_temp = -l-i;

				nextUpLeft(v_temp,l_temp,r_temp);
				while(board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == perspective*(2))
				{
					count++;
					nextUpLeft(v_temp,l_temp,r_temp);
				}
				v_up = v_temp;
				l_up = l_temp;
				r_up = r_temp;
				v_temp = i;
				l_temp = l;
				r_temp = -l-i;
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
					vect.push_back(h1);
					vect.push_back(p1);
					vect.push_back(h2);
					vect.push_back(p2);
					
					return vect;
				}
			}
		}	
		
	}
	else if (r1 == r2)
	{
		int r = r1;
		int l_start = min(l1,l2) ,l_end = max(l1,l2);
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
					vect.push_back(h1);
					vect.push_back(p1);
					vect.push_back(h2);
					vect.push_back(p2);
					
					return vect;
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
					vect.push_back(h1);
					vect.push_back(p1);
					vect.push_back(h2);
					vect.push_back(p2);
					
					return vect;
				}


				//check right axis row
				v_temp = -r-i;
				l_temp = i;
				r_temp = r;

				nextUpRight(v_temp,l_temp,r_temp);
				while(board[v_temp + boardSize][l_temp + boardSize][r_temp + boardSize] == perspective*(2))
				{
					count++;
					nextUpRight(v_temp,l_temp,r_temp);
				}
				v_up = v_temp;
				l_up = l_temp;
				r_up = r_temp;
				v_temp = -r-i;
				l_temp = i;
				r_temp = r;
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
					vect.push_back(h1);
					vect.push_back(p1);
					vect.push_back(h2);
					vect.push_back(p2);
					
					return vect;
				}

				
			}
		}
		
	}
	else
	{
		cout << "Error! Given points (" <<  hexagon1 << "," << position1 << ") and (" <<  hexagon2 << "," << position2 << ") are not on same line" << endl;
		cout << "Above error printed in Board.cpp: Row_detect" << endl;	
	}
	return vect;
}

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
	
	// int v,l,r;
	// convertTo(3,0,v,l,r);
	// cout<<v<<l<<r<<endl;
	// int h,p;
	// convertBack(0,1,-1,h,p);
	// cout<<h<<p<<endl;
	

	addRing(1,3,5);
	cout<<endl;
	print_board();
	
	addRing(-1,0,0);
	cout<<endl;
	print_board();
	
	addRing(1,5,17);
	cout<<endl;
	print_board();
	
	addRing(-1,4,23);
	cout<<endl;
	print_board();

	addRing(-1,1,3);
	cout<<endl;
	print_board();
	
	moveRing(3,5,3,3);
	cout<<endl;
	print_board();
	
	moveRing(3,3,3,6);
	cout<<endl;
	print_board();
	
	moveRing(4,23,5,1);
	cout<<endl;
	print_board();
	
	moveRing(5,1,4,22);
	cout<<endl;
	print_board();
	
	moveRing(5,17,4,14);
	cout<<endl;
	print_board();

	moveRing(4,14,3,11);
	cout<<endl;
	print_board();

	moveRing(3,11,2,8);
	cout<<endl;
	print_board();

	moveRing(2,8,2,9);
	cout<<endl;
	print_board();
	
	vector<int> row;
	row = row_detect(2,9,2,10,1);
	cout<<endl;
	cout<<"4444444444444444444"<<endl;
	for(int i=0;i<row.size();i++)
		cout<<row.at(i)<<" ";
	cout<<endl;
	print_board();
	

	// moveRing(2,9,2,10);
	// cout<<endl;
	// print_board();

	moveRing(0,0,1,0);
	cout<<endl;
	print_board();
	
	moveRing(1,0,2,0);
	cout<<endl;
	print_board();
	
	moveRing(2,0,3,0);
	cout<<endl;
	print_board();
	
	moveRing(3,0,4,0);
	cout<<endl;
	print_board();

	moveRing(4,0,4,1);
	cout<<endl;
	print_board();
	
	moveRing(1,3,2,6);
	cout<<endl;
	print_board();
	
	cout<<"numRings: "<<numRings<<" numOppRings: "<<numOppRings<<" numDiscs: "<<numDiscs<<" numOppDiscs: "<<numOppDiscs<<endl;

	print_ring_vectors();
	
	// removeRing(5,17);
	// cout<<endl;
	// print_board();
	
	cout<<"numRings: "<<numRings<<" numOppRings: "<<numOppRings<<" numDiscs: "<<numDiscs<<" numOppDiscs: "<<numOppDiscs<<endl;
	
	print_ring_vectors();
	
	cout<<endl;
	// int v=0,l=0,r=0;
	// nextUp(v,l,r);
	// cout<<v<<l<<r<<endl;

	// int v1,l1,r1,v2,l2,r2;
	// cout<<row_detected(v1,l1,r1,v2,l2,r2,1)<<endl;
	// cout<<v1<<l1<<r1<<" "<<v2<<l2<<r2<<endl;
	// cout<<row_detected(v1,l1,r1,v2,l2,r2,-1)<<endl;
	// cout<<v1<<l1<<r1<<" "<<v2<<l2<<r2<<endl;
	cout<<endl;
	vector< vector<int> > s,e;
	row_detected_modified(s,e,-1);
	for(int i=0;i<s.size();i++)
	{
		for(int j=0;j<3;j++)
		{
			cout<<s.at(i).at(j);
		}
		cout<<" ";
		for(int j=0;j<3;j++)
		{
			cout<<e.at(i).at(j);
		}
		cout<<endl;
	}

	return 0;
}