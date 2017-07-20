#pragma once

#include<vector>


template<typename Element>
class MyStack
{
	using size_type =typename std::vector<Element>::size_type;
public:
	MyStack() = delete;
	MyStack(size_type size) : stack(size),topOfStack(0){}
	
	bool empty()
	{
		if (topOfStack == 0)
			return true;
		else
			return false;
	}

	void push(Element newEle)
	{
		if (topOfStack != stack.size())
			stack[topOfStack++] = newEle;
		else
			cout << "The stack is full.";
	}
private:
	std::vector<Element> stack;

	size_type topOfStack;
};