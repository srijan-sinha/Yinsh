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
	miniMax(depth, turn, bestMoves, numeric_limits<int>::min(), numeric_limits<int>::max());
	// cerr<<"Size: " << bestMoves.size() << endl;
	// for(int i = 0; i < bestMoves.size(); i++) {
	// 	cerr<<bestMoves.at(i)<<endl;
	// }
	return bestMoves.at(bestMoves.size() - 1);
}

double YinshBot::miniMax(int depth, int perspective, vector<string>& bestMoves, double a, double b) {
	
	// int a = std::numeric_limits<int>::max();
	double score;
	if (perspective == 1)
		score = numeric_limits<int>::min();
	else
		score = numeric_limits<int>::max();
	double tempScore = 0;
	string tempMove = "";
	string move_min = "",move_max = "",move = "";

	if(depth == 0) 
	{
		// cerr<<"Eval: " << evalFunction()<<endl;
		return evalFunction();
	}
	else 
	{
		string bestMove;
		double bestVal;
		int indexBest = 0;
		if(perspective == 1)
			bestVal = numeric_limits<int>::min();
		else
			bestVal = numeric_limits<int>::max();
		vector<string> moves = moveList(perspective);
		// cerr<<"Size of the possible moves vector: "<<moves.size()<<endl;
		if (moves.size()>=1)
		{
			for(int i=0;i<moves.size();i++)
			{
				board->executeCommand(moves.at(i),perspective);
				if(perspective*bestVal < perspective*evalFunction()) {
					bestVal = evalFunction();
					bestMove = moves.at(i);
					indexBest = i;
				}
				// cerr<<"possible move: "<<moves.at(i)<<"with score: "<<evalFunction()<<" no of scored rings: "<<board->getRingsScored()<<endl;
				board->undoCommand(moves.at(i),perspective);
			}
			moves.at(indexBest) = moves.at(0);
			moves.at(0) = bestMove;

			if(perspective == 1)
				bestVal = numeric_limits<int>::min();
			else
				bestVal = numeric_limits<int>::max();
			if (moves.size()>=2)
			{
				indexBest = 1;
				for(int i=1;i<moves.size();i++)
				{
					board->executeCommand(moves.at(i),perspective);
					if(perspective*bestVal < perspective*evalFunction()) {
						bestVal = evalFunction();
						bestMove = moves.at(i);
						indexBest = i;
					}
					// cerr<<"possible move: "<<moves.at(i)<<"with score: "<<evalFunction()<<" no of scored rings: "<<board->getRingsScored()<<endl;
					board->undoCommand(moves.at(i),perspective);
				}
				moves.at(indexBest) = moves.at(1);
				moves.at(1) = bestMove;
				if(perspective == 1)
					bestVal = numeric_limits<int>::min();
				else
					bestVal = numeric_limits<int>::max();
				if (moves.size() >= 2)
				{	
					indexBest = 2;
					for(int i=2;i<moves.size();i++)
					{
						board->executeCommand(moves.at(i),perspective);
						if(perspective*bestVal < perspective*evalFunction()) {
							bestVal = evalFunction();
							bestMove = moves.at(i);
							indexBest = i;
						}
						// cerr<<"possible move: "<<moves.at(i)<<"with score: "<<evalFunction()<<" no of scored rings: "<<board->getRingsScored()<<endl;
						board->undoCommand(moves.at(i),perspective);
					}
					moves.at(indexBest) = moves.at(2);
					moves.at(2) = bestMove;
				}			
			}
		}
		for(int i = 0; i < moves.size(); i++) 
		{
			// cerr << "Trying move: " << moves.at(i) << endl;
			tempMove = moves.at(i);
			
			board->executeCommand(tempMove,perspective);
			tempScore = miniMax(depth - 1, -1*perspective, bestMoves, a, b);

			if(perspective == 1) 
			{
				b = min(tempScore,b);

				if(abs(tempScore - score) < 0.0001 || (tempScore - score) > 0.0001) {
					// cerr<<"*************************************8"<<endl;
					// cerr << "Max" << endl;

					score = tempScore;
					move_min = tempMove;
				}
			}
			else 
			{
				a = max(tempScore,a);
			
				if(abs(tempScore - score) < 0.0001 || (score - tempScore) > 0.0001) {
					// cerr<<"*************************************8"<<endl;
					// cerr << "Min" << endl;
					score = tempScore;
					move_max = tempMove;
				}
			}
			board->undoCommand(tempMove,perspective);
			if (a>=b)
			{
				bestMoves.push_back(tempMove);
				return tempScore;	
			}
		}
		if (perspective == 1)
		{
			bestMoves.push_back(move_min);
			move = move_min;
		}
		else
		{
			bestMoves.push_back(move_max);
			move = move_max;
		}
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
	double weight1 = 10;
	double weight2 = -9;
	double weight3 = 10;
	double weight4 = -9;
	double weight5 = 50000;
	double weight6 = -9000;
	double weight7 = 5;
	double weight8 = -4;
	double weight9 = 50;
	double weight10 = 1000;
	double weight11 = -900;
	double weight12 = 10;
	double weight13 = -9;
	double weight14 = 10;
	double weight15 = -9;

	double eval = 0;

	if(board->getNumRings() <= maxRings && board->getRingsScored() == 0 && board->getNumDiscs()==0) {
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
		
		vector< vector<int> > s1,e1;
		board->row_detected_modified(s1,e1,1,SequenceLength - 1);

		vector< vector<int> > s2,e2;
		board->row_detected_modified(s2,e2,-1,SequenceLength - 1);

		eval += (weight10 * s1.size() * s1.size()) + (weight11 * s2.size() * s2.size());

		for (int i=0; i<s1.size(); i++)
		{
			int controlled = board->row_marker_check(s1.at(i), e1.at(i),SequenceLength-1);
			eval += (weight12 * controlled * controlled);
		}

		for (int i=0; i<s2.size(); i++)
		{
			int oppControlled = SequenceLength - 1 - board->row_marker_check(s2.at(i), e2.at(i),SequenceLength-1);
			eval += (weight13 * oppControlled * oppControlled);
		}
		int s,c=0,c_opp=0;
		s = board->all_marker_check(c,c_opp);
		eval += weight14*c + weight15*c_opp;
		// eval = eval + (weight10 * discsOurControl()) + (weight11 * discsOppControl());
	}
	return eval;
}
