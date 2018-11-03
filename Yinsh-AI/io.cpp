#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <bits/stdc++.h>
#include <vector>

using namespace std;

int main(int argc, char* argv[])
{
	int a,b;
	a = stoi(argv[1]);
	b = stoi(argv[2]);

	// ifstream file ("out.txt");
	// if (file.is_open())
	// {
	// 	int x,y;
	// 	file >> x >> y;
	// 	if (a == 1)
	// 		b = x;
	// 	else
	// 		b = y;
	// }
	// else 
	// 	cerr << "Unable to open file"; 
	
	
	srand((int)time(0));
	vector<double> w;

	ifstream nfile ("first_gen.txt");
	if (nfile.is_open())
	{
		string s;
		// cout<<"skip complete1"<<endl;
		for(int i=1;i<b;i++)
			getline(nfile,s);
		// cout<<"skip complete"<<endl;
		for(int i=0;i<15;i++)
		{
			double weight;
			nfile>>weight;
			// cout<<weight<<endl;
			w.push_back(weight);
		}
	}
	else 
		cerr << "Unable to open file"; 

	string outfile;
	// if (a == 1)
	// 	outfile = "input1.txt";
	// else
		outfile = "input2.txt";

	ofstream mfile (outfile);

	if (mfile.is_open())
	{
		// for(int j=0;j<100;j++)
		// {
			for(int i=0;i<15;i++) 
			{
				// double r = ((double) rand()/RAND_MAX)*100;
				mfile << w.at(i) << " ";
			}
			mfile<<endl;
		// }
	}
	else 
		mfile << "Unable to open file";
	
	return 0;
}