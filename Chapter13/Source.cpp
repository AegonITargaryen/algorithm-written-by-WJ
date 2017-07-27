#include<iostream>
#include"redBlackTree.h"


using namespace std;
void main()
{
	vector<int> vec;
	redBlackTree<int> tree;
	tree.insert(11);
	tree.insert(2);
	tree.insert(14);
	tree.insert(15);
	tree.insert(1);
	tree.insert(7);
	tree.insert(5);
	tree.insert(8);
	tree.insert(4);
	tree.del(11);
	tree.del(14);
	
	vec = tree.inorderTraversal();
	
	for (auto i : vec)
	{
		cout << i << " ";
	}
	for (auto i : tree.nodeColour)
	{
		cout << i << " ";
	}

	return;
}