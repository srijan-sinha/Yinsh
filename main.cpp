#include <bits/stdc++.h>

#include "YinshBot.h"

using namespace std;

int main ()
{

	int turn = -1;
	YinshBot *y = new YinshBot(5,5,5,3,turn);
	while(true)
	{
		string in_command;
		getline(cin, in_command);
		
		y->executeCommand(in_command, turn);
		turn = -1 * turn;
		y->print_board();
		cout<<"opp turn done"<<endl;
		for(int i=0;i<y->board->ringV_opp.size();i++)
		{
			cout<<y->board->ringV_opp.at(i)<<y->board->ringL_opp.at(i)<<y->board->ringR_opp.at(i)<<" ";
		}
		cout<<endl;
		y->changeTurn();
		string out_command = y->findNextMove(1);
		cout<<"output command: "<<out_command<<endl;
		y->executeCommand(out_command, turn);
		y->print_board();
		cout<<"turn done"<<endl;
		y->changeTurn();
		for(int i=0;i<y->board->ringV.size();i++)
		{
			cout<<y->board->ringV.at(i)<<y->board->ringL.at(i)<<y->board->ringR.at(i)<<" ";
		}
		turn = -1 * turn;
		
		
	}




    // Parse the input.
    // if ( argc < 3 )
    // {   
    //     cout<<"Missing arguments\n";
    //     cout<<"Correct format : \n";
    //     cout << "./main <input_filename> <output_filename>";
    //     exit ( 0 );
    // }
// 	Board *b  = new Board(5,5,5,5);
// 	b->initBoard(5);
// 	b->print_board();
	
// 	b->addDisc(1,2,5);
// 	cout<<endl;
// 	b->print_board();

// 	b->addDisc(1,2,4);
// 	cout<<endl;
// 	b->print_board();
	
// 	b->addDisc(1,3,5);
// 	cout<<endl;
// 	b->print_board();

// 	b->addDisc(1,4,6);
// 	cout<<endl;
// 	b->print_board();

// 	b->addDisc(1,4,8);
// 	cout<<endl;
// 	b->print_board();

// 	b->addDisc(1,4,9);
// 	cout<<endl;
// 	b->print_board();

// 	b->addDisc(1,4,10);
// 	cout<<endl;
// 	b->print_board();

// 	b->addDisc(1,4,11);
// 	cout<<endl;
// 	b->print_board();

// 	b->addDisc(1,5,9);
// 	cout<<endl;
// 	b->print_board();


// 	b->addDisc(-1,2,6);
// 	cout<<endl;
// 	b->print_board();

// 	b->addRing(1,4,12);
// 	cout<<endl;
// 	b->print_board();

// 	b->addRing(1,5,17);
// 	cout<<endl;
// 	b->print_board();
	
// 	b->addRing(1,5,18);
// 	cout<<endl;
// 	b->print_board();


// 	b->addRing(1,4,14);
// 	cout<<endl;
// 	b->print_board();

// 	b->addRing(1,4,17);
// 	cout<<endl;
// 	b->print_board();

// // cout<<"moves done"<<endl;

// 	// b->moveRing(4,12,1,3);
// 	// cout<<endl;
// 	// b->print_board();

// 	// vector<string> v = b->moveRingMoves (v, 1, b->ringV, b->ringL, b->ringR) ;
// 	// for(int i=0;i<v.size();i++)
// 	// {
// 	// 	cout<<v.at(i)<<endl;
// 	// }
// 	// cout<<v.size()<<endl;
	
// 	vector<string> o;
// 	// o.push_back("");
// 	o = b->generateMoveList(1);
// 	// o = b->fullMove("",1);
// 	for(int i=0;i<o.size();i++)
// 	{
// 		cout<<o.at(i)<<endl;
// 	}
// 	cout<<o.size()<<endl;
// 	cout<<"end"<<endl;
    return 0;
}