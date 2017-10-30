#include"Func_declaration.h"

#include<vector>
#include<map>
#include<iostream>



std::pair<int, std::vector<int>> bestCut(int length,std::vector<int>& price)
{
	std::vector<int> result(length+1,0);
	std::vector<int> cut(length + 1, 0);
	for (int tmpLength = 1; tmpLength <= length; ++tmpLength)
	{
		for (int cutIndex = 1; cutIndex <= tmpLength; ++cutIndex)
		{
			if (result[tmpLength] < price[cutIndex] + result[tmpLength - cutIndex] - (cutIndex == tmpLength? 0:1))
			{																			
				result[tmpLength] = price[cutIndex] + result[tmpLength - cutIndex] - (cutIndex == tmpLength ? 0 : 1);
				cut[tmpLength] = cutIndex;
			}
		}
	}
	std::vector<int> sectionLength;
	while (length != 0)
	{
		sectionLength.push_back(cut[length]);
		length -= cut[length];
	}
	return std::pair<int, std::vector<int>>(result[result.size() - 1], sectionLength);
}

long long Fibonacci(int numIndex)
{
	if (numIndex == 1 || numIndex == 2)
		return 1;
	std::vector<long long> result(numIndex+1, 1);
	for (int tmpIndex = 3; tmpIndex <= numIndex; ++tmpIndex)
	{
		result[tmpIndex] = result[tmpIndex - 1] + result[tmpIndex - 2];
	}
	return result[result.size() - 1];
}

void matrixChainOrder(std::vector<int> chainScale)
{
	int matrixNum = chainScale.size() - 1;
	std::vector<std::vector<long long>> minMultiplyNum(matrixNum, std::vector<long long>(matrixNum, LLONG_MAX));
	std::vector<std::vector<int>> index(matrixNum, std::vector<int>(matrixNum, 0));
	for (int i = 0; i != matrixNum; ++i)
		minMultiplyNum[i][i] = 0;
	for (int length = 2; length <= matrixNum; ++length)
	{
		for (int i = 0; i <= matrixNum-length; ++i)
		{
			int j = length + i - 1;
			for (int k = i; k <= j - 1; ++k)
			{
				int count = minMultiplyNum[i][k] + minMultiplyNum[k + 1][j] + chainScale[i] * chainScale[k + 1] * chainScale[j + 1];
				if (count < minMultiplyNum[i][j])
				{
					minMultiplyNum[i][j] = count;
					index[i][j] = k;
				}
			}
		}
	}
	std::cout << minMultiplyNum[0][matrixNum - 1] << std::endl;
	printMatrixOrder(index, 0, matrixNum - 1);
}

void printMatrixOrder(std::vector<std::vector<int>>& index, int i, int j)
{
	if (i == j)
		std::cout << "A" << i;
	else
	{
		std::cout << "(";
		printMatrixOrder(index, i, index[i][j]);
		printMatrixOrder(index, index[i][j]+1, j);
		std::cout << ")";
	}
}

void monotoneIncreaseSubsequence(std::vector<int> sequence)
{
	std::vector<int> sequenceLength(sequence.size(), 1);
	std::vector<int> sequencePreNode(sequence.size(), 0);
	int sequenceTailIndex = 0;
	for (int index = 1; index != sequence.size(); ++index)
	{
		for (int tmp = 0; tmp != index; ++tmp)
		{
			if (sequence[tmp] < sequence[index])
			{
				if (sequenceLength[tmp] + 1>sequenceLength[index])
				{
					sequenceLength[index] = sequenceLength[tmp] + 1;
					sequencePreNode[index] = tmp;
					sequenceTailIndex = index;
				}
			}
			else
			{
				if (sequenceLength[tmp] > sequenceLength[index])
				{
					sequenceLength[index] = sequenceLength[tmp];
					sequencePreNode[index] = tmp;
					sequenceTailIndex = tmp;
				}
			}
		}
	}
	std::cout << sequenceLength[sequence.size() - 1] << std::endl;
	std::vector<int> subsequence(sequenceLength[sequence.size() - 1]);
	for (int x = subsequence.size()-1; x >= 0; --x)
	{
		subsequence[x] = sequence[sequenceTailIndex];
		sequenceTailIndex = sequencePreNode[sequenceTailIndex];
	}
	for (auto i : subsequence)
		std::cout << i << " ";
}

void optimalBST(std::vector<double> priceOfKey, std::vector<double> priceOfFakeKey)
{
	/*
	expectation[i,j] is the expectation of the BST with key nodes from Ki to K(j-1)



						priceOfKey[i]        i==j    0<=i<=n+1 && 0<=j<=n+1 
	expectation[i,j]=
						min{expectation[i,r]+expectation[r,j]+w[i,j]}     i<j   0<=i<=n+1 && 0<=j<=n+1 




	w[i,j]=sum(priceOfKey[i],......,priceOfKey[j-1])+sum(priceOfFakeKey[i],......,priceOfFakeKey[j])
		  =w[i,r]+w[r,j]-priceOfFakeKey[r]
	*/
	int keyNumber = priceOfKey.size(), fakeKeyNumber = priceOfFakeKey.size();
	if (keyNumber + 1 != fakeKeyNumber)
		return;
	std::vector<std::vector<double>> expectation(fakeKeyNumber, std::vector<double>(fakeKeyNumber, DBL_MAX));
	std::vector<std::vector<double>> w(fakeKeyNumber, std::vector<double>(fakeKeyNumber,0));
	std::vector<std::vector<int>> devidePoint(fakeKeyNumber, std::vector<int>(fakeKeyNumber));
	for (int i = 0; i != fakeKeyNumber; ++i)
	{
		expectation[i][i] = priceOfFakeKey[i];
		w[i][i] = priceOfFakeKey[i];
	}
	for (int length = 1; length != fakeKeyNumber; ++length)
	{
		for (int i = 0; i <= fakeKeyNumber - 1 - length; ++i)
		{
			int j = i + length;
			w[i][j] = w[i][j - 1] + priceOfKey[j - 1] + priceOfFakeKey[j];
			for (int r = i; r < j; ++r)
			{
				if (expectation[i][r] + expectation[r+1][j] + w[i][j] < expectation[i][j])
				{
					expectation[i][j] = expectation[i][r] + expectation[r+1][j] + w[i][j];
					devidePoint[i][j] = r;
				}
			}
		}
	}
	std::cout << expectation[0][fakeKeyNumber - 1] << std::endl;
	std::cout << "preorder:" << std::endl;
	constructOptimalBST_preorder(devidePoint, 0, fakeKeyNumber - 1);
	std::cout << std::endl << "inorder:" << std::endl;
	constructOptimalBST_inorder(devidePoint, 0, fakeKeyNumber - 1);
}

void constructOptimalBST_preorder(std::vector<std::vector<int>>& devidePoint, int i, int j)
{
	if (i == j)
	{
		std::cout << "D" << j << " ";
		return;
	}
	int root = devidePoint[i][j];
	//constructOptimalBST(devidePoint, i, root);
	std::cout << "K" << root << " ";
	constructOptimalBST_preorder(devidePoint, i, root);
	constructOptimalBST_preorder(devidePoint, root + 1, j);
}

void constructOptimalBST_inorder(std::vector<std::vector<int>>& devidePoint, int i, int j)
{
	if (i == j)
	{
		std::cout << "D" << j << " ";
		return;
	}
	int root = devidePoint[i][j];
	constructOptimalBST_inorder(devidePoint, i, root);
	std::cout << "K" << root << " ";
	constructOptimalBST_inorder(devidePoint, root + 1, j);
}

