#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include<vector>

using namespace std;

int main()
{
	srand((int)time(0));
	vector< vector<double> > u;
	ifstream file ("first_gen.txt");
	if (file.is_open())
	{
		while(!file.eof())
		{
			vector<double> v;
			for(int j=0;j<15;j++)
			{
				double r;
				file >> r;
				v.push_back(r); 		
			}
			u.push_back(v);
		}
	}
	else 
		cout << "Unable to open file";
	
	

	ofstream mfile ("first_gen.txt",ios::app);
	if (mfile.is_open())
	{
		for(int i=0;i<u.size();i++)
		{
			for(int j=0;j<u.at(i).size();j++)
			{
				mfile<<u.at(i).at(j)<<" ";
			}
			if (i!=u.size())
				mfile<<endl;
		}
		for(int i=0;i<u.size();i++)
		{
			for(int j=i+1;j<u.size();j++)
			{
				for(int k=0;k<15;k++)
				{
					double p = ((double) rand()/RAND_MAX)*100;
					if (p > 50)
					{
						mfile<<u.at(i).at(k)<<" ";
					}
					else 
					{
						mfile<<u.at(j).at(k)<<" ";
					}
				}
				mfile<<endl;
			
			}
		}	
	
	}
	else 
		mfile << "Unable to open file";
	
	return 0;
}