#pragma once
#include<iostream>
#include<initializer_list>

template<typename Element> 
class MyDoublyLinkedlistNode;

template<typename Element>
class MyDoublyLinkedlist;



template<typename Element>
class MyDoublyLinkedlistNode
{
	template<typename X> friend class MyDoublyLinkedlist;
public:
	MyDoublyLinkedlistNode(Element nodeValue) :nodeValue(nodeValue){}

private:
	Element nodeValue;
	MyDoublyLinkedlistNode<Element>* prev = nullptr,* next = nullptr;
};

template<typename Element> 
class MyDoublyLinkedlist
{	
public:
	MyDoublyLinkedlist():header(nullptr){};
	MyDoublyLinkedlist(Element firstNodeValue) 
		:header(new MyDoublyLinkedlistNode<Element>(firstNodeValue)),length(1){}

	bool isEmpty(){ return header == nullptr; }
	MyDoublyLinkedlistNode<Element>* searchByValue(Element searchValue)
	{
		MyDoublyLinkedlistNode<Element>* tmpPoint = header;

			while (tmpPoint != nullptr)
			{
				if (tmpPoint->nodeValue == searchValue)
					break;
				else
					tmpPoint = tmpPoint->next;
			}
		return tmpPoint;
	}

	MyDoublyLinkedlistNode<Element>* insert(Element insertValue, size_t index)//insert back 
	{
		if (length == 0)
		{
			++length;
			header = new MyDoublyLinkedlistNode<Element>(insertValue);
			return header;
		}
		if (index > length)
			index = length;
		MyDoublyLinkedlistNode<Element>* tmpPoint = header;
		while (index != 1)
		{
			tmpPoint = tmpPoint->next;
			--index;
		}
		MyDoublyLinkedlistNode<Element>* trans = tmpPoint->next;
		tmpPoint->next = new MyDoublyLinkedlistNode<Element>(insertValue);
		tmpPoint->next->next = trans;
		if (trans != nullptr)
		{
			trans->prev = tmpPoint->next;
		}
		if (tmpPoint != header)
		{
			tmpPoint->next->prev = tmpPoint;
		}
		++length;
		return tmpPoint->next;
	}
	
	MyDoublyLinkedlistNode<Element>* deleteFirstValue(Element deleteValue)
	{
		MyDoublyLinkedlistNode<Element>* tmpPoint = header;
		while (!(tmpPoint == nullptr))
		{
			if (tmpPoint->nodeValue != deleteValue)
			{
				tmpPoint = tmpPoint->next;
			}
			else
			{
				if (header == tmpPoint)
				{
					MyDoublyLinkedlistNode<Element>* tmp = header;
					header = tmpPoint->next;
					delete tmp;
					--length;
					break;
				}
				MyDoublyLinkedlistNode<Element>* nextNode = tmpPoint->next;
				tmpPoint->prev->next = nextNode;
				if (nextNode != nullptr)
					nextNode->prev = tmpPoint;
				delete tmpPoint;
				tmpPoint = nextNode;
				--length;
				break;
			}
		}
		return tmpPoint;
	}

	void print()
	{
		MyDoublyLinkedlistNode<Element>* tmpPoint = header;
		while (!(tmpPoint == nullptr))
		{
			std::cout << tmpPoint->nodeValue << " ";
			tmpPoint = tmpPoint->next;
		}
		std::cout << std::endl;
	}

private:
	MyDoublyLinkedlistNode<Element>* header = nullptr;
	size_t length = 0;
};