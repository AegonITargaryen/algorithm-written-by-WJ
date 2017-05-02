#pragma once
#include<vector>

template<typename Element>
class methods
{
	using size_type = typename std::vector<Element>::size_type;


public:
	std::vector<Element>& insertionSort(std::vector<Element>& vec)
	{
		Element tmp;
		for (typename std::vector<Element>::size_type index = 1; index != vec.size(); ++index)
		{
			tmp = vec[index];
			typename std::vector<Element>::size_type point;
			for (point = index; point > 0; --point)
			{
				if (vec[point - 1] < tmp)
				{
					break;
				}
				vec[point] = vec[point - 1];
			}
			vec[point] = tmp;
		}
		return vec;
	}

	std::vector<Element>& mergeSort(std::vector<Element>& vec, size_type beg, size_type end)
	{
		if (beg+1 < end)
		{
			mergeSort(vec, beg, (beg + end) / 2);
			mergeSort(vec, (beg + end) / 2, end);
			Merge(vec, beg, (beg + end) / 2, end);
		}
		return vec;
	}





private:
	std::vector<Element>& Merge(std::vector<Element>& vec, size_type beg1, size_type beg2, size_type end)
	{
		vector<Element> tmpStore;
		size_type tmp1, tmp2;
		for (tmp1 = beg1, tmp2 = beg2; tmp1 != beg2 && tmp2 != end;)
		{
			if (vec[tmp1] <= vec[tmp2])
			{
				tmpStore.push_back(vec[tmp1++]);
			}
			else
			{
				tmpStore.push_back(vec[tmp2++]);
			}
		}
		while (tmp1 != beg2)
			tmpStore.push_back(vec[tmp1++]);
		while (tmp2 != end)
			tmpStore.push_back(vec[tmp2++]);
		copy(tmpStore.begin(), tmpStore.end(), vec.begin() + beg1);
		return vec;
	}


};

