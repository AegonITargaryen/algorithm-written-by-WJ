#include<iostream>
#include"Tree.h"

using namespace std;
void main()
{
	BinarySearchTree<int> tree;
	tree.insert(4);
	tree.insert(2);
	tree.insert(1);
	tree.insert(3);
	tree.insert(11);
	tree.insert(10);
	tree.insert(12);
	tree.insert(7);
	tree.insert(5);
	tree.insert(8);
	tree.insert(6);
	tree.insert(9);
	tree.deleteNode(4);
	tree.deleteNode(10);
	tree.deleteNode(11);
	tree.deleteNode(7);
	tree.deleteNode(8);
	tree.deleteNode(1);
	tree.deleteNode(3);
	tree.deleteNode(6);
	tree.deleteNode(9);
	tree.deleteNode(5);
	tree.deleteNode(12);
	tree.deleteNode(2);
	tree.deleteNode(12);
	tree.insert(6);
	for (auto i : tree.inorderTraversal())
		cout << i << " ";
	return;
}