#ifndef BINARY_NODE_TREE_
#define BINARY_NODE_TREE_

#include "memory"
#include "BinaryTreeInterface.h"
#include "BinaryNode.h"
#include "PrecondViolatedExcep.h"
#include "NotFoundException.h"

using namespace std;

template<class ItemType>
class BinaryNodeTree : public BinaryTreeInterface<ItemType> {
private:
    shared_ptr<BinaryNode<ItemType>> rootPtr;

protected:
    //-------------------------------------------------------------------------------------------------------------------
    // Protected Utility Methods Section: Recursive helper methods for the public methods.
    //-------------------------------------------------------------------------------------------------------------------
    int getHeightHelper(shared_ptr<BinaryNode<ItemType>> subTreePtr) const;

    int getNumberOfNodesHelper(shared_ptr<BinaryNode<ItemType>> subTreePtr) const;

    /**
     * Recursively adds a new node to the tree in a left/right fashion to keep the tree balanced.
     */
    auto balancedAdd(shared_ptr<BinaryNode<ItemType>> subTreePtr, shared_ptr<BinaryNode<ItemType>> newNodePtr);

    /**
     * Copies values up the tree to overwrite value in current node until a leaf is reached; the leaf is then removed,
     * since its value is stored in the parent.
     * @param subTreePtr
     * @return
     */
    shared_ptr<BinaryNode<ItemType>> moveValuesUpTree(shared_ptr<BinaryNode<ItemType>> subTreePtr);

    /**
     * Removes the target value from the tree by calling moveValuesUpTree to overwrite value with value from child.
     * @param subTreePtr
     * @param target
     * @param success
     * @return
     */
    virtual shared_ptr<BinaryNode<ItemType>>
    removeValue(shared_ptr<BinaryNode<ItemType>> subTreePtr,
                ItemType target, bool &success);


    /**
     * Recursively searches for target value in the tree by using a preorder traversal.
     * @param treePtr
     * @param target
     * @param success
     * @return
     */
    auto findNode(shared_ptr<BinaryNode<ItemType>> treePtr,
                  const ItemType &target,
                  bool &success) const;

    /**
     * Copies the tree rooted at treePtr and returns a pointer to the copy.
     * @param oldTreeRootPtr
     * @return
     */
    shared_ptr<BinaryNode<ItemType>> copyTree(shared_ptr<BinaryNode<ItemType>> oldTreeRootPtr) const;

    /**
     * Recursively deletes all nodes from the tree
     * @param subTreePtr
     */
    void destroyTree(shared_ptr<BinaryNode<ItemType>> subTreePtr);

    // Recursive traversal helper methods:
    void preorder(void visit(ItemType &), shared_ptr<BinaryNode<ItemType>> treePtr) const;

    void inorder(void visit(ItemType &), shared_ptr<BinaryNode<ItemType>> treePtr) const;

    void postorder(void visit(ItemType &), shared_ptr<BinaryNode<ItemType>> treePtr) const;

public:
    //--------------- Constructor and Destructor Section.   ----------------------------------------------------
    BinaryNodeTree();

    explicit BinaryNodeTree(const ItemType &rootItem);

    explicit BinaryNodeTree(const ItemType &rootItem,
                            const shared_ptr<BinaryNodeTree<ItemType>> leftTreePtr,
                            const shared_ptr<BinaryNodeTree<ItemType>> rightTreePtr);

    BinaryNodeTree(const BinaryNodeTree<ItemType> &tree);

    virtual ~BinaryNodeTree();

    //-------------------------- Public BinaryTreeInterface Methods Section. ----------------------------------------
    bool isEmpty() const;

    int getHeight() const;

    int getNumberOfNodes() const;

    /**
     * @throws PrecondViolatedExcept
     */
    ItemType getRootData() const noexcept(false);

    void setRootData(const ItemType &newItem);

    bool add(const ItemType &newData); // Adds a node
    bool remove(const ItemType &target); // Removes a node
    void clear();

    /**
     * @throws PrecondViolatedExcept
     */
    ItemType getEntry(const ItemType &anEntry) const noexcept(false);

    bool contains(const ItemType &anEntry) const;

    //--------------------------  Public Traversals Section. -------------------------------
    void preorderTraverse(void visit(ItemType &)) const;

    void inorderTraverse(void visit(ItemType &)) const;

    void postorderTraverse(void visit(ItemType &)) const;

    //----------------------------------  Overloaded Operator Section. ------------------------------------------
    BinaryNodeTree &operator=(const BinaryNodeTree &rightHandSide);
};

#include "BinaryNodeTree.cpp"

#endif
