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
	init_depth = 1;
	boardSize = n;
	maxRings = m;
	SequenceLength = k;
	ringsToWin = l;
	turn = startTurn;

	board = new Board(n, m, k, l);

	w.push_back(500); // 1
	w.push_back(450); // 2
	w.push_back(100);//3
	w.push_back(90);//4
	w.push_back(1000000);//5
	w.push_back(1000000);//6
	w.push_back(5);//7
	w.push_back(4);//8
	w.push_back(100000);//9
	w.push_back(50000);//10
	w.push_back(50000);//11
	w.push_back(500);//12
	w.push_back(500);//13
	w.push_back(1000);//14
	w.push_back(1000);//15

	weightsSum = 0;
	for(int i=0;i<w.size();i++)
	{
		weightsSum += w.at(i);
	}
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
	init_depth = depth;
	vector<string> bestMoves;
	double score = miniMax(depth, turn, bestMoves, numeric_limits<int>::min(), numeric_limits<int>::max());
	// double score = miniMax1(depth, turn, bestMoves);
	// cerr<<"Size: " << bestMoves.size() << endl;
	// for(int i = 0; i < bestMoves.size(); i++) {
	// 	cerr<<bestMoves.at(i)<<endl;
	// }
	// cerr<<"bestMoves size: "<<bestMoves.size()<<endl;

	//imp
	// cerr<<"*********************************************************************************"<<endl;
	// cerr<<"final move selected: "<<bestMoves.at(bestMoves.size() - 1)<<" with score: "<<score<<endl;
		cerr<<"count of prune: "<<eff<<endl;
	
	return bestMoves.at(bestMoves.size() - 1);
}


double YinshBot::miniMax(int depth, int perspective, vector<string>& bestMoves, double a, double b) {
	
	// int a = std::numeric_limits<int>::max();
	// cerr<<"Depth: " << depth << " "<<endl;
	
	// cerr<<endl;
	if(depth <= 0 || checkGameEnd()) 
	{
		return evalFunction();
	}
	else 
	{
		vector<string> moves = moveList(perspective);
		int s = moves.size();
		int x = min(6,s);
		for(int j=0;j<x;j++)
		{
			string bestMove = " ";
			double bestVal;
			int indexBest = 0;

			if(perspective == 1)
				bestVal = numeric_limits<int>::min();
			else
				bestVal = numeric_limits<int>::max();
						
			for(int i=j;i<moves.size();i++)
			{

				board->executeCommand(moves.at(i),perspective);
				if (perspective == 1)
				{
					double t = evalFunction();
					if(bestVal - t < 0.0000001) 
					{
						bestVal = t;
						bestMove = moves.at(i);
						indexBest = i;
					}	
				}
				else
				{
					double t = evalFunction();
					if(bestVal - t > 0.0000001) 
					{
						bestVal = t;
						bestMove = moves.at(i);
						indexBest = i;
					}	
				}
				
				board->undoCommand(moves.at(i),perspective);
			}
			moves.at(indexBest) = moves.at(j);
			moves.at(j) = bestMove;
			cerr<<"ordering of move: "<<moves.at(j)<<" with score: "<<bestVal<<endl;
		}
			

		double score;
		if (perspective == 1)
		{
			score = numeric_limits<int>::min();
			// cerr<<"in max: depth: "<<depth<<endl;
		}
		else
		{
			score = numeric_limits<int>::max();
			// cerr<<"in min: depth: "<<depth<<endl;
		}

		double tempScore = 0;
		string tempMove = "";
		string move_min = "",move_max = "",move = "";
		// cerr<<"possible moves no. :"<<moves.size()<<endl;
		

		// if (moves.size() > 70)
		// 	depth--;


		for(int i = 0; i < moves.size(); i++) 
		{
			// cerr << "Trying move: " << moves.at(i);
			tempMove = moves.at(i);
			
			board->executeCommand(tempMove,perspective);
			tempScore = miniMax(depth - 1, -1*perspective, bestMoves, a, b);
			// cerr<<" with score: "<<score<<endl;
			if(perspective == 1) 
			{
				// cerr << "Trying move: " << moves.at(i);
				// cerr<<" with score: "<<score<<endl;
			
				a = max(a,tempScore);
				if(tempScore - score > 0.0000001) 
				{
					score = tempScore;
					move_max = tempMove;
				}
			}
			else 
			{
				b = min(b,tempScore);
				if(tempScore - score < 0.0000001) 
				{
					score = tempScore;
					move_min = tempMove;
				}
			}
			board->undoCommand(tempMove,perspective);

			if (a - b > 0.0000001 || abs(a-b) <= 0.0000001)
			{
				// cerr<<"###########################################prune"<<endl;
				eff++;
				break;
			}
		}

		if (perspective == 1)
		{
			bestMoves.push_back(move_max);
			move = move_max;
			// cerr<<"Selected move in maxValue: "<<move_max<<" with score: "<<score<<" rings scored: "<<board->getRingsScored()<<" depth: "<<depth<<endl;
		}
		else
		{
			bestMoves.push_back(move_min);
			move = move_min;
			// cerr<<"Selected move in minValue: "<<move_min<<" with score: "<<score<<" rings scored: "<<board->getRingsScored()<<" depth: "<<depth<<endl;

		}

		return score;
	}
}

vector<string> YinshBot::moveList(int perspective) 
{

	return board->generateMoveList(perspective);
}

bool YinshBot::checkGameEnd() 
{
	if (board->getRingsScored() == 3 || board->getOppRingsScored() == 3)
		return true;
	return false;
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




vector<double> YinshBot::getWeights () {
	return w;
}

vector<double> YinshBot::getFeatures (double &min, double &max) {
	vector<double> f;

	double eval1 = 0,eval2 = 0,eval3 = 0,eval4 = 0,eval5 = 0,eval6 = 0,eval7 = 0,eval8 = 0,eval9 = 0,eval10 = 0,eval11 = 0,eval12 = 0,eval13 = 0,eval14 = 0,eval15 = 0;
	if(board->getNumRings() <= maxRings && board->getRingsScored() == 0 && board->getNumDiscs()==0) 
	{
		int h, p = 1;
		for(int i = 0; i < board->getNumRings(); i++) {
			board->convertBack(getRingVLR(1, 1, i), getRingVLR(1, 2, i), getRingVLR(1, 3, i), h, p);
			eval7 = eval7 + (24/(h+1));
		}
		eval7 = (eval7-4.0)/20.0;
		
		for(int i = 0; i < board->getNumOppRings(); i++) {
			board->convertBack(getRingVLR(2, 1, i), getRingVLR(2, 2, i), getRingVLR(2, 3, i), h, p);
			eval8 = eval8 + (24/(h+1));
		}
		eval8 = (eval8-4.0)/20.0;

		eval9 = ringAttacks()/5.0;

		
	}
	else 
	{
		eval1 = board->getNumDiscs()/86.0;
		eval2 = (board->getNumOppDiscs())/86.0;
		eval3 = board->getNumRings()/5.0;
		eval4 = board->getNumOppRings()/5.0;
		eval5 = board->getRingsScored()/3.0;
		eval6 = board->getOppRingsScored()/3.0;
		
		vector< vector<int> > s1,e1;
		board->row_detected_modified(s1,e1,1,SequenceLength - 1);

		vector< vector<int> > s2,e2;
		board->row_detected_modified(s2,e2,-1,SequenceLength - 1);

		eval10 = s1.size()/6.0;
		eval11 = s2.size()/6.0;

		for (int i=0; i<s1.size(); i++)
		{
			int controlled = board->row_marker_check(s1.at(i), e1.at(i),SequenceLength-1);
			eval12 += controlled/4.0*s1.size();
		}

		for (int i=0; i<s2.size(); i++)
		{
			int oppControlled = SequenceLength - 1 - board->row_marker_check(s2.at(i), e2.at(i),SequenceLength-1);
			eval13 += oppControlled/4.0*s2.size();
		}

		// int s,c=0,c_opp=0;
		// s = board->all_marker_check(c,c_opp);
		// eval14 = c/86.0;
		// eval15 = c_opp/86.0;
	}
	f.push_back(eval1);
	f.push_back(eval2);
	f.push_back(eval3);
	f.push_back(eval4);
	f.push_back(eval5);
	f.push_back(eval6);
	f.push_back(eval7);
	f.push_back(eval8);
	f.push_back(eval9);
	f.push_back(eval10);
	f.push_back(eval11);
	f.push_back(eval12);
	f.push_back(eval13);
	f.push_back(eval14);
	f.push_back(eval15);

	return f;
}

double YinshBot::evalFunction () {

	double min = numeric_limits<int>::max(), max = numeric_limits<int>::min();
	vector<double> f = getFeatures(min,max);
	double eval = 0;
	// eval += -w.at(0)*(f.at(0) - min)/(max-min) + w.at(1)*(f.at(1) - min)/(max-min) + w.at(2)*(f.at(2) - min)/(max-min) 
	// 		-w.at(3)*(f.at(3) - min)/(max-min) + w.at(4)*(f.at(4) - min)/(max-min) - w.at(5)*(f.at(5) - min)/(max-min) + 
	// 		w.at(9)*(f.at(9) - min)/(max-min) - w.at(10)*(f.at(10) - min)/(max-min) + w.at(11)*(f.at(11) - min)/(max-min) - 
	// 		w.at(12)*(f.at(12) - min)/(max-min) + w.at(13)*(f.at(13) - min)/(max-min) - w.at(14)*(f.at(14) - min)/(max-min);
	// eval += w.at(6)*(f.at(6) - min)/(max-min) - w.at(7)*(f.at(7) - min)/(max-min) + w.at(8)*(f.at(8) - min)/(max-min);
	
	eval += -w.at(0)*f.at(0) + w.at(1)*f.at(1) + w.at(2)*f.at(2) - w.at(3)*f.at(3) + w.at(4)*f.at(4) - w.at(5)*f.at(5) + 
			w.at(9)*f.at(9) - w.at(10)*f.at(10) + w.at(11)*f.at(11) - w.at(12)*f.at(12) + w.at(13)*f.at(13) - w.at(14)*f.at(14);
	eval += w.at(6)*f.at(6) - w.at(7)*f.at(7) + w.at(8)*f.at(8);
	if (board->getRingsScored() == 3)
	{
		// cerr<<"*******************************winning state"<<endl;
		eval = weightsSum*4;
	}
	if (board->getOppRingsScored() == 3)
	{
		// cerr<<"*******************************winning state"<<endl;
		eval = weightsSum*4*(-1);
	}
		
	eval = sigmoid(eval/weightsSum);
	
	return eval;
}

double YinshBot::sigmoid(double eval)
{
	return 1/(1 + pow(2.71828,-1*eval));
}



// double YinshBot::evalFunction () {
// 	// double weight1 = 2;
// 	// double weight2 = -3;
// 	// double weight3 = 20;
// 	// double weight4 = -15;
// 	// double weight5 = 5000;
// 	// double weight6 = -3000;
// 	// double weight7 = 2;
// 	// double weight8 = -1;
// 	// double weight9 = 35;
// 	// double weight10 = 15;
// 	// double weight11 = -12;
// 	// double weight12 = 0;
// 	// double weight13 = 0;
// 	// double weight14 = 0;
// 	// double weight15 = 0;

// 	double weight1 = 500;
// 	double weight2 = -450;
// 	double weight3 = 100;
// 	double weight4 = -90;
// 	double weight5 = 1000000;
// 	//for us as player 2
// 	double weight6 = -1000000;
// 	//for us as player 1
// 	// double weight6 = -5000000;
// 	double weight7 = 5;
// 	double weight8 = -4;
// 	double weight9 = 50;
// 	double weight10 = 50000;
// 	double weight11 = -50000;
// 	double weight12 = 500;
// 	double weight13 = -500;
// 	double weight14 = 1000;
// 	double weight15 = -1000;

// 	double eval = 0;

// 	if(board->getNumRings() <= maxRings && board->getRingsScored() == 0 && board->getNumDiscs()==0) {
// 		int h, p = 1;
// 		for(int i = 0; i < board->getNumRings(); i++) {
// 			board->convertBack(getRingVLR(1, 1, i), getRingVLR(1, 2, i), getRingVLR(1, 3, i), h, p);
// 			eval = eval + (weight7 * (24/(h+1)));
// 		}
// 		for(int i = 0; i < board->getNumOppRings(); i++) {
// 			board->convertBack(getRingVLR(2, 1, i), getRingVLR(2, 2, i), getRingVLR(2, 3, i), h, p);
// 			eval = eval + (weight8 * (24/(h+1)));
// 		}
// 		eval = eval + (weight9 * ringAttacks());
// 	}
// 	else {
// 		eval = eval + (weight1 * board->getNumDiscs()) + (weight2 * board->getNumOppDiscs());
// 		eval = eval + (weight3 * board->getNumRings()) + (weight4 * board->getNumOppRings());
// 		eval = eval + (weight5 * board->getRingsScored()*board->getRingsScored()) + (weight6 * board->getOppRingsScored());
		
// 		if (board->getRingsScored() == 3)
// 			eval += numeric_limits<int>::max();
		
// 		vector< vector<int> > s1,e1;
// 		board->row_detected_modified(s1,e1,1,SequenceLength - 1);

// 		vector< vector<int> > s2,e2;
// 		board->row_detected_modified(s2,e2,-1,SequenceLength - 1);

// 		eval += (weight10 * s1.size() * s1.size()) + (weight11 * s2.size() * s2.size());

// 		for (int i=0; i<s1.size(); i++)
// 		{
// 			int controlled = board->row_marker_check(s1.at(i), e1.at(i),SequenceLength-1);
// 			eval += (weight12 * controlled * controlled);
// 		}

// 		for (int i=0; i<s2.size(); i++)
// 		{
// 			int oppControlled = SequenceLength - 1 - board->row_marker_check(s2.at(i), e2.at(i),SequenceLength-1);
// 			eval += (weight13 * oppControlled * oppControlled);
// 		}
// 		int s,c=0,c_opp=0;
// 		s = board->all_marker_check(c,c_opp);
// 		eval += weight14*c + weight15*c_opp;
// 		// eval = eval + (weight10 * discsOurControl()) + (weight11 * discsOppControl());
// 	}
// 	return eval;
// }
