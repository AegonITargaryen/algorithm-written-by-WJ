#include<vector>

enum Colour{red,black};

template
<typename Element>
class redBlackTreeNode
{
	template<typename X> friend class redBlackTree;
public:
	redBlackTreeNode() = delete;
	redBlackTreeNode(Element key) 
		:key(key), left(nullptr), right(nullptr), nodeColour(black), parent(nullptr){}

	~redBlackTreeNode();

private:
	Colour nodeColour;
	Element key;
	redBlackTreeNode<Element>* left;
	redBlackTreeNode<Element>* right;
	redBlackTreeNode<Element>* parent;
};

template
<typename Element>
redBlackTreeNode<Element>::~redBlackTreeNode()
{
	delete left;
	delete right;
	if (parent != nullptr)
	{
		if (parent->left == this)
			parent->left == nullptr;
		else
			parent->right == nullptr;
	}
}

template
<typename Element>
class redBlackTree
{
public:
	redBlackTree() :root(nullptr){}
	redBlackTree(redBlackTreeNode<Element>* tmpNode) :root(tmpNode)
	{
		if (tmpNode->parent != nullptr)
		{
			if (tmpNode->parent->left == tmpNode)
				tmpNode->parent->left == nullptr;
			else
				tmpNode->parent->right == nullptr;
			tmpNode->parent = nullptr;
		}
	}
	~redBlackTree();

	std::vector<Element> inorderTraversal();
	redBlackTreeNode<Element>* findFirst(Element key);
	redBlackTreeNode<Element>* leftRotate(redBlackTreeNode<Element>* willBeRotate);
	redBlackTreeNode<Element>* rightRotate(redBlackTreeNode<Element>* willBeRotate);
	redBlackTreeNode<Element>* insert(Element key);
	void del(Element key);

	std::vector<bool> nodeColour;
private:
	void inorder(redBlackTreeNode<Element>* tmpPoint);

	void insertFixUp(redBlackTreeNode<Element>* tmpPoint);

	void transplant(redBlackTreeNode<Element>* tmpPoint, redBlackTreeNode<Element>* newPoint);
	void deleteFixUp(redBlackTreeNode<Element>* willBeAdjusted,
					redBlackTreeNode<Element>* willBeAdjustedNodeParent);


	redBlackTreeNode<Element>* root;
	std::vector<Element> keyList;
	
};

template
<typename Element>
void redBlackTree<Element>::deleteFixUp(redBlackTreeNode<Element>* willBeAdjusted,
										redBlackTreeNode<Element>* willBeAdjustedNodeParent)
{
	while (root != willBeAdjusted && (willBeAdjusted == nullptr || willBeAdjusted->nodeColour == black))
	{
		if (willBeAdjustedNodeParent->left == willBeAdjusted)
		{
			redBlackTreeNode<Element>* willBeAdjustedNodeBrother = willBeAdjustedNodeParent->right;
			if (willBeAdjustedNodeBrother->nodeColour == red)
			{
				willBeAdjustedNodeBrother->nodeColour = black;
				willBeAdjustedNodeParent->nodeColour = red;
				leftRotate(willBeAdjustedNodeParent);
				willBeAdjustedNodeBrother = willBeAdjustedNodeParent->right;
			}
			if (willBeAdjustedNodeBrother->nodeColour == black &&
				(willBeAdjustedNodeBrother->left == nullptr || willBeAdjustedNodeBrother->left->nodeColour == black) &&
				(willBeAdjustedNodeBrother->right == nullptr || willBeAdjustedNodeBrother->right->nodeColour == black))
			{
				willBeAdjustedNodeBrother->nodeColour = red;
				willBeAdjusted = willBeAdjustedNodeParent;
				willBeAdjustedNodeParent = willBeAdjusted->parent;
			}
			else if (willBeAdjustedNodeBrother->left != nullptr&&
				willBeAdjustedNodeBrother->left->nodeColour == red)
			{
				willBeAdjustedNodeBrother->nodeColour = red;
				willBeAdjustedNodeBrother->left->nodeColour = black;
				rightRotate(willBeAdjustedNodeBrother);
				willBeAdjustedNodeBrother = willBeAdjustedNodeParent->right;
			}
			else if (willBeAdjustedNodeBrother->right!=nullptr&&
						willBeAdjustedNodeBrother->right->nodeColour==red)
			{
				willBeAdjustedNodeBrother->nodeColour = willBeAdjustedNodeParent->nodeColour;
				willBeAdjustedNodeBrother->right->nodeColour = black;
				willBeAdjustedNodeParent->nodeColour = black;
				leftRotate(willBeAdjustedNodeParent);
				willBeAdjusted = root;
			}
		}
		else
		{
			redBlackTreeNode<Element>* willBeAdjustedNodeBrother = willBeAdjustedNodeParent->left;
			if (willBeAdjustedNodeBrother->nodeColour == red)
			{
				willBeAdjustedNodeBrother->nodeColour = black;
				willBeAdjustedNodeParent->nodeColour = red;
				rightRotate(willBeAdjustedNodeParent);
				willBeAdjustedNodeBrother = willBeAdjustedNodeParent->left;
			}
			if (willBeAdjustedNodeBrother->nodeColour == black &&
				(willBeAdjustedNodeBrother->right == nullptr || willBeAdjustedNodeBrother->right->nodeColour == black) &&
				(willBeAdjustedNodeBrother->left == nullptr || willBeAdjustedNodeBrother->left->nodeColour == black))
			{
				willBeAdjustedNodeBrother->nodeColour = red;
				willBeAdjusted = willBeAdjustedNodeParent;
				willBeAdjustedNodeParent = willBeAdjusted->parent;
			}
			else if (willBeAdjustedNodeBrother->right != nullptr&&
				willBeAdjustedNodeBrother->right->nodeColour == red)
			{
				willBeAdjustedNodeBrother->nodeColour = red;
				willBeAdjustedNodeBrother->right->nodeColour = black;
				leftRotate(willBeAdjustedNodeBrother);
				willBeAdjustedNodeBrother = willBeAdjustedNodeParent->left;
			}
			else if (willBeAdjustedNodeBrother->left != nullptr&&
				willBeAdjustedNodeBrother->left->nodeColour == red)
			{
				willBeAdjustedNodeBrother->nodeColour = willBeAdjustedNodeParent->nodeColour;
				willBeAdjustedNodeBrother->left->nodeColour = black;
				willBeAdjustedNodeParent->nodeColour = black;
				rightRotate(willBeAdjustedNodeParent);
				willBeAdjusted = root;
			}
		}
	}
	if (willBeAdjusted != nullptr)
		willBeAdjusted->nodeColour = black;
}

template
<typename Element>
void redBlackTree<Element>::del(Element key)
{
	redBlackTreeNode<Element>* willBeDelete = root;
	while (willBeDelete != nullptr)
	{
		if (willBeDelete->key == key)
			break;
		else if (key <= willBeDelete->key)
			willBeDelete = willBeDelete->left;
		else
			willBeDelete = willBeDelete->right;
	}
	if (willBeDelete == nullptr)
		return;
	
	redBlackTreeNode<Element>* willBeMove = willBeDelete;
	Colour originalColour = willBeMove->nodeColour;


	redBlackTreeNode<Element>* mayBeAdjusted;
	redBlackTreeNode<Element>* mayBeAdjustedNodeParent;	//if mayBeAdjusted is nullptr,we can't find its parent.
														//so we use this pointer variable.

	if (willBeDelete->left == nullptr)
	{
		mayBeAdjusted = willBeDelete->right;

		transplant(willBeDelete, mayBeAdjusted);
		mayBeAdjustedNodeParent = willBeDelete->parent;

		willBeDelete->left = willBeDelete->right = nullptr;
		delete willBeDelete;
	}
	else if (willBeDelete->right == nullptr)
	{
		mayBeAdjusted = willBeDelete->left;
		transplant(willBeDelete, mayBeAdjusted);
		mayBeAdjustedNodeParent = willBeDelete->parent;

		willBeDelete->right = willBeDelete->left = nullptr;
		delete willBeDelete;
	}
	else
	{
		willBeMove = willBeDelete->right;
		while (willBeMove->left != nullptr)
			willBeMove = willBeMove->left;

		originalColour = willBeMove->nodeColour;
		mayBeAdjusted = willBeMove->right;
		if (willBeDelete == willBeMove->parent)
		{
			mayBeAdjustedNodeParent = willBeMove;
		}
		else
		{
			transplant(willBeMove, willBeMove->right);
			willBeMove->right = willBeDelete->right;
			mayBeAdjustedNodeParent = willBeMove->parent;
		}
		transplant(willBeDelete, willBeMove);
		willBeMove->left = willBeDelete->left;
		if (willBeDelete->left != nullptr)
			willBeDelete->left->parent = willBeMove;
		willBeMove->nodeColour = willBeDelete->nodeColour;
		willBeDelete->left = willBeDelete->right = nullptr;
		delete willBeDelete;
	}
	if (originalColour == black)
		deleteFixUp(mayBeAdjusted, mayBeAdjustedNodeParent);
	return;
}

template
<typename Element>
void redBlackTree<Element>::transplant(redBlackTreeNode<Element>* tmpPoint,
										redBlackTreeNode<Element>* newPoint)
{
	if (root == tmpPoint)
		root = newPoint;
	else if (tmpPoint->parent->left == tmpPoint)
		tmpPoint->parent->left = newPoint;
	else
		tmpPoint->parent->right = newPoint;
	if (newPoint != nullptr)
		newPoint->parent = tmpPoint->parent;
	return;
}

template
<typename Element>
void redBlackTree<Element>::insertFixUp(redBlackTreeNode<Element>* tmpPoint)
{
	while (tmpPoint->parent!=nullptr&&tmpPoint->parent->nodeColour == red)
	{
		/*if (tmpPoint == root)
		{
			tmpPoint->nodeColour = black;
			return;
		}*/
		if (tmpPoint->parent == tmpPoint->parent->parent->left)
		{
			redBlackTreeNode<Element>* uncle = tmpPoint->parent->parent->right;
			if (uncle != nullptr&&uncle->nodeColour == red)
			{
				uncle->nodeColour = black;
				tmpPoint->parent->nodeColour = black;
				tmpPoint->parent->parent->nodeColour = red;
				tmpPoint = tmpPoint->parent->parent;
			}
			else
			{
				if (tmpPoint->parent->right == tmpPoint)
				{
					tmpPoint = tmpPoint->parent;
					leftRotate(tmpPoint);
				}
				tmpPoint->parent->nodeColour = black;
				tmpPoint->parent->parent->nodeColour = red;
				rightRotate(tmpPoint->parent->parent);
			}
		}
		else
		{
			redBlackTreeNode<Element>* uncle = tmpPoint->parent->parent->left;
			if (uncle != nullptr&&uncle->nodeColour == red)
			{
				uncle->nodeColour = black;
				tmpPoint->parent->nodeColour = black;
				tmpPoint->parent->parent->nodeColour = red;
				tmpPoint = tmpPoint->parent->parent;
			}
			else
			{
				if (tmpPoint->parent->left == tmpPoint)
				{
					tmpPoint = tmpPoint->parent;
					rightRotate(tmpPoint);
				}
				tmpPoint->parent->nodeColour = black;
				tmpPoint->parent->parent->nodeColour = red;
				leftRotate(tmpPoint->parent->parent);
			}
		}
		root->nodeColour = black;
	}
	root->nodeColour = black;
	return;
}

template
<typename Element>
redBlackTreeNode<Element>* redBlackTree<Element>::insert(Element key)
{
	if (root == nullptr)
	{
		root = new redBlackTreeNode<Element>(key);
		return root;
	}
	redBlackTreeNode<Element>* tmpParent = nullptr;
	redBlackTreeNode<Element>* tmpLocation = root;
	while (tmpLocation != nullptr)
	{
		tmpParent = tmpLocation;
		if (key <= tmpLocation->key)
			tmpLocation = tmpLocation->left;
		else
			tmpLocation = tmpLocation->right;
	}
	if (key <= tmpParent->key)
	{
		tmpParent->left = new redBlackTreeNode<Element>(key);
		tmpParent->left->nodeColour = red;
		tmpParent->left->parent = tmpParent;
		insertFixUp(tmpParent->left);
	}
	else
	{
		tmpParent->right = new redBlackTreeNode<Element>(key);
		tmpParent->right->nodeColour = red;
		tmpParent->right->parent = tmpParent;
		insertFixUp(tmpParent->right);
	}
	
}

template
<typename Element>
redBlackTreeNode<Element>* redBlackTree<Element>::rightRotate(redBlackTreeNode<Element>* willBeRotate)
{
	//redBlackTreeNode<Element>* willBeRotate = findFirst(key);
	if (willBeRotate == nullptr)
		return willBeRotate;
	redBlackTreeNode<Element>* relatedNode = willBeRotate->left;
	if (relatedNode == nullptr)
		return willBeRotate;
	willBeRotate->left = relatedNode->right;
	if (relatedNode->right != nullptr)
		relatedNode->right->parent = willBeRotate;

	relatedNode->parent = willBeRotate->parent;
	if (willBeRotate->parent == nullptr)
		root = relatedNode;
	else if (willBeRotate->parent->left == willBeRotate)
		willBeRotate->parent->left = relatedNode;
	else
		willBeRotate->parent->right = relatedNode;

	relatedNode->right = willBeRotate;
	willBeRotate->parent = relatedNode;
	return willBeRotate;
}

template
<typename Element>
redBlackTreeNode<Element>* redBlackTree<Element>::leftRotate(redBlackTreeNode<Element>* willBeRotate)
{
	//redBlackTreeNode<Element>* willBeRotate = findFirst(key);
	if (willBeRotate == nullptr)
		return willBeRotate;
	redBlackTreeNode<Element>* rightNode = willBeRotate->right;
	if (rightNode == nullptr)
		return willBeRotate;
	willBeRotate->right = rightNode->left;
	if (rightNode->left != nullptr)
		rightNode->left->parent = willBeRotate;
	
	rightNode->parent = willBeRotate->parent;
	if (willBeRotate->parent == nullptr)
		root = rightNode;
	else if (willBeRotate->parent->left == willBeRotate)
		willBeRotate->parent->left = rightNode;
	else
		willBeRotate->parent->right = rightNode;

	rightNode->left = willBeRotate;
	willBeRotate->parent = rightNode;
	return willBeRotate;
}

template
<typename Element>
redBlackTree<Element>::~redBlackTree()
{
	delete root;
}

template
<typename Element>
std::vector<Element> redBlackTree<Element>::inorderTraversal()
{
	keyList.clear();
	inorder(root);
	return keyList;
}

template
<typename Element>
void redBlackTree<Element>::inorder(redBlackTreeNode<Element>* tmpPoint)
{
	if (tmpPoint != nullptr)
	{
		inorder(tmpPoint->left);
		keyList.push_back(tmpPoint->key);
		if (tmpPoint->nodeColour==red)
		{
			nodeColour.push_back(true);
		}
		else
		{
			nodeColour.push_back(false);
		}
		inorder(tmpPoint->right);
	}
	return;
}

template
<typename Element>
redBlackTreeNode<Element>* redBlackTree<Element>::findFirst(Element key)
{
	redBlackTreeNode<Element>* tmpPoint = root;
	while (tmpPoint != nullptr)
	{
		if (tmpPoint->key == key)
			break;
		else if (key < tmpPoint->key)
			tmpPoint = tmpPoint->left;
		else
			tmpPoint = tmpPoint->right;
	}
	return tmpPoint;
}