#include"Solution.h"
#include<iostream>

using namespace std;

void main()
{
	vector<int> vec{ 2, 5, 3, 0, 2, 3, 0, 3 };
	Solution sln;
	sln.CountingSort(vec, 6);
	for (auto i : vec)
	{
		cout << i << " ";
	}
	return;
}