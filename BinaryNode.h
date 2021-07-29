#ifndef BINARY_NODE_
#define BINARY_NODE_

#include "memory"

using namespace std;

template<class ItemType>
class BinaryNode
{   
private:
   ItemType                         item;           // Data portion
   shared_ptr<BinaryNode<ItemType>> leftChildPtr;   // Pointer to left child
   shared_ptr<BinaryNode<ItemType>> rightChildPtr;  // Pointer to right child

public:
   explicit BinaryNode();
   explicit BinaryNode(const ItemType& anItem);
   BinaryNode(const ItemType& anItem,
              shared_ptr<BinaryNode<ItemType>> leftPtr,
              shared_ptr<BinaryNode<ItemType>> rightPtr);

   void setItem(const ItemType& anItem);
   ItemType getItem() const;
   
   bool isLeaf() const;

   auto getLeftChildPtr() const;
   auto getRightChildPtr() const;
   
   void setLeftChildPtr(shared_ptr<BinaryNode<ItemType>> leftPtr);
   void setRightChildPtr(shared_ptr<BinaryNode<ItemType>> rightPtr);
};

#include "BinaryNode.cpp"

#endif 
