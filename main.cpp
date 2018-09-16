#include <bits/stdc++.h>

#include "Board.h"

using namespace std;

int main ()
{
    // Parse the input.
    // if ( argc < 3 )
    // {   
    //     cout<<"Missing arguments\n";
    //     cout<<"Correct format : \n";
    //     cout << "./main <input_filename> <output_filename>";
    //     exit ( 0 );
    // }
	Board *b  = new Board(5,5,5,5);
	b->initBoard(5);
	b->print_board();
	
	b->addDisc(1,2,5);
	cout<<endl;
	b->print_board();

	b->addDisc(1,2,4);
	cout<<endl;
	b->print_board();
	
	b->addDisc(1,3,5);
	cout<<endl;
	b->print_board();

	b->addDisc(1,4,6);
	cout<<endl;
	b->print_board();

	b->addDisc(1,4,8);
	cout<<endl;
	b->print_board();

	b->addDisc(1,4,9);
	cout<<endl;
	b->print_board();

	b->addDisc(1,4,10);
	cout<<endl;
	b->print_board();

	b->addDisc(1,4,11);
	cout<<endl;
	b->print_board();

	b->addDisc(1,5,9);
	cout<<endl;
	b->print_board();


	b->addDisc(-1,2,6);
	cout<<endl;
	b->print_board();

	b->addRing(1,4,12);
	cout<<endl;
	b->print_board();

	b->addRing(1,4,14);
	cout<<endl;
	b->print_board();

	b->addRing(1,4,17);
	cout<<endl;
	b->print_board();

	// b->moveRing(4,12,1,3);
	// cout<<endl;
	// b->print_board();


	vector<string> o;
	o = b->fullMove("",1);
	for(int i=0;i<o.size();i++)
	{
		cout<<o.at(i)<<endl;
	}
	cout<<o.size()<<endl;
	cout<<"end"<<endl;
    return 0;
}