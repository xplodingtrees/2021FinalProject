#include "iostream"
#include "BinarySearchTree.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///                              Protected Utility Methods Section
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**********************************************************************************************************************/
template<class ItemType>
auto BinarySearchTree<ItemType>::placeNode( shared_ptr<BinaryNode<ItemType>> subTreePtr,
                                            shared_ptr<BinaryNode<ItemType>> newNodePtr) {
    if (subTreePtr == nullptr)
        return newNodePtr;
    else {
        if (aComparator->greaterThan(subTreePtr->getItem(), newNodePtr->getItem()))
            subTreePtr->setLeftChildPtr(placeNode(subTreePtr->getLeftChildPtr(), newNodePtr));
        else
            subTreePtr->setRightChildPtr(placeNode(subTreePtr->getRightChildPtr(), newNodePtr));

        return subTreePtr;
    }
}

/**********************************************************************************************************************/
template<class ItemType>
shared_ptr<BinaryNode<ItemType>>
BinarySearchTree<ItemType>::removeValue(shared_ptr<BinaryNode<ItemType>> subTreePtr,
                                        const ItemType target,
                                        bool &success) {
    if (subTreePtr == nullptr) { // Not found here
        success = false;
        return subTreePtr;
    }
    if(aComparator->equals(subTreePtr->getItem(), target)) { // Item is in the root of some subtree
        subTreePtr = removeNode(subTreePtr);
        success = true;
        return subTreePtr;
    }
    else { //Not found, keep searching
        //if (subTreePtr->getItem() > target) { // Search the left subtree
        if (aComparator->greaterThan(subTreePtr->getItem(), target)) { // Search the left subtree
            subTreePtr->setLeftChildPtr(removeValue(subTreePtr->getLeftChildPtr(), target, success));
        }
        else {// Search the right subtree
            subTreePtr->setRightChildPtr(removeValue(subTreePtr->getRightChildPtr(), target, success));
        }
        return subTreePtr;
    }
}

/**********************************************************************************************************************/
template<class ItemType>
auto BinarySearchTree<ItemType>::removeNode(shared_ptr<BinaryNode<ItemType>> nodePtr) {
    /***
     * Case 1) Node is a leaf - it is deleted
     * Case 2) Node has one child - parent adopts child
     * Case 3) Node has two children:
     *              Traditional implementation: Find successor node.
     *              Alternate implementation: Find successor value and replace node's value;
     *              alternate does not need pass-by-reference
     */
    if (nodePtr->isLeaf()) {
        nodePtr.reset();
        return nodePtr; // delete and return nullptr
    }
    else if (nodePtr->getLeftChildPtr() == nullptr)  { // Has rightChild only (not a leaf)
        return nodePtr->getRightChildPtr();
    }
    else if (nodePtr->getRightChildPtr() == nullptr) { // Has left child only (not a leaf)
        return nodePtr->getLeftChildPtr();
    }
    else { // Has two children
        // Traditional way to remove a value in a node with two children
        ItemType newNodeValue;
        nodePtr->setRightChildPtr(removeLeftmostNode(nodePtr->getRightChildPtr(), newNodeValue));
        nodePtr->setItem(newNodeValue);
        return nodePtr;

        /**
         *  Alternative way to remove a value in a node with two children; does not require pass-by-reference.
         *  We need to check whether this right child has a left child.
         *  This is similar to the base case in "findSuccessorValue" but we need to remove the
         *  special case where the right child *is* the inorder successor
         */
    }
}

/**********************************************************************************************************************/
template<class ItemType>
auto BinarySearchTree<ItemType>::removeLeftmostNode(shared_ptr<BinaryNode<ItemType>> subTreePtr,
                                                         ItemType &inorderSuccessor) {
    if (subTreePtr->getLeftChildPtr() == nullptr) {
        inorderSuccessor = subTreePtr->getItem();
        return removeNode(subTreePtr);
    } else {
        subTreePtr->setLeftChildPtr(removeLeftmostNode(subTreePtr->getLeftChildPtr(), inorderSuccessor));
        return subTreePtr;
    }
}

/**********************************************************************************************************************/
// Override findNode because now we can use a binary search as the tree is ordered.
template<class ItemType>
auto BinarySearchTree<ItemType>::findNode(shared_ptr<BinaryNode<ItemType>> subTreePtr, const ItemType &target) const {
    // Uses a binary search

    if((subTreePtr == nullptr)  || (aComparator->equals(subTreePtr->getItem(), target))) // Not found OR Found (short circuit evaluation)
        return subTreePtr;
    else {
        if (aComparator->greaterThan(subTreePtr->getItem(), target))
            return findNode(subTreePtr->getLeftChildPtr(), target); // Search left subtree
        else
            return findNode(subTreePtr->getRightChildPtr(), target); // Search right subtree
    }
}




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                     PUBLIC METHODS BEGIN HERE
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///--------------------------------------------------------------------------------------
///           Constructor and Destructor Section
///--------------------------------------------------------------------------------------

/**********************************************************************************************************************/
template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(shared_ptr<Comparator<ItemType>>& aComparator) : aComparator(aComparator){};

/**********************************************************************************************************************/
template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(const ItemType &rootItem, shared_ptr<Comparator<ItemType>> aComparator)
        : rootPtr(make_shared<BinaryNode<ItemType>>(rootItem, nullptr, nullptr)),
          aComparator(aComparator) {}

/**********************************************************************************************************************/
template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(const BinarySearchTree<ItemType> &treePtr) {
    rootPtr = this->copyTree(treePtr.rootPtr); // Call inherited method
    this->aComparator = treePtr.aComparator;
}

/**********************************************************************************************************************/
template<class ItemType>
BinarySearchTree<ItemType>::~BinarySearchTree() {
    this->destroyTree(rootPtr); // Call inherited method
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///                          Public BinaryTreeInterface Methods Section
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**********************************************************************************************************************/
template<class ItemType>
bool BinarySearchTree<ItemType>::isEmpty() const {
    return rootPtr == nullptr;
}

/**********************************************************************************************************************/
template<class ItemType>
int BinarySearchTree<ItemType>::getHeight() const {
    return this->getHeightHelper(rootPtr); // Call inherited method
}

/**********************************************************************************************************************/
template<class ItemType>
int BinarySearchTree<ItemType>::getNumberOfNodes() const {
    return this->getNumberOfNodesHelper(rootPtr); // Call inherited method
}

/**********************************************************************************************************************/
template<class ItemType>
void BinarySearchTree<ItemType>::clear() {
    this->destroyTree(rootPtr); // Call inherited method
    rootPtr.reset();
}

/**********************************************************************************************************************/
/// Must override setRootData to disable its affect:
template<class ItemType>
void BinarySearchTree<ItemType>::setRootData(const ItemType &newData) const {
    throw PrecondViolatedExcep("Cannot change root value in a BST!");
}

/**********************************************************************************************************************/
template<class ItemType>
bool BinarySearchTree<ItemType>::add(const ItemType &newData) {
    auto newNodePtr = make_shared<BinaryNode<ItemType>>(newData);
    rootPtr = placeNode(rootPtr, newNodePtr);
    return true;
}

/**********************************************************************************************************************/
template<class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType &target) {
    bool isSuccessful = false;
    rootPtr = removeValue(rootPtr, target, isSuccessful);  // call may change isSuccessful
    return isSuccessful;
}

/**********************************************************************************************************************/
// Override getEntry to use our improved findNode:
template<class ItemType>
ItemType BinarySearchTree<ItemType>::getEntry(const ItemType &anEntry) const {
    shared_ptr<BinaryNode<ItemType>> nodeWithEntry = findNode(rootPtr, anEntry);
    if (nodeWithEntry == nullptr)
        throw NotFoundException("Entry not found in tree.");
    else
        return nodeWithEntry->getItem();
}

/**********************************************************************************************************************/
// Override contains to use our improved findNode:
template<class ItemType>
bool BinarySearchTree<ItemType>::contains(const ItemType &anEntry) const {

    return (findNode(rootPtr, anEntry) == nullptr);  // nullptr is same as false
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                Public Traversals Section
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**********************************************************************************************************************/
template<class ItemType>
void BinarySearchTree<ItemType>::preorderTraverse(void visit(ItemType &)) const {
    this->preorder(visit, rootPtr); // Call inherited method
}
/**********************************************************************************************************************/
template<class ItemType>
void BinarySearchTree<ItemType>::inorderTraverse(void visit(ItemType &)) const {
    this->inorder(visit, rootPtr); // Call inherited method
}

/**********************************************************************************************************************/
template<class ItemType>
void BinarySearchTree<ItemType>::postorderTraverse(void visit(ItemType &)) const {
    this->postorder(visit, rootPtr); // Call inherited method
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                       Overloaded Operator
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**********************************************************************************************************************/
template<class ItemType>
BinarySearchTree<ItemType> &BinarySearchTree<ItemType>::
operator=(const BinarySearchTree<ItemType> &rightHandSide) {
    if (!isEmpty())
        clear();
    this = copyTree(&rightHandSide); // Call inherited method

    return *this;
}

