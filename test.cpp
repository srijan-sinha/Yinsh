#include <iostream>
#include <bits/stdc++.h>
using namespace std;
void func(int& v)
{
	// cout<<"in func"<<v<<endl;
	// int s = v;
	v = v + 1;
}
int main()
{
	int v = 0;
	func(v);
	cout<<v<<endl;
	return 0;
}