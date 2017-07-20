#pragma once
#include<vector>
#include<stdlib.h>

template<typename Element>
class Solution
{
	using size_type = typename std::vector<Element>::size_type;
public:
	Element randomizedSelect(typename std::vector<Element>  vec, size_type beg, size_type end, size_type aim)
	{
		if (end - beg == 1)
			return vec[beg];
		size_type breakPoint = randomizedPartition(vec, beg, end);
		size_type lengthLeftSequence = breakPoint - beg;
		if (lengthLeftSequence == aim)
			return vec[aim];
		else if (aim < lengthLeftSequence)
			return randomizedSelect(vec, beg, breakPoint, aim);
		else
			return randomizedSelect(vec, breakPoint + 1, end, aim - lengthLeftSequence);
	}


	size_type randomizedPartition(typename std::vector<Element>& vec, size_type beg, size_type end)
	{
		size_type breakPoint = (rand() % (end - beg)) + beg;
		std::swap(vec[breakPoint], vec[end - 1]);
		size_type tmpLeft = beg, tmpRight = end - 2;
		while (true)
		{
			if (tmpLeft >= tmpRight)
			{
				if (vec[tmpLeft] >= vec[end - 1])
				{
					std::swap(vec[tmpLeft], vec[end - 1]);
					return tmpLeft;
				}
				if (vec[tmpLeft] < vec[end - 1])
				{
					std::swap(vec[tmpLeft + 1], vec[end - 1]);
					return tmpLeft + 1;
				}
			}
			else
			{
				std::swap(vec[tmpLeft], vec[tmpRight]);
			}
			while (vec[tmpLeft] < vec[end - 1] && tmpLeft != end - 2)
				++tmpLeft;
			while (vec[tmpRight] > vec[end - 1] && tmpRight != beg)
				--tmpRight;
		}
	}











	void inserationSorting(std::vector<Element>& vec, size_type beg, size_type end)
	{
		for (size_type tmp = beg; tmp != end; ++tmp)
		{
			Element tmpNum = vec[tmp];
			for (size_type point = tmp;;)
			{
				if (point == beg)
				{
					vec[point] = tmpNum;
					break;
				}
				if (vec[--point] > tmpNum)
					vec[point + 1] = vec[point];
				else
				{
					vec[point+1] = tmpNum;
					break;
				}
			}
			
		}
	}
	size_type partition(std::vector<Element>& vec, size_type beg, size_type end, Element demarcationPoint)
	{
		size_type lessThanDemacation = beg;
		for (; beg != end; ++beg)
		{
			if (vec[beg] <= demarcationPoint)
			{
				std::swap(vec[beg], vec[lessThanDemacation]);
				++lessThanDemacation;
			}
		}
		return lessThanDemacation;
	}

	Element theBestSelect(std::vector<Element> vec, size_type beg, size_type end, size_type index)
	{
		if (end - beg <= 2)		//base case for recursion
		{
			inserationSorting(vec, beg, end);
			return vec[beg+index];		//must use beg+index,because we are operating in one vector,not a new vector.
		}
		size_type medianSequenceBeg = beg;
		size_type tmpBeg = beg;
		for (; tmpBeg + 5 <= end; tmpBeg += 5)
		{
			inserationSorting(vec, tmpBeg, tmpBeg + 5);
			std::swap(vec[medianSequenceBeg++], vec[tmpBeg + 2]);
		}
		if (tmpBeg != end)
		{
			inserationSorting(vec, tmpBeg, end);
			std::swap(vec[medianSequenceBeg++], vec[tmpBeg + (end - tmpBeg) / 2]);
		}
		Element demarcationPoint = theBestSelect
			(vec, beg, medianSequenceBeg, beg + (medianSequenceBeg - beg) / 2);//recursion need base case

		size_type demarcationIndex = partition(vec, beg, end, demarcationPoint);
		if (index == demarcationIndex-beg)
			return demarcationPoint;
		else if (index < demarcationIndex - beg)
		{
			//std::vector<Element> newvec(vec.begin()+beg,)
			return theBestSelect(vec, beg, demarcationIndex, index);
		}
		else if (index>demarcationIndex - beg)
		{
			return theBestSelect(vec, demarcationIndex, end, index - (demarcationIndex - beg));
		}
	}
};

