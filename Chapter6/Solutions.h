#pragma once

#include<vector>
#include<iostream>

template<typename Element>
class Solution
{
public:
	using size_type =typename std::vector<Element>::size_type;

	void MaxHeapify(std::vector<Element>& vec, size_type willBeInsert)
	{
		size_type largestElementIndex;
		size_type leftChild = willBeInsert * 2 + 1;
		size_type rightChild = leftChild + 1;
		if (leftChild<vec.size() && vec[leftChild]>vec[willBeInsert])
		{
			largestElementIndex = leftChild;
		}
		else
		{
			largestElementIndex = willBeInsert;
		}
		if (rightChild<vec.size() && vec[rightChild]>vec[largestElementIndex])
		{
			largestElementIndex = rightChild;
		}
		if (largestElementIndex != willBeInsert)
		{
			std::swap(vec[largestElementIndex], vec[willBeInsert]);
			MaxHeapify(vec, largestElementIndex);
		}
		return;
	}


	void BuildMaxHeap(std::vector<Element>& vec)
	{
		for (size_type tmp = vec.size() / 2; tmp != 0;)
		{
			MaxHeapify(vec, --tmp);
		}
	}


	std::vector<Element> HeapSort(std::vector<Element>& vec)
	{
		BuildMaxHeap(vec);
		std::vector<Element> vecResult;
		while (vec.size() != 0)
		{
			std::swap(vec[0], vec[vec.size()-1]);
			vecResult.push_back(vec[vec.size()-1]);
			vec.pop_back();
			MaxHeapify(vec, 0);
		}
		return vecResult;
	}
};


