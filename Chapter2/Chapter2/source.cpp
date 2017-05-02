#include"methods.h"
#include<vector>
#include<iostream>

using namespace std;
void main()
{
	methods<int> solution;
	vector<int> vec{ 5, 3, 8, 10, 2, 6, 7, 9 };
	solution.mergeSort(vec, 0, vec.size());
	for (auto i : vec)
		cout << i << " ";
	return;
}