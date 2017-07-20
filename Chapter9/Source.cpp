#include"Solution.h"
#include<stdlib.h>
#include<iostream>

using namespace std;
void main()
{
	Solution<int> sln;
	vector<int> vec{ 2, 6, 8, 5, 3, 4, 7, 9, 1 };
	cout << sln.theBestSelect(vec, 0, vec.size(), 4);
	
	
	return;
}