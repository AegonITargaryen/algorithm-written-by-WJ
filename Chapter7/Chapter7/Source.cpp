#include"Solution.h"
#include<vector>
#include<iostream>

using namespace std;
void main()
{
	Solution<int> sln;

	vector<int> vec = { 3, 5, 9, 6, 1, 2, 4, 8, 7 };
	//vector<int> vec = { 3,3,3,3,3,3,3 };
	sln.QuickSort(vec, 0, vec.size());
	for (auto i : vec)
		cout << i << " ";

	return;
}