#include "RedBlackTree.h"

int main()
{
	RBTree<int> tree(26);
	tree.insert(17);
	tree.insert(41);
	tree.insert(14);
	tree.insert(21);
	tree.insert(30);
	tree.insert(47);
	tree.insert(10);
	tree.insert(16);
	tree.insert(19);
	tree.insert(23);
	tree.insert(28);
	tree.insert(38);
	tree.insert(7);
	tree.insert(12);
	tree.insert(15);
	tree.insert(20);
	tree.insert(35);
	tree.insert(39);
	tree.insert(3);
	tree.delNode(41);
	tree.preorderTraversal();
	std::cout << std::endl;
	tree.inorderTraversal();

	return 0;
}