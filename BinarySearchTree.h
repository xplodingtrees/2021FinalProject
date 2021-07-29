#ifndef BINARY_SEARCH_TREE_
#define BINARY_SEARCH_TREE_

#include "memory"
#include "BinaryTreeInterface.h"
#include "BinaryNode.h"
#include "BinaryNodeTree.h"
#include "NotFoundException.h"
#include "PrecondViolatedExcep.h"

#include "Comparator.h"

using namespace std;


template<class ItemType>
class BinarySearchTree : public BinaryNodeTree<ItemType> {
private:
    shared_ptr<BinaryNode<ItemType>> rootPtr;
    /**
     * This object is used to compare the ItemType objects instead of comparing directly the objects stored in the
     * node. This allows us to use pointers to objects while comparing the object's data!!!
     * otherwise, we will be comparing the pointers memory address, and we don't want that.
     */

    shared_ptr<Comparator<ItemType>> aComparator;

protected:
    //-----------------------------------------------------------------------------------------------------------------
    // Protected Utility Methods Section:   Recursive helper methods for the public methods.
    //-----------------------------------------------------------------------------------------------------------------
    /**
     * Recursively finds where the given node should be placed and inserts it in a leaf at that point.
     * @param subTreePtr
     * @param newNode
     * @return
     */
    auto placeNode(shared_ptr<BinaryNode<ItemType>> subTreePtr,
                   shared_ptr<BinaryNode<ItemType>> newNode);

    /**
     * Removes the given target value from the tree while maintaining a binary search tree.
     * @param subTreePtr
     * @param target
     * @param success
     * @return
     */
    shared_ptr<BinaryNode<ItemType>> removeValue(shared_ptr<BinaryNode<ItemType>> subTreePtr,
                                                      ItemType target,
                                                      bool &success) override;

    /**
     * Removes a given node from a tree while maintaining a binary search tree.
     * @param nodePtr
     * @return
     */
    auto removeNode(shared_ptr<BinaryNode<ItemType>> nodePtr);

    /**
     * Removes the leftmost node in the left subtree of the node pointed to by nodePtr.
     * Sets inorderSuccessor to the value in this node.
     * @param subTreePtr
     * @param inorderSuccessor
     * @return a pointer to the revised subtree
     */
    auto removeLeftmostNode(shared_ptr<BinaryNode<ItemType>> subTreePtr, ItemType &inorderSuccessor);

    /**
     * Returns a pointer to the node containing the given value, or nullptr if not found.
     * @param treePtr
     * @param target
     * @return
     */
    auto findNode(shared_ptr<BinaryNode<ItemType>> treePtr,const ItemType &target) const;

public:

    explicit BinarySearchTree(shared_ptr<Comparator<ItemType>>& aComparator);

    explicit BinarySearchTree(const ItemType &rootItem, shared_ptr<Comparator<ItemType>> aComparator);

    BinarySearchTree(const BinarySearchTree<ItemType> &tree);

    virtual ~BinarySearchTree();

    //----------------------------------------------------------------------------------------------------------------
    bool isEmpty() const override;

    int getHeight() const override;

    int getNumberOfNodes() const override;

    void setRootData(const ItemType &newData) const noexcept(false) ;

    bool add(const ItemType &newData) override;

    bool remove(const ItemType &target) override;

    void clear() override;

    ItemType getEntry(const ItemType &anEntry) const noexcept(false) override;

    bool contains(const ItemType &anEntry) const override;

    //----------------------  Public Traversals Section. ------------------------------------------------------------
    void preorderTraverse(void visit(ItemType &)) const override;

    void inorderTraverse(void visit(ItemType &)) const override;

    void postorderTraverse(void visit(ItemType &)) const override;

    //---------------------------- Overloaded Operator Section. ------------------------------------------------------
    BinarySearchTree<ItemType> &operator=(const BinarySearchTree<ItemType> &rightHandSide);

};

#include "BinarySearchTree.cpp"

#endif
