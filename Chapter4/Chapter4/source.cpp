#include"methods.h"
#include<iostream>

using namespace std;
void main()
{
	methods<int> solution;
	vector<int> vec{ 13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7 };
	vector<int> vec1{ -2,-4 };


	cout << solution.findMaxSumInLinearTime(vec1, 0, vec1.size());

	return;
}