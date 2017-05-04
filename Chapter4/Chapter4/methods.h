#pragma once
#include<vector>


template<typename Element>
class methods
{
	using size_type = typename std::vector<Element>::size_type;
public:
	
	Element findMaxSumInLinearTime(std::vector<Element>& vec, size_type beg, size_type end)
	{
		Element maxSum = vec[beg], curSum = vec[beg++];
		while (beg != end)
		{
			if (curSum <= 0)
				curSum = vec[beg++];
			else
				curSum += vec[beg++];

			if (curSum >= maxSum)
				maxSum = curSum;
		}
		return maxSum;
	}



	Element findMaxSumByDivideAndConquerMethod(std::vector<Element>& vec, size_type beg, size_type end)	
																				//divide-and-conquer method
	{																			//to get the maximum sequence
		if (end - beg <= 1)
		{
			return vec[beg];
		}
		Element leftMaxSum = 0, rightMaxSum = 0, crossMaxSum = 0, tmpSum = 0;
		size_type mid = (beg + end) / 2;
		size_type firstPoint = mid - 1, secondPoint = mid;

		leftMaxSum = findMaxSumByDivideAndConquerMethod(vec, beg, mid);
		rightMaxSum = findMaxSumByDivideAndConquerMethod(vec, mid, end);

		crossMaxSum += vec[firstPoint];
		tmpSum += vec[firstPoint];
		while (firstPoint != beg)
		{
			tmpSum += vec[--firstPoint];
			if (tmpSum > crossMaxSum)
				crossMaxSum = tmpSum;
		}
		crossMaxSum += vec[secondPoint];
		tmpSum = crossMaxSum;
		while (secondPoint != end - 1)
		{
			tmpSum += vec[++secondPoint];
			if (tmpSum > crossMaxSum)
				crossMaxSum = tmpSum;
		}

		if (leftMaxSum >= rightMaxSum&&leftMaxSum >= crossMaxSum)
			return leftMaxSum;
		else if (rightMaxSum >= leftMaxSum&&rightMaxSum >= crossMaxSum)
			return rightMaxSum;
		else
			return crossMaxSum;
	}




};

