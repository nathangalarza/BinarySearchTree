#pragma once
#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include "BinaryTreeInterface.h"
#include "BinaryNode.h"
#include "BinaryNodeTree.h"
#include "NotFoundException.h"
#include "PrecondViolatedExcep.h"

template<class ItemType>
class BinarySearchTree : public BinaryNodeTree<ItemType>
{
private:
	BinaryNode<ItemType>* rootPtr;

protected:

	BinaryNode<ItemType>* insertInorder(BinaryNode<ItemType>* subTreePtr, BinaryNode<ItemType>* newNode);

	BinaryNode<ItemType>* removeValue(BinaryNode<ItemType>* subTreePtr, const ItemType target, bool& success);

	BinaryNode<ItemType>* removeNode(BinaryNode<ItemType>* nodePtr);

	BinaryNode<ItemType>* removeLeftmostNode(BinaryNode<ItemType>* subTreePtr, ItemType& inorderSuccessor);

	BinaryNode<ItemType>* findNode(BinaryNode<ItemType>* treePtr, const ItemType& target) const;

public:

	BinarySearchTree();
	BinarySearchTree(const ItemType& rootItem);
	BinarySearchTree(const BinarySearchTree<ItemType>& tree);
	virtual ~BinarySearchTree();

	bool isEmpty() const;
	int getHeight() const;
	int getNumberOfNodes() const;
	ItemType getRootData() const throw(PrecondViolatedExcep);
	void setRootData(const ItemType& newData) const throw(PrecondViolatedExcep);
	bool add(const ItemType& newEntry);
	bool remove(const ItemType& anEntry);
	void clear();
	ItemType getEntry(const ItemType& anEntry) const
		throw (NotFoundException);
	bool contains(const ItemType& anEntry) const;

	void preorderTraverse(void visit(ItemType&)) const;
	void inorderTraverse(void visit(ItemType&)) const;
	void postorderTraverse(void visit(ItemType&)) const;

	BinarySearchTree<ItemType>& operator=(const BinarySearchTree<ItemType>& rightHandSide);
	bool operator==(const BinarySearchTree<ItemType>& aBinarySearchTree);
};

//#include "BinarySearchTree.cpp"

#endif



template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree() : rootPtr(nullptr)
{

}

template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(const ItemType& rootItem)
{
	rootPtr = new BinaryNode<ItemType>(rootItem, nullptr, nullptr);
}

template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(const BinarySearchTree<ItemType>& treePtr)
{
	rootPtr = this->copyTree(treePtr.rootPtr);
}

template<class ItemType>
BinarySearchTree<ItemType>::~BinarySearchTree()
{
	this->destroyTree(rootPtr);
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::insertInorder(BinaryNode<ItemType>* subTreePtr, BinaryNode<ItemType>* newNodePtr)
{
	if (subTreePtr == nullptr)
		return newNodePtr;
	else
	{
		if (subTreePtr->getItem() > newNodePtr->getItem())
			subTreePtr->setLeftChildPtr(insertInorder(subTreePtr->getLeftChildPtr(), newNodePtr));
		else
			subTreePtr->setRightChildPtr(insertInorder(subTreePtr->getRightChildPtr(), newNodePtr));

		return subTreePtr;
	}
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeValue(BinaryNode<ItemType>* subTreePtr, const ItemType target, bool& success)
{
	if (subTreePtr == nullptr)
	{
		success = false;
		return nullptr;
	}
	if (subTreePtr->getItem() == target)
	{
		subTreePtr = removeNode(subTreePtr);
		success = true;
		return subTreePtr;
	}
	else
	{
		if (subTreePtr->getItem() > target)
			subTreePtr->setLeftChildPtr(removeValue(
				subTreePtr->getLeftChildPtr(), target, success));
		else
			subTreePtr->setRightChildPtr(removeValue(
				subTreePtr->getRightChildPtr(), target, success));

		return subTreePtr;
	}
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeNode(BinaryNode<ItemType>* nodePtr)
{
	if (nodePtr->isLeaf())
	{
		delete nodePtr;
		nodePtr = nullptr;
		return (nodePtr);
	}
	else if (nodePtr->getLeftChildPtr() == nullptr)
	{
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getRightChildPtr();
		delete nodePtr;
		nodePtr = nullptr;
		return nodeToConnectPtr;
	}
	else if (nodePtr->getRightChildPtr() == nullptr)
	{
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getLeftChildPtr();
		delete nodePtr;
		nodePtr = nullptr;
		return nodeToConnectPtr;
	}
	else
	{
		ItemType newNodeValue;
		nodePtr->setRightChildPtr(removeLeftmostNode(nodePtr->getRightChildPtr(), newNodeValue));
		nodePtr->setItem(newNodeValue);
		return nodePtr;
	}
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType& inorderSuccessor)
{
	if (nodePtr->getLeftChildPtr() == nullptr)
	{
		inorderSuccessor = nodePtr->getItem();
		return removeNode(nodePtr);
	}
	else
	{
		nodePtr->setLeftChildPtr(removeLeftmostNode(nodePtr->getLeftChildPtr(),
			inorderSuccessor));
		return nodePtr;
	}  // end if      
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findNode(BinaryNode<ItemType>* subTreePtr, const ItemType& target) const
{
	if (subTreePtr == nullptr)
		return nullptr;
	else if (subTreePtr->getItem() == target)
		return subTreePtr;
	else if (subTreePtr->getItem() > target)
		return findNode(subTreePtr->getLeftChildPtr(), target);
	else
		return findNode(subTreePtr->getRightChildPtr(), target);
}

template<class ItemType>
bool BinarySearchTree<ItemType>::isEmpty() const
{
	return rootPtr == nullptr;
}

template<class ItemType>
int BinarySearchTree<ItemType>::getHeight() const
{
	return this->getHeightHelper(rootPtr);
}

template<class ItemType>
int BinarySearchTree<ItemType>::getNumberOfNodes() const
{
	return this->getNumberOfNodesHelper(rootPtr);
}

template<class ItemType>
void BinarySearchTree<ItemType>::clear()
{
	this->destroyTree(rootPtr);
	rootPtr = nullptr;
}

template<class ItemType>
ItemType BinarySearchTree<ItemType>::getRootData() const
{
	if (isEmpty())
		throw PrecondViolatedExcep("getRootData() called with empty tree.");
	return rootPtr->getItem();
}

template<class ItemType>
void BinarySearchTree<ItemType>::setRootData(const ItemType& newItem) const
{
	throw PrecondViolatedExcep("Cannot change root value in a BST!");
}

template<class ItemType>
bool BinarySearchTree<ItemType>::add(const ItemType& newData)
{
	BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newData);
	rootPtr = insertInorder(rootPtr, newNodePtr);

	return true;
}

template<class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType& target)
{
	bool isSuccessful = false;
	rootPtr = removeValue(rootPtr, target, isSuccessful);
	return isSuccessful;
}

template<class ItemType>
ItemType BinarySearchTree<ItemType>::getEntry(const ItemType& anEntry) const
{
	BinaryNode<ItemType>* nodeWithEntry = findNode(rootPtr, anEntry);
	if (nodeWithEntry == nullptr)
	{
		throw NotFoundException("Entry not found in tree.");
	}
	else
	{
		return nodeWithEntry->getItem();
	}
}

template<class ItemType>
bool BinarySearchTree<ItemType>::contains(const ItemType& anEntry) const
{
	return (findNode(rootPtr, anEntry) == nullptr ? false : true);
}

template<class ItemType>
void BinarySearchTree<ItemType>::preorderTraverse(void visit(ItemType&)) const
{
	this->preorder(visit, rootPtr);
}

template<class ItemType>
void BinarySearchTree<ItemType>::inorderTraverse(void visit(ItemType&)) const
{
	this->inorder(visit, rootPtr);
}

template<class ItemType>
void BinarySearchTree<ItemType>::postorderTraverse(
	void visit(ItemType&)) const
{
	this->postorder(visit, rootPtr);
}


template<class ItemType>
BinarySearchTree<ItemType>& BinarySearchTree<ItemType>::operator=(const BinarySearchTree<ItemType>& rightHandSide)
{
	if (!isEmpty())
		clear();
	this = copyTree(&rightHandSide);

	return *this;
}

template<class ItemType>
bool BinarySearchTree<ItemType>::operator==(const BinarySearchTree<ItemType>& aBinarySearchTree)
{
	if (this == aBinarySearchTree)
	{
		return true;
	}
	else
	{
		return false;
	}
}