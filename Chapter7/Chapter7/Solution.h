#pragma once

#include<vector>

template<typename Element>
class Solution
{
public:
	using size_type =typename std::vector<Element>::size_type;
	void QuickSort(std::vector<Element>& vec,size_type beg,size_type end)
	{
		if (end - beg > 1)
		{
			size_type demarcation = QuickSortDevide(vec, beg, end);
			QuickSort(vec, beg, demarcation);
			QuickSort(vec, ++demarcation, end);
		}
	}


	size_type QuickSortDevide(std::vector<Element>& vec, size_type beg, size_type end)
	{
		Element demarcationPoint;
		if (vec[beg] > vec[beg + (end - beg) / 2])
			std::swap(vec[beg], vec[beg + (end - beg) / 2]);
		if (vec[beg] > vec[end - 1])
			std::swap(vec[beg], vec[end - 1]);
		if (vec[beg + (end - beg) / 2] > vec[end - 1])
			std::swap(vec[beg + (end - beg) / 2], vec[end - 1]);

		std::swap(vec[beg + (end - beg) / 2], vec[end - 1]);
		demarcationPoint = vec[end - 1];					//choose the demarcation point.

		size_type leftPoint = beg, rightPoint = end - 2;	
		if (leftPoint == rightPoint)
			return ++leftPoint;								//if only two numbers in the sequence,
															//the sequence has already been sorted.
		
		while (leftPoint < rightPoint)
		{
			while (vec[leftPoint] < demarcationPoint)
				++leftPoint;
			while (rightPoint>beg&&vec[rightPoint] > demarcationPoint)
				--rightPoint;
			if (leftPoint < rightPoint)
				std::swap(vec[leftPoint++], vec[rightPoint--]);//prevent the situation that
																//every number is equal.
			
		}
		std::swap(vec[leftPoint], vec[end-1]);
		return leftPoint;

	}
};