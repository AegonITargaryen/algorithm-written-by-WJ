#include<iostream>
#include<vector>

template
<typename Element>
class TreeNode
{
	template
	<typename X>friend class BinarySearchTree;
public:
	TreeNode() = delete;
	TreeNode(Element key) :
		key(key), leftChild(nullptr), rightChild(nullptr),parent(nullptr){}
	TreeNode(Element key, TreeNode<Element>* parent) :
		key(key), leftChild(nullptr), rightChild(nullptr), parent(parent){}
	~TreeNode();

	Element getKey(){ return this->key; }
private:
	TreeNode<Element>* leftChild;
	TreeNode<Element>* rightChild;
	TreeNode<Element>* parent;
	Element key;
};


template
<typename Element>
TreeNode<Element>::~TreeNode()
{
	if (leftChild != nullptr)
		delete leftChild;
	if (rightChild != nullptr)
		delete rightChild;
}


//二叉搜索树
template
<typename Element>
class BinarySearchTree
{
public:
	BinarySearchTree() :root(nullptr){}
	BinarySearchTree(Element rootKey) :root(new TreeNode<Element>(rootKey)){}
	BinarySearchTree(TreeNode<Element>* node) :root(node){ root->parent = nullptr; }
	~BinarySearchTree();

	TreeNode<Element>* insert(Element willBeInsert);            //插入元素
	std::vector<Element> inorderTraversal();					//中序遍历
	TreeNode<Element>* searchFirst(Element willBeFind);				//搜索
	TreeNode<Element>* treeMinimum();
	TreeNode<Element>* treeMaximum();							//树的最大值和最小值
	TreeNode<Element>* inorderSuccessor(Element tmpNum);		//中序遍历的后继
	TreeNode<Element>* inorderPrecursor(Element tmpNum);		//中序遍历的前驱
	void deleteNode(Element tmpNum);				//删除

private:
	TreeNode<Element>* root;
	std::vector<Element> traversal;

	void inorder(TreeNode<Element>* tmpKey);
	void del(TreeNode<Element>* willBeDelete);
	void transplant(TreeNode<Element>* willBeReplaced, TreeNode<Element>* newNode);
};

template
<typename Element>
void BinarySearchTree<Element>::transplant(TreeNode<Element>* willBeReplaced, TreeNode<Element>* newNode)
{
	if (willBeReplaced==root)
	{
		root = newNode;
	}
	else if (willBeReplaced == willBeReplaced->parent->leftChild)
	{
		willBeReplaced->parent->leftChild = newNode;
	}
	else
	{
		willBeReplaced->parent->rightChild = newNode;
	}
	if (newNode != nullptr)
	{
		newNode->parent = willBeReplaced->parent;
	}
	willBeReplaced->leftChild = willBeReplaced->rightChild = nullptr;
	delete willBeReplaced;
	/*if (newNode != nullptr)
	{
		willBeReplaced->key = newNode->key; willBeReplaced->leftChild = newNode->leftChild;
		willBeReplaced->rightChild = newNode->rightChild;
	}
	else
	{
		willBeReplaced->leftChild = willBeReplaced->rightChild = nullptr;
		if (willBeReplaced->parent->leftChild == willBeReplaced)
			willBeReplaced->parent->leftChild = nullptr;
		else
			willBeReplaced->parent->rightChild = nullptr;
		delete willBeReplaced;

	}*/

}

template
<typename Element>
void BinarySearchTree<Element>::del(TreeNode<Element>* willBeDelete)
{
	if (willBeDelete->leftChild == nullptr)
	{
		transplant(willBeDelete, willBeDelete->rightChild);
	}
	else if (willBeDelete->rightChild == nullptr)
	{
		transplant(willBeDelete, willBeDelete->leftChild);
	}
	else
	{
		TreeNode<Element>* tmpNode = willBeDelete->rightChild;
		while (tmpNode->leftChild != nullptr)
			tmpNode = tmpNode->leftChild;
		willBeDelete->key = tmpNode->key;
		transplant(tmpNode, tmpNode->rightChild);
	}
	return;
}

template
<typename Element>
void BinarySearchTree<Element>::deleteNode(Element tmpNum)
{
	TreeNode<Element>* willBeDelete = searchFirst(tmpNum);
	if (willBeDelete == nullptr)
		return;
	del(willBeDelete);
	return;
}

template
<typename Element>
TreeNode<Element>* BinarySearchTree<Element>::inorderPrecursor(Element tmpNum)
{
	TreeNode<Element>* location = searchFirst(tmpNum);
	if (location != nullptr)
	{
		if (location->leftChild != nullptr)
		{
			location = location->leftChild;
			while (location->rightChild != nullptr)
			{
				location = location->rightChild;
			}
		}
		else
		{
			TreeNode<Element>* tmp = location;
			location = location->parent;
			while (location != nullptr&&location->rightChild != tmp)
			{
				tmp = location;
				location = location->parent;
			}
		}
	}
	return location;
}

template
<typename Element>
TreeNode<Element>* BinarySearchTree<Element>::inorderSuccessor(Element tmpNum)
{
	TreeNode<Element>* location = searchFirst(tmpNum);
	if (location != nullptr)
	{
		if (location->rightChild != nullptr)
		{
			location = location->rightChild;
			while (location->leftChild != nullptr)
			{
				location = location->leftChild;
			}
		}
		else
		{
			TreeNode<Element>* tmp = location;
			location = location->parent;
			while (location != nullptr&&tmp != location->leftChild)
			{
				tmp = location;
				location = location->parent;
			}
		}
	}
	return location;
}

template
<typename Element>
TreeNode<Element>* BinarySearchTree<Element>::treeMaximum()
{
	TreeNode<Element>* tmp = root;
	if (tmp != nullptr)
	{
		while (tmp->rightChild != nullptr)
		{
			tmp = tmp->rightChild;
		}
	}
	return tmp;
}

template
<typename Element>
TreeNode<Element>* BinarySearchTree<Element>::treeMinimum()
{
	TreeNode<Element>* tmp = root;
	if (tmp != nullptr)
	{
		while (tmp->leftChild != nullptr)
		{
			tmp = tmp->leftChild;
		}
	}
	return tmp;
}

template
<typename Element>
TreeNode<Element>* BinarySearchTree<Element>::searchFirst(Element willBeFind)
{
	TreeNode<Element>* tmpLocation = root;
	while (tmpLocation != nullptr && tmpLocation->key != willBeFind)
	{
		if (tmpLocation->key >= willBeFind)
			tmpLocation = tmpLocation->leftChild;
		else
			tmpLocation = tmpLocation->rightChild;
	}
	return tmpLocation;
}

template
<typename Element>
void BinarySearchTree<Element>::inorder(TreeNode<Element>* tmpKey)
{
	if (tmpKey != nullptr)
	{
		inorder(tmpKey->leftChild);
		traversal.push_back(tmpKey->key);
		inorder(tmpKey->rightChild);
	}
	return;
}

template
<typename Element>
std::vector<Element> BinarySearchTree<Element>::inorderTraversal()
{
	traversal.empty();
	inorder(root);
	return traversal;
}

template						
<typename Element>
TreeNode<Element>* BinarySearchTree<Element>::insert(Element willBeInsert)
{
	if (root == nullptr)
	{
		root = new TreeNode<Element>(willBeInsert);
		return root;
	}
	TreeNode<Element>* preSlot = nullptr;
	TreeNode<Element>* tmpSlot = root;
	while (tmpSlot != nullptr)
	{
		preSlot = tmpSlot;
		if (tmpSlot->key >= willBeInsert)
			tmpSlot = tmpSlot->leftChild;
		else
			tmpSlot = tmpSlot->rightChild;
	}
	if (preSlot->key >= willBeInsert)
	{
		preSlot->leftChild = new TreeNode<Element>(willBeInsert, preSlot);
		return preSlot->leftChild;
	}
	else
	{
		preSlot->rightChild = new TreeNode<Element>(willBeInsert, preSlot);
		return preSlot->rightChild;
	}
}

template
<typename Element>
BinarySearchTree<Element>::~BinarySearchTree()
{
	
	delete root;
}
