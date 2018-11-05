//****************************

// Main functions left, parser for execute and undo Command, and eval function.

//****************************

//////////////////////////////

// Major things left alpha beta pruning(including ordering of moves) and depth differentiation based on move likability.

////////////////////////////


#include "YinshBot.h"

YinshBot::YinshBot () {

}

YinshBot::YinshBot (int n, int m, int k, int l, int startTurn,vector<double> wt) {
	boardSize = n;
	maxRings = m;
	SequenceLength = k;
	ringsToWin = l;
	turn = startTurn;
	board = new Board(n, m, k, l);
	w = wt;
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
			// if (checkGameEnd())
			// {
			// 	cerr<<"Game End with move: ";
			// 	cerr<<tempMove<<endl;
			// }
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
	if (board->getRingsScored() == 3 || board->getOppRingsScored() == 3)
		return true;
	else
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
		if (min > eval7) min = eval7;
		if (max < eval7) max = eval7;
		// cerr<<"eval7: "<<eval7<<endl;
		// eval += eval7*weight7;

		for(int i = 0; i < board->getNumOppRings(); i++) {
			board->convertBack(getRingVLR(2, 1, i), getRingVLR(2, 2, i), getRingVLR(2, 3, i), h, p);
			eval8 = eval8 + (24/(h+1));
		}
		eval8 = (eval8-4.0)/20.0;

		if (min > eval8) min = eval8;
		if (max < eval8) max = eval8;
		// cerr<<"eval8: "<<eval8<<endl;

		// eval += eval8*weight8;

		eval9 = ringAttacks()/5.0;
		if (min > eval9) min = eval9;
		if (max < eval9) max = eval9;
		// cerr<<"eval9: "<<eval9<<endl;
		// eval += eval9*weight9;

		
	}
	else 
	{
		eval1 = board->getNumDiscs()/86.0;
		if (min > eval1) min = eval1;
		if (max < eval1) max = eval1;
		eval2 = (board->getNumOppDiscs())/86.0;
		if (min > eval2) min = eval2;
		if (max < eval2) max = eval2;
		eval3 = board->getNumRings()/5.0;
		if (min > eval3) min = eval3;
		if (max < eval3) max = eval3;
		eval4 = board->getNumOppRings()/5.0;
		if (min > eval4) min = eval4;
		if (max < eval4) max = eval4;
		eval5 = board->getRingsScored()/3.0;
		if (min > eval5) min = eval5;
		if (max < eval5) max = eval5;
		eval6 = board->getOppRingsScored()/3.0;
		if (min > eval6) min = eval6;
		if (max < eval6) max = eval6;
		// eval = eval + (weight1 * eval1) + (weight2 * eval2);
		// eval = eval + (weight3 * eval3) + (weight4 * eval4);
		// eval = eval + (weight5 * eval5) + (weight6 * eval6);
		
		
		vector< vector<int> > s1,e1;
		board->row_detected_modified(s1,e1,1,SequenceLength - 1);

		vector< vector<int> > s2,e2;
		board->row_detected_modified(s2,e2,-1,SequenceLength - 1);

		eval10 = s1.size()/6.0;
		if (min > eval10) min = eval10;
		if (max < eval10) max = eval10;
		eval11 = s2.size()/6.0;
		if (min > eval11) min = eval11;
		if (max < eval11) max = eval11;
		// eval += (weight10 * eval10) + (weight11 * eval11);

		for (int i=0; i<s1.size(); i++)
		{
			int controlled = board->row_marker_check(s1.at(i), e1.at(i),SequenceLength-1);
			eval12 += controlled/4.0*s1.size();
		}
		if (min > eval12) min = eval12;
		if (max < eval12) max = eval12;
		// eval += weight12*eval12;

		for (int i=0; i<s2.size(); i++)
		{
			int oppControlled = SequenceLength - 1 - board->row_marker_check(s2.at(i), e2.at(i),SequenceLength-1);
			eval13 += oppControlled/4.0*s2.size();
		}
		if (min > eval13) min = eval13;
		if (max < eval13) max = eval13;
		// eval += weight13*eval13;

		int s,c=0,c_opp=0;
		s = board->all_marker_check(c,c_opp);
		if (min > eval14) min = eval14;
		if (max < eval14) max = eval14;
		eval14 = c/86.0;
		if (min > eval15) min = eval15;
		if (max < eval15) max = eval15;
		eval15 = c_opp/86.0;
		// eval += weight14*eval14 + weight15*eval15;
		// eval = eval + (weight10 * discsOurControl()) + (weight11 * discsOppControl());
		// cerr<<"normalized: "<<(eval1 - min)/(max-min)<<endl;
		
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
	// cerr<<"eval1: "<<eval1<<endl;
	// double e = eval1/86;
	// cerr<<"eval1: "<<e<<endl;

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
	
	// cerr<<"contri from f1: "<<f.at(0)<<endl;
	// cerr<<"contri from f2: "<<f.at(1)<<endl;
	// cerr<<"contri from f3: "<<f.at(2)<<endl;
	// cerr<<"contri from f4: "<<f.at(3)<<endl;
	// cerr<<"contri from f5: "<<f.at(4)<<endl;
	// cerr<<"contri from f6: "<<f.at(5)<<endl;
	// cerr<<"contri from f7: "<<f.at(6)<<endl;
	// cerr<<"contri from f8: "<<f.at(7)<<endl;
	// cerr<<"contri from f9: "<<f.at(8)<<endl;
	// cerr<<"contri from f10: "<<f.at(9)<<endl;
	// cerr<<"contri from f11: "<<f.at(10)<<endl;
	// cerr<<"contri from f12: "<<f.at(11)<<endl;
	// cerr<<"contri from f13: "<<f.at(12)<<endl;
	// cerr<<"contri from f14: "<<f.at(13)<<endl;
	// cerr<<"contri from f15: "<<f.at(14)<<endl<<endl;
	
	eval += -w.at(0)*f.at(0) + w.at(1)*f.at(1) + w.at(2)*f.at(2) - w.at(3)*f.at(3) + w.at(4)*f.at(4) - w.at(5)*f.at(5) + 
			w.at(9)*f.at(9) - w.at(10)*f.at(10) + w.at(11)*f.at(11) - w.at(12)*f.at(12) + w.at(13)*f.at(13) - w.at(14)*f.at(14);
	eval += w.at(6)*f.at(6) - w.at(7)*f.at(7) + w.at(8)*f.at(8);
	if (board->getRingsScored() == 3)
		eval = weightsSum*4;
		
	// cerr<<"eval before sigmoid: "<<eval/weightsSum<<endl;
	eval = sigmoid(eval/weightsSum);
	// cerr<<"eval after sigmoid: "<<eval<<endl;

	return eval;
}

double YinshBot::sigmoid(double eval)
{
	return 1/(1 + pow(2.71828,-1*eval));
}

vector<double> YinshBot::Derivative(vector<double> features) {
	double f = evalFunction();
	// cout<<f<<endl;
	vector<double> v;	
	for(int i=0;i<features.size();i++)
	{
		v.push_back(f*(1-f)*features.at(i));
	}
	return v;
}

vector<double> YinshBot::selfPlay(int p,vector<double> wt,double epsilon)
{
	srand((int)time(0));

	vector<double> e;
	double delta = 1, gamma = 0.9, alpha = 0.1, lambda = 0;
	double min = numeric_limits<int>::max(), max = numeric_limits<int>::min();
	vector<double> f = getFeatures(min,max);

	// cout<<"initial features"<<endl;
	// for(int i=0;i<f.size();i++)
	// {
	// 	cout<<f.at(i)<<endl;
	// }
	// cout<<endl;
	
	e = Derivative(f);
	
	// cout<<"initial derivative"<<endl;
	// for(int i=0;i<e.size();i++)
	// {
	// 	cout<<e.at(i)<<endl;
	// }
	// cout<<endl;

	int count = 1;
	for(int t=0;!checkGameEnd();t++)
	{
		double V_old = evalFunction();

		double q = ((double) rand()/RAND_MAX);
		vector<string> moves = moveList(p);
		if (q < epsilon)
		{
			int r = ((double) rand()/RAND_MAX)*(moves.size()-1);
			// cout<<"random move: "<<moves.at(r)<<endl;
			board->executeCommand(moves.at(r),p);
				
		}
		else
		{
			board->executeCommand(moves.at(0),p);
			double maximum = p*evalFunction();
			int best=0;
			board->undoCommand(moves.at(0),p);

			for(int i=1;i<moves.size();i++)
			{
				board->executeCommand(moves.at(i),p);
				double score = evalFunction();
				if (p*score > maximum)
				{
					maximum = p*score;
					best = i;
				}
				board->undoCommand(moves.at(i),p);
			}
			// cout<<"best move: "<<moves.at(best)<<endl;
			board->executeCommand(moves.at(best),p);

		}
		
		double V_new;
		if (checkGameEnd())
		{
			V_new = 1;
		}	
		else
		{
			V_new = evalFunction();
		}

		// if (!checkGameEnd() && q < epsilon)
		// 	delta = 0;
		// else
			// delta = gamma*V_new - V_old;
		
		if (count <= 10)
		{

			for(int i=6;i<=8;i++)
				wt.at(i) = wt.at(i) + alpha*delta*e.at(i);

		}
		else
		{

			for(int i=0;i<=5;i++)
				wt.at(i) = wt.at(i) + alpha*delta*e.at(i);

			for(int i=9;i<wt.size();i++)
				wt.at(i) = wt.at(i) + alpha*delta*e.at(i);

		}

		w = wt;
		// cout<<"new weights: "<<endl;
		// for(int i=0;i<w.size();i++)
		// {
		// 	cout<<setw(7)<<w.at(i);
		// }

		double min = numeric_limits<int>::max(), max = numeric_limits<int>::min();
		vector<double> der = Derivative(getFeatures(min,max));

		if (count <= 10)
		{
			for(int i=6;i<=8;i++)
				e.at(i) = gamma*lambda*e.at(i) + der.at(i);
		}
		else
		{

			for(int i=0;i<=5;i++)
				e.at(i) = gamma*lambda*e.at(i) + der.at(i);
				
			for(int i=9;i<e.size();i++)
				e.at(i) = gamma*lambda*e.at(i) + der.at(i);
				
		}
		

		p = -p;
		count++;
	}

	
	
	return wt;

}