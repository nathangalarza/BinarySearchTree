#ifndef _BINARY_TREE_INTERFACE
#define _BINARY_TREE_INTERFACE

template<class ItemType>
class BinaryTreeInterface {
public:
	//virtual bool isEmpty()const = 0;
	//virtual int getHeight() const = 0;
	//virtual int getNumberofNodes()const = 0;
	//virtual ItemType getRootData()const = 0;
	//virtual ItemType setRootData(const ItemType & newData) = 0;
	virtual bool add(const ItemType & newData) = 0;
	virtual bool remove(const ItemType& data) = 0;
	virtual void clear() = 0;
	virtual ItemType getEntry(const ItemType& anEntry) const = 0;
	//virtual bool contains(const ItemType& anEntry)const = 0;
	virtual void preorderTraverse(void visit(ItemType&))const = 0;
	virtual void inorderTraverse(void visit(ItemType&))const = 0;
	virtual void postorderTraverse(void visit(ItemType&))const = 0;
};
#endif