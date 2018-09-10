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

void YinshBot::executeCommand (string command) {

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
