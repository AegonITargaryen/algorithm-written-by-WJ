#include<iostream>
#include<vector>

enum Color{red,black};
template
<typename Element>
class RBTreeNode
{
	template<typename X> friend class RBTree;
public:
	RBTreeNode();
	RBTreeNode(Element val);

private:
	bool isGuard;
	Element val;
	RBTreeNode<Element>* left;
	RBTreeNode<Element>* right;
	RBTreeNode<Element>* parent;
	Color color;
};

template
<typename Element>
RBTreeNode<Element>::RBTreeNode() :isGuard(true), color(black){}

template
<typename Element>
RBTreeNode<Element>::RBTreeNode(Element val) : isGuard(false), val(val), color(red)
{
	left = new RBTreeNode<Element>();
	left->parent = this;
	right = new RBTreeNode<Element>();
	right->parent = this;
	parent = new RBTreeNode<Element>();
}

/*-----------------------------------------------------------------*/
template
<typename Element>
class RBTree
{
public:
	RBTree(Element val);

	void preorderTraversal();
	void inorderTraversal();
	void insert(Element val);
	void delNode(Element val);

private:
	RBTreeNode<Element>* root;
	void leftRotate(RBTreeNode<Element>* rotatePoint);//not change the color
	void rightRotate(RBTreeNode<Element>* rotatePoint);//not change the color
	void insertAdjust(RBTreeNode<Element>* tmpIndex);

	void replace(RBTreeNode<Element>* newNode, RBTreeNode<Element>* originalNode);
	void delAdjust(RBTreeNode<Element>* binaryColorNode);
};

template
<typename Element>
void RBTree<Element>::delAdjust(RBTreeNode<Element>* binaryColorNode)
{
	while (binaryColorNode != root&&binaryColorNode->color==black)
	{
		if (binaryColorNode->parent->left == binaryColorNode)
		{
			RBTreeNode<Element>* friendNode = binaryColorNode->parent->right;
			if (friendNode->color == red)
			{
				friendNode->color = black;
				binaryColorNode->parent->color = red;
				leftRotate(binaryColorNode->parent);
			}
			else
			{
				if (friendNode->left->color == black&&friendNode->right->color == black)
				{
					friendNode->color = red;
					binaryColorNode = binaryColorNode->parent;
				}
				else if (friendNode->left->color == red&&friendNode->right->color==black)
				{
					friendNode->color = red;
					friendNode->left->color = black;
					rightRotate(friendNode);
				}
				else if (friendNode->right->color == red)
				{
					friendNode->color = friendNode->parent->color;
					friendNode->parent->color = black;
					friendNode->right->color = black;
					leftRotate(friendNode->parent);
					binaryColorNode = root;
				}
			}
		}
		else
		{
			RBTreeNode<Element>* friendNode = binaryColorNode->parent->left;
			if (friendNode->color == red)
			{
				friendNode->color = black;
				binaryColorNode->parent->color = red;
				rightRotate(binaryColorNode->parent);
			}
			else
			{
				if (friendNode->right->color == black&&friendNode->left->color == black)
				{
					friendNode->color = red;
					binaryColorNode = binaryColorNode->parent;
				}
				else if (friendNode->right->color == red&&friendNode->left->color == black)
				{
					friendNode->color = red;
					friendNode->right->color = black;
					leftRotate(friendNode);
				}
				else if (friendNode->left->color == red)
				{
					friendNode->color = friendNode->parent->color;
					friendNode->parent->color = black;
					friendNode->left->color = black;
					rightRotate(friendNode->parent);
					binaryColorNode = root;
				}
			}
		}
	}
	binaryColorNode->color = black;
}

template
<typename Element>
void RBTree<Element>::replace(RBTreeNode<Element>* newNode, RBTreeNode<Element>* originalNode)
{
	newNode->parent = originalNode->parent;
	if (originalNode->parent->isGuard)
	{
		root = newNode;
	}
	else if (originalNode->parent->left == originalNode)
	{
		originalNode->parent->left = newNode;
	}
	else
	{
		originalNode->parent->right = newNode;
	}
	return;
}

template
<typename Element>
void RBTree<Element>::delNode(Element val)
{
	RBTreeNode<Element>* willBeDelete = root;
	RBTreeNode<Element>* willBeReplace;
	RBTreeNode<Element>* replaceNode;
	Color originalColor;

	while (!(willBeDelete->isGuard) && willBeDelete->val != val)
	{
		if (val <= willBeDelete->val)
			willBeDelete = willBeDelete->left;
		else
			willBeDelete = willBeDelete->right;
	}
	if (willBeDelete->isGuard)
		return;
	if (willBeDelete->left->isGuard)
	{
		willBeReplace = willBeDelete;
		replaceNode = willBeDelete->right;
		originalColor = willBeReplace->color;
		replace(replaceNode, willBeDelete);
		delete willBeDelete->left;
		delete willBeDelete;
	}
	else if (willBeDelete->right->isGuard)
	{
		willBeReplace = willBeDelete;
		replaceNode = willBeDelete->left;
		originalColor = willBeReplace->color;
		replace(replaceNode, willBeDelete);
		delete willBeDelete->right;
		delete willBeDelete;
	}
	else
	{
		willBeReplace = willBeDelete->right;
		while (!willBeReplace->left->isGuard)
			willBeReplace = willBeReplace->left;
		replaceNode = willBeReplace->right;
		originalColor = willBeReplace->color;
		replace(replaceNode, willBeReplace);
		replace(willBeReplace, willBeDelete);
		delete willBeReplace->left;
		willBeReplace->left = willBeDelete->left;
		willBeDelete->left->parent = willBeReplace;
		willBeReplace->right = willBeDelete->right;
		willBeDelete->right->parent = willBeReplace;
		willBeReplace->color = willBeDelete->color;
		delete willBeDelete;
	}
	if (originalColor == black)
		delAdjust(replaceNode);

}

template
<typename Element>
void RBTree<Element>::insertAdjust(RBTreeNode<Element>* tmpNode)
{
	while (tmpNode->parent->color == red)
	{
		if (tmpNode->parent->parent->left == tmpNode->parent)
		{
			RBTreeNode<Element>* uncleNode = tmpNode->parent->parent->right;
			if (uncleNode->color == red)
			{
				uncleNode->color = black;
				tmpNode->parent->color = black;
				tmpNode = tmpNode->parent->parent;
				tmpNode->color = red;
			}
			else
			{
				if (tmpNode->parent->right == tmpNode)
				{
					leftRotate(tmpNode->parent);
					tmpNode = tmpNode->left;
				}
				tmpNode->parent->color = black;
				tmpNode->parent->parent->color = red;
				rightRotate(tmpNode->parent->parent);
				tmpNode = tmpNode->parent;
			}
		}
		else
		{
			RBTreeNode<Element>* uncleNode = tmpNode->parent->parent->left;
			if (uncleNode->color == red)
			{
				uncleNode->color = black;
				tmpNode->parent->color = black;
				tmpNode = tmpNode->parent->parent;
				tmpNode->color = red;
			}
			else
			{
				if (tmpNode->parent->left == tmpNode)
				{
					rightRotate(tmpNode->parent);
					tmpNode = tmpNode->right;
				}
				tmpNode->parent->color = black;
				tmpNode->parent->parent->color = red;
				leftRotate(tmpNode->parent->parent);
				tmpNode = tmpNode->parent;
			}
		}
	}
	root->color = black;
}

template
<typename Element>
void RBTree<Element>::insert(Element val)
{
	RBTreeNode<Element>* tmpIndex = root;
	while (!(tmpIndex->isGuard))
	{
		if (tmpIndex->val >= val)
		{
			tmpIndex = tmpIndex->left;
		}
		else
		{
			tmpIndex = tmpIndex->right;
		}
	}
	if (tmpIndex == root)
	{
		delete tmpIndex->parent;
		delete tmpIndex;
		root = new RBTreeNode<Element>(val);
		root->color = black;
		tmpIndex = root;
	}
	else
	{
		RBTreeNode<Element>* tmpParent = tmpIndex->parent;
		if (tmpParent->left == tmpIndex)
		{
			delete tmpParent->left;
			tmpParent->left = new RBTreeNode<Element>(val);
			delete tmpParent->left->parent;
			tmpParent->left->parent = tmpParent;
			tmpIndex = tmpParent->left;
		}
		else
		{
			delete tmpParent->right;
			tmpParent->right = new RBTreeNode<Element>(val);
			delete tmpParent->right->parent;
			tmpParent->right->parent = tmpParent;
			tmpIndex = tmpParent->right;
		}
	}
	insertAdjust(tmpIndex);
}

template
<typename Element>
void RBTree<Element>::rightRotate(RBTreeNode<Element>* rotatePoint)
{
	RBTreeNode<Element>* newPoint = rotatePoint->left;
	if (root == rotatePoint)
		root = newPoint;
	newPoint->parent = rotatePoint->parent;
	if (!rotatePoint->parent->isGuard)
	{
		if (rotatePoint->parent->left == rotatePoint)
			rotatePoint->parent->left = newPoint;
		else
			rotatePoint->parent->right = newPoint;
	}
	newPoint->right->parent = rotatePoint;
	rotatePoint->left = newPoint->right;
	rotatePoint->parent = newPoint;
	newPoint->right = rotatePoint;
}

template
<typename Element>
void RBTree<Element>::leftRotate(RBTreeNode<Element>* rotatePoint)
{
	RBTreeNode<Element>* newPoint = rotatePoint->right;
	if (root == rotatePoint)
		root = newPoint;
	newPoint->parent = rotatePoint->parent;
	if (!rotatePoint->parent->isGuard)
	{
		if (rotatePoint->parent->left == rotatePoint)
			rotatePoint->parent->left = newPoint;
		else
			rotatePoint->parent->right = newPoint;
	}
	newPoint->left->parent = rotatePoint;
	rotatePoint->right = newPoint->left;
	rotatePoint->parent = newPoint;
	newPoint->left = rotatePoint;
}

template
<typename Element>
RBTree<Element>::RBTree(Element val)
{
	root = new RBTreeNode<Element>(val);
	root->color = black;
}

template
<typename Element>
void RBTree<Element>::inorderTraversal()
{
	std::vector<RBTreeNode<Element>*> stack;
	RBTreeNode<Element>* tmpPoint = root;
	while (true)
	{
		while (!tmpPoint->isGuard)
		{
			stack.push_back(tmpPoint);
			tmpPoint = tmpPoint->left;
		}
		if (stack.size() == 0)
			break;
		else
		{
			std::cout << stack[stack.size() - 1]->val << '(' 
				<< ((stack[stack.size() - 1]->color == black) ? '1' : '0') << ')'<<" ";
			tmpPoint = stack[stack.size() - 1]->right;
			stack.pop_back();
		}
	}
}

template
<typename Element>
void RBTree<Element>::preorderTraversal()
{
	std::vector<RBTreeNode<Element>*> stack;
	RBTreeNode<Element>* tmpPoint = root;
	while (true)
	{
		while (!tmpPoint->isGuard)
		{
			std::cout << tmpPoint->val << "(" << ((tmpPoint->color == black) ? "1" : "0") << ")" << " ";
			stack.push_back(tmpPoint);
			tmpPoint = tmpPoint->left;
		}
		if (stack.size() == 0)
			break;
		else
		{
			tmpPoint = stack[stack.size() - 1]->right;
			stack.pop_back();
		}
	}
}