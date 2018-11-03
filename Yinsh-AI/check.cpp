#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <bits/stdc++.h>
#include <vector>

using namespace std;

int main(int argc, char* argv[])
{
	int ax,bx,x,y,a=0;
	string astr,bstr;
	
	srand((int)time(0));

	// ifstream file ("out.txt");
	// if (file.is_open())
	// {
	// 	int x,y;
	// 	file >> ax >> bx;		
	// }
	// else 
	// 	cerr << "Unable to open file"; 

	// cerr<<"ax: "<<ax<<"bx: "<<bx<<endl;
	ifstream nfile ("output.txt");
	if (nfile.is_open())
	{
		string s;
		// cout<<"ho"<<endl;
		// cout<<"skip complete1"<<endl;
		while(!nfile.eof( ))
		{
			getline(nfile,s);
			// cout<<s<<endl;
			if (s == "YOU WIN!")
			{
				a=2;
				cerr<<"player 2 won"<<endl;
				// x = bx;
				// y = bx + 1;
				break;
			}
			else if (s == "OTHER PLAYER WINS!")	
			{
				a=1;
				cerr<<"player 1 won"<<endl;

				// x = ax;
				// y = bx + 1;
				break;
			}
		}
		// cout<<"outside"<<endl;
		if (a!=0)
		{

			getline(nfile,s);
			astr = s.substr(13,s.size() - 13);
			getline(nfile,s);
			bstr = s.substr(19,s.size() - 19);
				
		}	
	}
	else 
		cerr << "Unable to open file"; 


	vector<double> vect;
	ifstream f ("input2.txt");
	if (f.is_open())
	{
		for(int i=0;i<15;i++)
		{
			double r;
			f>>r;
			vect.push_back(r);
		}
	}
	else 
		cerr << "Unable to open file"; 

	// cerr<<"x: "<<x<<"y: "<<y<<endl;

	// string outfile;
	// if (a == 1)
	// 	outfile = "input1.txt";
	// else
	// 	outfile = "input2.txt";
	
	ofstream mfile ("final.txt",ios::app);

	if (mfile.is_open())
	{
		if (a == 2)
		{
			for(int i=0;i<15;i++)
			{
				mfile<<vect.at(i)<<" ";
			}	
			mfile<<endl;
		}
	}
	else 
		mfile << "Unable to open file";
	
	return 0;
}