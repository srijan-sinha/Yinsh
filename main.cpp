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
	cout<<"^^"<<endl;

	b->addRing(1,0,0);
	cout<<endl;
	b->print_board();

	b->moveRing(0,0,3,0);
	cout<<endl;
	b->print_board();

	b->moveRing(3,0,1,3);
	cout<<endl;
	b->print_board();


	vector<string> m;
	m = b->addRingMoves(m);
	for(int i=0;i<m.size();i++)
	{
		cout<<m.at(i)<<endl;
	}
	cout<<m.size()<<endl;

	// b->print_ring_vectors();

	vector<string> n;
	n = b->moveRingMoves(n,1,b->ringV,b->ringL,b->ringR);
	for(int i=0;i<n.size();i++)
	{
		cout<<n.at(i)<<endl;
	}
	cout<<n.size()<<endl;

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