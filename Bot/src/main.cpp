#include <bits/stdc++.h>

#include "YinshBot.h"
// #include "Board.h"

using namespace std;

int main ()
{

	//main main program

	int player_id, board_size, time_limit, s;
    // cerr<<player_id << board_size << time_limit;
	cin >> player_id >> board_size >> time_limit >> s;
	cin.ignore();
	if (player_id == 1)
	{
		int turn = 1;
		YinshBot *y = new YinshBot(board_size,board_size,s,3,turn);
		
		string s = "P 0 0";
		y->executeCommand(s, turn);
		cout << s << endl;
		y->print_board();
		y->changeTurn();
		turn = -1 * turn;
		int count = 0;		
		while(true)
		{
			// cout << "Opponent's Command: ";
			string in_command;
			// cerr<<"give input command: "<<endl;
			getline(cin, in_command);
			// cerr<<"input command: "<<in_command<<endl;
			y->executeCommand(in_command, turn);
			y->print_board();
			turn = -1 * turn;
			// cerr<<"opp turn done"<<endl;
			// for(int i=0;i<y->board->ringV_opp.size();i++)
			// {
			// 	cerr<<y->board->ringV_opp.at(i)<<y->board->ringL_opp.at(i)<<y->board->ringR_opp.at(i)<<" ";
			// }
			// cerr<<endl;
			y->changeTurn();
			string out_command;
			if (count<board_size)
				out_command = y->findNextMove(1);
			else if(count > 15 && count < 40)
				out_command = y->findNextMove(3);
			else
				out_command = y->findNextMove(3);
			cout<<out_command<<endl;
			y->executeCommand(out_command, turn);
			cerr << endl;
			// cout << "Our Move: " << out_command << endl;
			y->print_board();
			// cerr<<"turn done"<<endl;
			y->changeTurn();
			// for(int i=0;i<y->board->ringV.size();i++)
			// {
			// 	cerr<<y->board->ringV.at(i)<<y->board->ringL.at(i)<<y->board->ringR.at(i)<<" ";
			// }
			turn = -1 * turn;
			count++;
			
		}
		cerr<<"count of prune: "<<y->eff<<endl;
		
	}
	else
	{
		int count = 0;
		int turn = -1;
		YinshBot *y = new YinshBot(board_size,board_size,s,3,turn);
		while(true)
		{
			string in_command;
			// cerr<<"give input command: "<<endl;
			getline(cin, in_command);
			y->executeCommand(in_command, turn);
			y->print_board();
			turn = -1 * turn;
			// cerr<<"opp turn done"<<endl;
			y->changeTurn();
			string out_command;
			if (count<board_size)
				out_command = y->findNextMove(1);
			else if(count > 15 && count < 40)
				out_command = y->findNextMove(3);
			else 
				out_command = y->findNextMove(3);
			cout<<out_command<<endl;

			y->executeCommand(out_command, turn);
			// cerr<<"selected move: "<<out_command<<" with score: "<<y->evalFunction()<<endl;
			y->print_board();
			// cerr<<"turn done"<<endl;
			y->changeTurn();
			turn = -1 * turn;
			count++;
			
		}
		cerr<<"count of prune: "<<y->eff<<endl;
	}

	    return 0;
}
	
	// Board *b  = new Board(5,5,5,5);
	// 	b->initBoard(5);
	// 	b->print_board();
		
	// 	b->addDisc(-1,2,1);
	// 	cerr<<endl;
	// 	b->print_board();

	// 	b->addDisc(-1,2,2);
	// 	cerr<<endl;
	// 	b->print_board();


	// 	b->addDisc(1,4,6);
	// 	cerr<<endl;
	// 	b->print_board();

	// 	b->addDisc(1,5,8);
	// 	cerr<<endl;
	// 	b->print_board();


	// 	b->addRing(1,3,4);
	// 	cerr<<endl;
	// 	b->print_board();

	// 	b->moveRing(3,4,2,0);
	// 	cerr<<endl;
	// 	b->print_board();
	    
	// 	vector< vector<int> > s,e;
	// 	b->row_detected_modified(s,e,1,5);
	// 	cout<<s.size()<<endl;
	// 	for(int i=0;i<s.size();i++)
	// 	{
	// 		for(int j=0;j<3;j++)
	// 		cout<<s.at(i).at(j);
	// 	}
	// 	cout<<" ";
	// 	for(int i=0;i<e.size();i++)
	// 	{
	// 		for(int j=0;j<3;j++)
	// 		cout<<e.at(i).at(j);
	// 	}


    // Parse the input.
    // if ( argc < 3 )
    // {   
    //     cerr<<"Missing arguments\n";
    //     cerr<<"Correct format : \n";
    //     cerr << "./main <input_filename> <output_filename>";
    //     exit ( 0 );
    // }
// 	Board *b  = new Board(5,5,5,5);
// 	b->initBoard(5);
// 	b->print_board();
	
// 	b->addDisc(1,2,5);
// 	cerr<<endl;
// 	b->print_board();

// 	b->addDisc(1,2,4);
// 	cerr<<endl;
// 	b->print_board();
	
// 	b->addDisc(1,3,5);
// 	cerr<<endl;
// 	b->print_board();

// 	b->addDisc(1,4,6);
// 	cerr<<endl;
// 	b->print_board();

// 	b->addDisc(1,4,8);
// 	cerr<<endl;
// 	b->print_board();

// 	b->addDisc(1,4,9);
// 	cerr<<endl;
// 	b->print_board();

// 	b->addDisc(1,4,10);
// 	cerr<<endl;
// 	b->print_board();

// 	b->addDisc(1,4,11);
// 	cerr<<endl;
// 	b->print_board();

// 	b->addDisc(1,5,9);
// 	cerr<<endl;
// 	b->print_board();


// 	b->addDisc(-1,2,6);
// 	cerr<<endl;
// 	b->print_board();

// 	b->addRing(1,4,12);
// 	cerr<<endl;
// 	b->print_board();

// 	b->addRing(1,5,17);
// 	cerr<<endl;
// 	b->print_board();
	
// 	b->addRing(1,5,18);
// 	cerr<<endl;
// 	b->print_board();


// 	b->addRing(1,4,14);
// 	cerr<<endl;
// 	b->print_board();

// 	b->addRing(1,4,17);
// 	cerr<<endl;
// 	b->print_board();

// // cerr<<"moves done"<<endl;

// 	// b->moveRing(4,12,1,3);
// 	// cerr<<endl;
// 	// b->print_board();

// 	// vector<string> v = b->moveRingMoves (v, 1, b->ringV, b->ringL, b->ringR) ;
// 	// for(int i=0;i<v.size();i++)
// 	// {
// 	// 	cerr<<v.at(i)<<endl;
// 	// }
// 	// cerr<<v.size()<<endl;
	
// 	vector<string> o;
// 	// o.push_back("");
// 	o = b->generateMoveList(1);
// 	// o = b->fullMove("",1);
// 	for(int i=0;i<o.size();i++)
// 	{
// 		cerr<<o.at(i)<<endl;
// 	}
// 	cerr<<o.size()<<endl;
// 	cerr<<"end"<<endl;
