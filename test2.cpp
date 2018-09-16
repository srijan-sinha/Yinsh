#include<iostream>
#include<bits/stdc++.h>
#include<string>
using namespace std;

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


void undoCommand (string command,int perspective) 
{
	cerr<<"command received for undo: "<<command<<endl;
	int i=command.size()-1;
	int count=0;
	int h1,p1,h2,p2,h3,p3;
			
	while(i>0)
	{
		int h,p;
		count=0;

		while(command.at(i) != ' ')
		{
			i--;
			count++;
			if (i==0)
				return;
		}
		p = stoi(command.substr(i+1,count));
		i--;

		count=0;
		while(command.at(i) != ' ')
		{
			i--;
			count++;

			if (i==0)
				return;
		}
		h = stoi(command.substr(i+1,count));
		i--;	

		if (command.at(i) == 'P')
		{
			//undoMoveRing

			// undoAddRing(h,p);
			cout<<"undoAddRing"<<endl;

		}
		else if (command.at(i) == 'M')
		{
			i=i-2;
			count=0;
			while(command.at(i) != ' ')
			{
				i--;
				count++;

				if (i==0)
					return;
			}
			p2 = stoi(command.substr(i+1,count));
			i--;

			count=0;
			while(command.at(i) != ' ')
			{
				i--;
				count++;

				if (i==0)
					return;
			}
			h2 = stoi(command.substr(i+1,count));
			i--;
			i=i-2;
			h1 = h;
			p1 = p;
			//undoMoveRings
			
			// undoMoveRing(h2,p2,h1,p1);
			cout<<"undoMoveRings"<<endl;
			cout<<h2<<p2<<h1<<p1<<endl;
		}
		else if (command.at(i) == 'X')
		{
			h1 = h;
			p1 = p;
			i-=2;
			// undoRemoveRing(perspective,h1,p1);
			// cout<<command.at(i)<<endl;
			cout<<"undoRemoveRing";
			cout<<h1<<p1<<endl;
			
		}
		else if (command.at(i) == 'E')
		{	

			h2 = h;
			p2 = p;
			i=i-3;

			count=0;
			while(command.at(i) != ' ')
			{
				i--;
				count++;
				if (i==0)
					return;
			}
			p3 = stoi(command.substr(i+1,count));
			i--;

			count=0;
			while(command.at(i) != ' ')
			{
				i--;
				count++;
				if (i==0)
					break;
			}
			h3 = stoi(command.substr(i+1,count));
			i-=4;
			cout<<command.at(i)<<endl;
			
			// undoRemoveRow(perspective,h3,p3,h2,p2);
			cout<<"undoRemoveRow"<<endl;
			cout<<h3<<p3<<h2<<p2<<endl;	
		}
		
	}
}	

int main()
{
	
	undoCommand("P 2 3",1);
	undoCommand("S 2 3 M 4 5",1);
	undoCommand("X 5 6",1);
	undoCommand("S 1 1 M 5 14 RS 1 1 RE 5 1 X 5 6",1);

	return 0;
}