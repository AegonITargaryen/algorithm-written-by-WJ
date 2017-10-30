#ifndef FUNCDECLARATION
#define FUNCDECLARATION

#include<vector>
#include<map>
#include<algorithm>

//15.1-3
std::pair<int, std::vector<int>> bestCut(int length, std::vector<int>& price);

//15.1-5
long long Fibonacci(int numIndex);

//15.2-1
//chainScale[i] is the row number and chainScale[i+1] is the column number of the metrix Ai
void matrixChainOrder(std::vector<int> chainScale);  
void printMatrixOrder(std::vector<std::vector<int>>& index, int i, int j);

//15.4-1   15.4-2
template
<typename Element>
void longestCommonSequence(std::vector<Element> sequence1, std::vector<Element> sequence2)
{
	int length1 = sequence1.size();
	int length2 = sequence2.size();
	std::vector<std::vector<int>> length(length1 + 1, std::vector<int>(length2+1, 0));
	for (int index1 = 1; index1 <= length1; ++index1)
	{
		for (int index2 = 1; index2 <= length2; ++index2)
		{
			if (sequence1[index1 - 1] == sequence2[index2 - 1])
			{
				length[index1][index2] = length[index1 - 1][index2 - 1] + 1;
			}
			else
			{
				length[index1][index2] = std::max(length[index1 - 1][index2], length[index1][index2 - 1]);
			}
		}
	}
	std::cout << length[length1][length2] << std::endl;
	int index1 = length1, index2 = length2;
	std::vector<Element> lcsequence(length[index1][index2]);
	for (int count = length[index1][index2] - 1; count >= 0;)
	{
		int num1 = length[index1 - 1][index2 - 1], num2=length[index1][index2 - 1], num3=length[index1 - 1][index2];
		if (num1 == num2&&num2 == num3&&length[index1][index2] == num1 + 1)
		{
			lcsequence[count] = sequence1[index1 - 1];
			--index1; --index2; --count;
		}
		else if (num3 == length[index1][index2])
			--index1;
		else
			--index2;
			
	}
	for (auto i : lcsequence)
		std::cout << i << " ";
}


//15.4-4
template
<typename Element>
void longestCommonSequence_minimaizedSpace(std::vector<Element> sequence1, std::vector<Element> sequence2)
{
	if (sequence1.size() > sequence2.size())
		std::swap(sequence1, sequence2);
	int length1 = sequence1.size(), length2 = sequence2.size();
	vector<int> lcsLength(length1 + 1, 0);
	for (int row = 1; row <= length2; ++row)
	{
		int ppre = 0, pre = 0;
		for (int column = 1; column <= length1; ++column)
		{
			if (sequence1[column-1] == sequence2[row-1])
			{
				pre = ppre + 1;
				ppre = lcsLength[column];
				lcsLength[column] = pre;
			}
			else
			{
				pre = std::max(pre, lcsLength[column]);
				ppre = lcsLength[column];
				lcsLength[column] = pre;
			}
		}
	}
	std::cout << lcsLength[length1];
}


//15.4.5
void monotoneIncreaseSubsequence(std::vector<int> sequence);


//15.5-1    15.5-2

//  k0  k1  ......  k(n-1)              Key    
//d0  d1  d2  ......  dn                FakeKey

void optimalBST(std::vector<double> priceOfKey, std::vector<double> priceOfFakeKey);
void constructOptimalBST_preorder(std::vector<std::vector<int>>& devidePoint, int i, int j);
void constructOptimalBST_inorder(std::vector<std::vector<int>>& devidePoint, int i, int j);

#endif

