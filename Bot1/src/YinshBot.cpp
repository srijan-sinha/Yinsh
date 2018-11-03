//****************************

// Main functions left, parser for execute and undo Command, and eval function.

//****************************

//////////////////////////////

// Major things left alpha beta pruning(including ordering of moves) and depth differentiation based on move likability.

////////////////////////////


#include "YinshBot.h"

YinshBot::YinshBot () {

}

YinshBot::YinshBot (int n, int m, int k, int l, int startTurn, int w1, int w2, int w3, int w4, int w5, int w6, int w7, int w8, int w9, int w10, int w11, int w12, int w13, int w14, int w15) {
	weight1 = w1;
	weight2 = w2;
	weight3 = w3;
	weight4 = w4;
	weight5 = w5;
	weight6 = w6;
	weight7 = w7;
	weight8 = w8;
	weight9 = w9;
	weight10 = w10;
	weight11 = w11;
	weight12 = w12;
	weight13 = w13;
	weight14 = w14;
	weight15 = w15;
	
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
	// cerr<<"Depth: " << depth << " "<<endl;
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
		double bestVal,bestVal1,val;
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
			bestVal1 = bestVal;
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
				if (moves.size() > 2)
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

					if (moves.size() > 3)
					{
						board->executeCommand(moves.at(3),perspective);
						val = evalFunction();
						board->undoCommand(moves.at(3),perspective);
													
						// cerr<<"factor: "<<bestVal1-val;
						int factor = 50000;
						// cerr << perspective * (bestVal1 - val) << " " << perspective * factor << endl;
						if (perspective*(bestVal1-val) > perspective*factor)
						{
							bestMoves.push_back(moves.at(0));
							return bestVal1;
						}
					}
				
				}

			}
		}
		// cerr << "***************************************" << endl;
		for(int i = 0; i < moves.size(); i++) 
		{
			// cerr << "Trying move: " << moves.at(i) << endl;
			tempMove = moves.at(i);
			
			board->executeCommand(tempMove,perspective);
			tempScore = miniMax(depth - 1, -1*perspective, bestMoves, a, b);

			if(perspective == 1) 
			{
				// b = min(tempScore,b);

				if(abs(tempScore - score) < 0.0001 || (tempScore - score) > 0.0001) {
					// cerr<<"*************************************8"<<endl;
					// cerr << "Max" << endl;

					score = tempScore;
					move_min = tempMove;
				}
			}
			else 
			{
				// a = max(tempScore,a);
			
				if(abs(tempScore - score) < 0.0001 || (score - tempScore) > 0.0001) {
					// cerr<<"*************************************8"<<endl;
					// cerr << "Min" << endl;
					score = tempScore;
					move_max = tempMove;
				}
			}
			board->undoCommand(tempMove,perspective);
			// if (a>=b)
			// {
			// 	bestMoves.push_back(tempMove);
			// 	return tempScore;	
			// }
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
		// cerr<<endl<<"selected move: "<<move<<"with score: "<<score<<" no of scored rings: "<<board->getRingsScored()<<endl;

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
	// double weight1 = 2;
	// double weight2 = -3;
	// double weight3 = 20;
	// double weight4 = -15;
	// double weight5 = 5000;
	// double weight6 = -3000;
	// double weight7 = 2;
	// double weight8 = -1;
	// double weight9 = 35;
	// double weight10 = 15;
	// double weight11 = -12;
	// double weight12 = 0;
	// double weight13 = 0;
	// double weight14 = 0;
	// double weight15 = 0;

	// double weight1 = 500;
	// double weight2 = 450;
	// double weight3 = 100;
	// double weight4 = 90;
	// double weight5 = 1000000;
	// double weight6 = -1000000;
	// double weight7 = 5;
	// double weight8 = 4;
	// double weight9 = 50;
	// double weight10 = 50000;
	// double weight11 = 50000;
	// double weight12 = 500;
	// double weight13 = 500;
	// double weight14 = 1000;
	// double weight15 = 1000;

	double eval = 0;
	double eval1 = 0,eval2 = 0,eval3 = 0,eval4 = 0,eval5 = 0,eval6 = 0,eval7 = 0,eval8 = 0,eval9 = 0,eval10 = 0,eval11 = 0,eval12 = 0,eval13 = 0,eval14 = 0,eval15 = 0;
	double min = numeric_limits<int>::max(), max = numeric_limits<int>::min();
	if(board->getNumRings() <= maxRings && board->getRingsScored() == 0 && board->getNumDiscs()==0) 
	{
		int h, p = 1;
		for(int i = 0; i < board->getNumRings(); i++) {
			board->convertBack(getRingVLR(1, 1, i), getRingVLR(1, 2, i), getRingVLR(1, 3, i), h, p);
			eval7 = eval7 + (24/(h+1));
		}
		if (min > eval7) min = eval7;
		if (max < eval7) max = eval7;
		// eval += eval7*weight7;

		for(int i = 0; i < board->getNumOppRings(); i++) {
			board->convertBack(getRingVLR(2, 1, i), getRingVLR(2, 2, i), getRingVLR(2, 3, i), h, p);
			eval8 = eval8 + (24/(h+1));
		}
		if (min > eval8) min = eval8;
		if (max < eval8) max = eval8;
		// eval += eval8*weight8;

		eval9 = ringAttacks();
		if (min > eval9) min = eval9;
		if (max < eval9) max = eval9;
		eval += eval9*weight9;

		eval += weight7*(eval7 - min)/(max-min) - weight8*(eval8 - min)/(max-min) + weight9*(eval9 - min)/(max-min);
	}
	else 
	{
		eval1 = board->getNumDiscs();
		if (min > eval1) min = eval1;
		if (max < eval1) max = eval1;
		eval2 = board->getNumOppDiscs();
		if (min > eval2) min = eval2;
		if (max < eval2) max = eval2;
		eval3 = board->getNumRings();
		if (min > eval3) min = eval3;
		if (max < eval3) max = eval3;
		eval4 = board->getNumOppRings();
		if (min > eval4) min = eval4;
		if (max < eval4) max = eval4;
		eval5 = board->getRingsScored()*board->getRingsScored();
		if (min > eval5) min = eval5;
		if (max < eval5) max = eval5;
		eval6 = board->getOppRingsScored();
		if (min > eval6) min = eval6;
		if (max < eval6) max = eval6;
		// eval = eval + (weight1 * eval1) + (weight2 * eval2);
		// eval = eval + (weight3 * eval3) + (weight4 * eval4);
		// eval = eval + (weight5 * eval5) + (weight6 * eval6);
		
		if (board->getRingsScored() == 3)
			eval += numeric_limits<int>::max();
		
		vector< vector<int> > s1,e1;
		board->row_detected_modified(s1,e1,1,SequenceLength - 1);

		vector< vector<int> > s2,e2;
		board->row_detected_modified(s2,e2,-1,SequenceLength - 1);

		eval10 = s1.size() * s1.size();
		if (min > eval10) min = eval10;
		if (max < eval10) max = eval10;
		eval11 = s2.size() * s2.size();
		if (min > eval11) min = eval11;
		if (max < eval11) max = eval11;
		// eval += (weight10 * eval10) + (weight11 * eval11);

		for (int i=0; i<s1.size(); i++)
		{
			int controlled = board->row_marker_check(s1.at(i), e1.at(i),SequenceLength-1);
			eval12 += controlled * controlled;
		}
		if (min > eval12) min = eval12;
		if (max < eval12) max = eval12;
		// eval += weight12*eval12;

		for (int i=0; i<s2.size(); i++)
		{
			int oppControlled = SequenceLength - 1 - board->row_marker_check(s2.at(i), e2.at(i),SequenceLength-1);
			eval13 += oppControlled * oppControlled;
		}
		if (min > eval13) min = eval13;
		if (max < eval13) max = eval13;
		// eval += weight13*eval13;

		int s,c=0,c_opp=0;
		s = board->all_marker_check(c,c_opp);
		if (min > eval14) min = eval14;
		if (max < eval14) max = eval14;
		eval14 = c;
		if (min > eval15) min = eval15;
		if (max < eval15) max = eval15;
		eval15 = c_opp;
		// eval += weight14*eval14 + weight15*eval15;
		// eval = eval + (weight10 * discsOurControl()) + (weight11 * discsOppControl());
		// cerr<<"normalized: "<<(eval1 - min)/(max-min)<<endl;
		eval += -weight1*(eval1 - min)/(max-min) + weight2*(eval2 - min)/(max-min) + weight3*(eval3 - min)/(max-min) 
			-weight4*(eval4 - min)/(max-min) + weight5*(eval5 - min)/(max-min) - weight6*(eval6 - min)/(max-min) + 
			weight10*(eval10 - min)/(max-min) - weight11*(eval11 - min)/(max-min) + weight12*(eval12 - min)/(max-min) - 
			weight13*(eval13 - min)/(max-min) + weight14*(eval14 - min)/(max-min) - weight15*(eval15 - min)/(max-min);
	}
	return eval;
}
