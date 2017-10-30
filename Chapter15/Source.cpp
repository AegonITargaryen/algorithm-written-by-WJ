#include<iostream>
#include<vector>
#include"Func_declaration.h"
#include<algorithm>

using namespace std;
vector<int> price = { 0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30 };
vector<int> chainScale = { 5, 10, 3, 12, 5, 50, 6 };
vector<int> sequence1 = { 1, 0, 0, 1, 0, 1, 0, 1 };
vector<int> sequence2 = { 0, 1, 0, 1, 1, 0, 1, 1, 0 };

vector<int> sequence3 = { 3, 1, 4, 2, 6, 0, 8, 7, 6, 9 };
vector<int> sequence4 = { 1, 2, 4, 3,4 ,6, 7, 8, 9 };

vector<double> sequence5 = { 0.15, 0.1, 0.05, 0.1, 0.2 };
vector<double> sequence6 = { 0.05, 0.1, 0.05, 0.05, 0.05, 0.1 };


vector<double> sequence7 = { 0.04, 0.06, 0.08, 0.02, 0.1, 0.12, 0.14 };
vector<double> sequence8 = { 0.06, 0.06, 0.06, 0.06, 0.05, 0.05, 0.05, 0.05 };


int main()
{
	/*std::pair<int, std::vector<int>> result = bestCut(7, price);
	cout << result.first << endl;
	for (auto i : result.second)
		cout << i << " ";*/

	/*cout << Fibonacci(100);*/

	//matrixChainOrder(chainScale);
	
	//longestCommonSequence(price, chainScale);

	/*longestCommonSequence_minimaizedSpace(sequence1, sequence2);*/

	//monotoneIncreaseSubsequence(sequence4);

	optimalBST(sequence7, sequence8);

	return 0;
}