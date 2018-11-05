#include<iostream>
#include<math.h>
using namespace std;
int main()
{
	// cout<<pow(4,2)<<endl;
	srand((int)time(0));

	int r = ((double) rand()/RAND_MAX)*12;
	cout<<r<<endl;			
	r = ((double) rand()/RAND_MAX)*12;
	cout<<r<<endl;			
	r = ((double) rand()/RAND_MAX)*12;
	cout<<r<<endl;			
	
	return 0;
}