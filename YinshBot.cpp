//****************************

// Main functions left, parser for execute and undo Command, and eval function.

//****************************

//////////////////////////////

// Major things left alpha beta pruning(including ordering of moves) and depth differentiation based on move likability.

////////////////////////////


#include "YinshBot.h"

YinshBot::YinshBot () {

}

YinshBot::YinshBot (int n, int m, int k, int l) {
	boardSize = n;
	maxRings = m;
	sequenceLength = k;
	ringsToWin = l;
	turn = startTurn;
	board = new Board(n, m, k, l);
}

void YinshBot::executeCommand (string command) 
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

void YinshBot::undoCommand (string command) {

}

string YinshBot::findNextMove () {

	string move = "";
	miniMax(5, turn, move);

}

int YinshBot::miniMax(int depth, int perspective, string& move) {
	
	vector<string> moves = moveList();
	int score = 0;
	int tempScore = 0;
	string tempMove = "";

	if(depth == 0) {
		return evalFunction();
	}
	else {
		for(int i = 0; i < moves.size(); i++) {
			tempMove = moves.at(i);
			executeCommand(tempMove);
			tempScore = minimax(depth - 1, -1*perspective);
			if(perspective == 1) {
				if(tempScore > score) {
					score = tempScore;
					move = tempMove;
				}
			}
			else {
				if(tempScore < score) {
					score = tempScore;
					move = tempMove;
				}
			}
			undoCommand(tempMove);
		}
	}
}

vector<string> YinshBot::moveList() {
	return Board->generateMoveList();
}

bool YinshBot::checkGameEnd () {

}

double YinshBot::evalFunction () {
	
}
