#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

int main()
{
	srand((int)time(0));

	ofstream file ("first_gen.txt");
	if (file.is_open())
	{
		for(int j=0;j<100;j++)
		{
			double r;
			// double w1 = 50;
			// double w2 = 45;
			// double w3 = 10;
			// double w4 = 9;
			// double w5 = 100000;
			// double w6 = -100000;
			// double w7 = 0.5;
			// double w8 = 0.4;
			// double w9 = 5;
			// double w10 = 5000;
			// double w11 = 5000;
			// double w12 = 50;
			// double w13 = 50;
			// double w14 = 100;
			// double w15 = 100; 
			r = ((double) rand()/RAND_MAX)*50 - 25;
			file << 50 - r << " "; //w1
			r = ((double) rand()/RAND_MAX)*50 - 25;
			file << 50 - r << " "; //w2
			r = ((double) rand()/RAND_MAX)*10 - 5;
			file << 10 - r << " "; //w3
			r = ((double) rand()/RAND_MAX)*10 - 5;
			file << 10 - r << " "; //w4
			r = ((double) rand()/RAND_MAX)*100000 - 50000;
			file << 100000 - r << " "; //w5
			r = ((double) rand()/RAND_MAX)*100000 - 50000;
			file << 100000 - r << " "; //w6
			r = ((double) rand()/RAND_MAX)*0.5 - 0.25;
			file << 0.5 - r << " "; //w7
			r = ((double) rand()/RAND_MAX)*0.5 - 0.25;
			file << 0.5 - r << " "; //w8
			r = ((double) rand()/RAND_MAX)*5 - 2.5;
			file << 5 - r << " "; //w9
			r = ((double) rand()/RAND_MAX)*5000 - 2500;
			file << 5000 - r << " "; //w10
			r = ((double) rand()/RAND_MAX)*5000 - 2500;
			file << 5000 - r << " "; //w11
			r = ((double) rand()/RAND_MAX)*50 - 25;
			file << 50 - r << " "; // w12
			r = ((double) rand()/RAND_MAX)*50 - 25;
			file << 50 - r << " "; // w13
			r = ((double) rand()/RAND_MAX)*100 - 50;
			file << 100 - r << " ";//w14
			r = ((double) rand()/RAND_MAX)*100 - 50;
			file << 100 - r << " ";// w15
			
			
			file<<endl;
		}
	}
	else 
		file << "Unable to open file";
	
	return 0;
}