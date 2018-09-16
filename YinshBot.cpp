//****************************

// Main functions left, parser for execute and undo Command, and eval function.

//****************************

//////////////////////////////

// Major things left alpha beta pruning(including ordering of moves) and depth differentiation based on move likability.

////////////////////////////


#include "YinshBot.h"

YinshBot::YinshBot () {

}

YinshBot::YinshBot (int n, int m, int k, int l, int startTurn) {
	boardSize = n;
	maxRings = m;
	SequenceLength = k;
	ringsToWin = l;
	turn = startTurn;
	board = new Board(n, m, k, l);
}

void YinshBot::print_board()
{
	board->print_board();
}

void YinshBot::changeTurn() {
	turn = -1*turn;
}

string YinshBot::findNextMove (int depth) {

	string move = "";
	vector<string> bestMoves;
	miniMax(depth, turn, bestMoves);
	// cout<<"Size: " << bestMoves.size() << endl;
	// for(int i = 0; i < bestMoves.size(); i++) {
	// 	cout<<bestMoves.at(i)<<endl;
	// }
	return bestMoves.at(bestMoves.size() - 1);
}

double YinshBot::miniMax(int depth, int perspective, vector<string>& bestMoves) {
	
	// int a = std::numeric_limits<int>::max();
	double score;
	if (perspective == 1)
		score = numeric_limits<int>::min();
	else
		score = numeric_limits<int>::max();
	double tempScore = 0;
	string tempMove = "";
	string move = "";

	if(depth == 0) {
		cout<<"Eval: " << evalFunction()<<endl;
		cout<<"Score: "<<score<<endl;
		return evalFunction();
	}
	else {
		vector<string> moves = moveList(perspective);
		for(int i = 0; i < moves.size(); i++) {
			cout << "Move: " << moves.at(i) << endl;
		}
		for(int i = 0; i < moves.size(); i++) {
			cout << "Trying move: " << moves.at(i) << endl;
			tempMove = moves.at(i);
			board->executeCommand(tempMove,perspective);
			cout<<"^^^^^"<<endl;
			tempScore = miniMax(depth - 1, -1*perspective, bestMoves);
			if(perspective == 1) {
				if(abs(tempScore - score) < 0.0001 || (tempScore - score) > 0.0001) {
					cout<<"*************************************8"<<endl;
					cout << "Max" << endl;
					score = tempScore;
					move = tempMove;
				}
			}
			else {
				if(abs(tempScore - score) < 0.0001 || (score - tempScore) > 0.0001) {
					cout<<"*************************************8"<<endl;
					cout << "Min" << endl;
					score = tempScore;
					move = tempMove;
				}
			}
			board->undoCommand(tempMove,perspective);
		}
		bestMoves.push_back(move);
		return score;
	}
}

vector<string> YinshBot::moveList(int perspective) 
{

	return board->generateMoveList(perspective);
}

bool YinshBot::checkGameEnd() 
{

}

void YinshBot::executeCommand(string s, int perspective) {
	board->executeCommand(s, perspective);
}

void YinshBot::undoCommand(string s, int perspective) {
	board->undoCommand(s, perspective);
}

double YinshBot::evalFunction () {
	double weight1 = 10;
	double weight2 = -5;
	double weight3 = 20;
	double weight4 = -15;
	double weight5 = 50;
	double weight6 = -70;

	double eval = 0;
	eval = eval + (weight1 * board->getNumDiscs()) + (weight2 * board->getNumOppDiscs());
	eval = eval + (weight3 * board->getNumRings()) + (weight4 * board->getNumOppRings());
	eval = eval + (weight5 * board->getRingsScored()) + (weight6 * board->getOppRingsScored());
	return eval;
}
