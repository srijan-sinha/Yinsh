#include <bits/stdc++.h>

#include "YinshBot.h"
// #include "Board.h"

using namespace std;

int main ()
{

	int turn = 1;
	vector<double> w;
	w.push_back(500); //1
	w.push_back(450); //2
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
	YinshBot *y;
	double epsilon = 0.9;
	for(int i=0;i<5000;i++)
	{
		y = new YinshBot(5,5,5,3,turn,w);
		string s = "P 0 0";
		y->executeCommand(s, turn);
		// cout << s << endl;
		cout<<epsilon<<endl;
		w = y->selfPlay(-1,y->w,epsilon);
		for(int i=0;i<w.size();i++)
			cout<<setw(9)<<w.at(i);
		cout<<endl;
		// if (epsilon > 0.1)
		// {
		// 	epsilon = 0.99*epsilon;
		// }
	}
	

	//******************************************************************************************* 	
	//main main program

	// int player_id, board_size, time_limit;
 //    // cerr<<player_id << board_size << time_limit;
	// cin >> player_id >> board_size >> time_limit;
	// cin.ignore();
	// if (player_id == 1)
	// {
	// 	int turn = 1;
	// 	YinshBot *y = new YinshBot(5,5,5,3,turn,w);
		
	// 	string s = "P 0 0";
	// 	y->executeCommand(s, turn);
	// 	cout << s << endl;
	// 	// y->print_board();
	// 	y->changeTurn();
	// 	turn = -1 * turn;
	// 	int count = 0;		
	// 	while(true)
	// 	{
	// 		// cout << "Opponent's Command: ";
	// 		string in_command;
	// 		// cerr<<"give input command: "<<endl;
	// 		getline(cin, in_command);
	// 		// cerr<<"input command: "<<in_command<<endl;
	// 		y->executeCommand(in_command, turn);
	// 		y->print_board();
	// 		turn = -1 * turn;
	// 		// cerr<<"opp turn done"<<endl;
	// 		// for(int i=0;i<y->board->ringV_opp.size();i++)
	// 		// {
	// 		// 	cerr<<y->board->ringV_opp.at(i)<<y->board->ringL_opp.at(i)<<y->board->ringR_opp.at(i)<<" ";
	// 		// }
	// 		// cerr<<endl;
	// 		y->changeTurn();
	// 		string out_command;
	// 		if (count<5)
	// 			out_command = y->findNextMove(1);
	// 		else if(count > 15 && count < 40)
	// 			out_command = y->findNextMove(3);
	// 		else
	// 			out_command = y->findNextMove(3);
	// 		cout<<out_command<<endl;
	// 		y->executeCommand(out_command, turn);
	// 		cerr << endl;
	// 		// cout << "Our Move: " << out_command << endl;
	// 		// y->print_board();
	// 		// cerr<<"turn done"<<endl;
	// 		y->changeTurn();
	// 		// for(int i=0;i<y->board->ringV.size();i++)
	// 		// {
	// 		// 	cerr<<y->board->ringV.at(i)<<y->board->ringL.at(i)<<y->board->ringR.at(i)<<" ";
	// 		// }
	// 		turn = -1 * turn;
	// 		count++;
			
	// 	}

	// }
	// else
	// {
	// 	int count = 0;
	// 	int turn = -1;
	// 	YinshBot *y = new YinshBot(5,5,5,3,turn,w);
	// 	while(true)
	// 	{
	// 		string in_command;
	// 		// cerr<<"give input command: "<<endl;
	// 		getline(cin, in_command);
	// 		y->executeCommand(in_command, turn);
	// 		// y->print_board();
	// 		turn = -1 * turn;
	// 		// cerr<<"opp turn done"<<endl;
	// 		y->changeTurn();
	// 		string out_command;
	// 		if (count<5)
	// 			out_command = y->findNextMove(1);
	// 		else if(count > 15 && count < 40)
	// 			out_command = y->findNextMove(3);
	// 		else 
	// 			out_command = y->findNextMove(3);
	// 		cout<<out_command<<endl;

	// 		y->executeCommand(out_command, turn);
	// 		// cerr<<"selected move: "<<out_command<<" with score: "<<y->evalFunction()<<endl;
	// 		// y->print_board();
	// 		// cerr<<"turn done"<<endl;
	// 		y->changeTurn();
	// 		turn = -1 * turn;
	// 		count++;
			
	// 	}

	// }

	    return 0;
}
