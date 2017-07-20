#include"Solution.h"
#include<vector>

using namespace std;

void Solution::CountingSort(std::vector<int>& vec, int maxinum)
{
	vector<int> count(maxinum, 0), result(vec.size(), 0);
	for (int tmpNum : vec)
	{
		++count[tmpNum];
	}
	for (int index = 1; index != count.size(); ++index)
	{
		count[index] += count[index - 1];
	}
	for (int tmpNum : vec)
	{
		result[count[tmpNum]-1] = tmpNum;
		count[tmpNum] = count[tmpNum] - 1;
	}
	vec = result;
}