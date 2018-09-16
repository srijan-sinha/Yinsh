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
	// cerr<<"Size: " << bestMoves.size() << endl;
	// for(int i = 0; i < bestMoves.size(); i++) {
	// 	cerr<<bestMoves.at(i)<<endl;
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

	if(depth == 0) 
	{
		// cerr<<"Eval: " << evalFunction()<<endl;
		return evalFunction();
	}
	else {
		vector<string> moves = moveList(perspective);
		
		for(int i = 0; i < moves.size(); i++) {
			// cerr << "Trying move: " << moves.at(i) << endl;
			tempMove = moves.at(i);
			
			board->executeCommand(tempMove,perspective);
			tempScore = miniMax(depth - 1, -1*perspective, bestMoves);

			cerr<<"possible move: "<<tempMove<<"with score: "<<tempScore<<"no of scored rings: "<<board->getRingsScored()<<endl;
			if(perspective == 1) {
				if(abs(tempScore - score) < 0.0001 || (tempScore - score) > 0.0001) {
					// cerr<<"*************************************8"<<endl;
					// cerr << "Max" << endl;
					score = tempScore;
					move = tempMove;
				}
			}
			else {
				if(abs(tempScore - score) < 0.0001 || (score - tempScore) > 0.0001) {
					// cerr<<"*************************************8"<<endl;
					// cerr << "Min" << endl;
					score = tempScore;
					move = tempMove;
				}
			}
			board->undoCommand(tempMove,perspective);
		}
		bestMoves.push_back(move);
		cerr<<endl<<"selected move: "<<move<<"with score: "<<score<<" no of scored rings: "<<board->getRingsScored()<<endl;

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

int YinshBot::getRingVLR(int perspective, int vlr, int i) {
	if(perspective == 1) {
		if(vlr == 1)
			return board->ringV.at(i);
		else if(vlr == 2)
			return board->ringL.at(i);
		else
			return board->ringR.at(i);
	}
	else {
		if(vlr == 1)
			return board->ringV_opp.at(i);
		else if(vlr == 2)
			return board->ringL_opp.at(i);
		else
			return board->ringR_opp.at(i);
	}
}

int YinshBot::ringAttacks() {
	int count = 0;
	for(int i = 0; i < board->getNumOppRings(); i++) {
		for(int j = 0; j < board->getNumRings(); j++) {
			if(board->checkLine(getRingVLR(-1, 1, i), getRingVLR(-1, 2, i), getRingVLR(-1, 3, i), getRingVLR(1, 1, j), getRingVLR(1, 2, j), getRingVLR(1, 3, j)))
				count++;
		}
	}
	return count;
}

double YinshBot::evalFunction () {
	double weight1 = 2;
	double weight2 = -3;
	double weight3 = 20;
	double weight4 = -15;
	double weight5 = 5000;
	double weight6 = -3000;
	double weight7 = 2;
	double weight8 = -1;
	double weight9 = 35;
	double weight10 = 15;
	double weight11 = -12;

	double eval = 0;

	if(board->getNumRings() < maxRings && board->getRingsScored() == 0) {
		int h, p = 1;
		for(int i = 0; i < board->getNumRings(); i++) {
			board->convertBack(getRingVLR(1, 1, i), getRingVLR(1, 2, i), getRingVLR(1, 3, i), h, p);
			eval = eval + (weight7 * (24/(h+1)));
		}
		for(int i = 0; i < board->getNumOppRings(); i++) {
			board->convertBack(getRingVLR(2, 1, i), getRingVLR(2, 2, i), getRingVLR(2, 3, i), h, p);
			eval = eval + (weight8 * (24/(h+1)));
		}
		eval = eval + (weight9 * ringAttacks());
	}
	else {
		eval = eval + (weight1 * board->getNumDiscs()) + (weight2 * board->getNumOppDiscs());
		eval = eval + (weight3 * board->getNumRings()) + (weight4 * board->getNumOppRings());
		eval = eval + (weight5 * board->getRingsScored()) + (weight6 * board->getOppRingsScored());
		if (board->getRingsScored() == 3)
			eval += numeric_limits<int>::max();
		// eval = eval + (weight10 * discsOurControl()) + (weight11 * discsOppControl());
	}
	return eval;
}
