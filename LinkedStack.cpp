#include "LinkedStack.h"

template<class ItemType>
LinkedStack<ItemType>::LinkedStack() : topPtr(nullptr){}

template<class ItemType>
LinkedStack<ItemType>::LinkedStack(const LinkedStack<ItemType> &aStack) {
    shared_ptr<Node<ItemType>> origChainPtr = aStack.topPtr; //Point to nodes in original chain

    if (origChainPtr == nullptr) //check if empty
        topPtr = nullptr; //original stack is empty
    else{
        //copy first node
        topPtr = new Node<ItemType>();
        topPtr->setItem(origChainPtr->getItem());

        Node<ItemType>* newChainPtr = topPtr; //point to last node in new chain

        origChainPtr = origChainPtr->getNext(); //advance original chain pointer

        while(origChainPtr != nullptr){ //copy remaining nodes
            ItemType nextItem = origChainPtr->getItem(); //get next item from original chain
            shared_ptr<Node<ItemType>> newNodePtr = new Node<ItemType>(nextItem); //create a new node containing the next item
            newChainPtr->setNext(newNodePtr); //link new node to end of new chain
            newChainPtr = newChainPtr->getNext(); //advance pointer to new last node
            origChainPtr = origChainPtr->getNext(); //advance original chain pointer
        }
        newChainPtr->setNext(nullptr); //flag end of chain
    }
}

template<class ItemType>
LinkedStack<ItemType>::~LinkedStack() {
    while (!isEmpty()){ //pop until stack empty
        pop();
    }
}

template<class ItemType>
bool LinkedStack<ItemType>::isEmpty() const {
    return topPtr == nullptr;
}

template<class ItemType>
bool LinkedStack<ItemType>::push(const ItemType &newEntry) {
    shared_ptr<Node<ItemType>> newNodePtr = new Node<ItemType>(newEntry, topPtr); //create new node with entry, set to top
    topPtr = newNodePtr; //set top pointer in stack to newly created node
    newNodePtr = nullptr; //set pointer to null to be safe

    return true;
}

template<class ItemType>
bool LinkedStack<ItemType>::pop() {
    if(!isEmpty()){ //validate not empty
        //stack is not empty, delete top
        shared_ptr<Node<ItemType>> nodeToDeletePtr = topPtr; //set top as node to delete
        topPtr = topPtr->getNext(); //switch head to next in chain

        //return deleted node to system
        nodeToDeletePtr->setNext(nullptr); //set next to null and delete old
        delete nodeToDeletePtr;
        nodeToDeletePtr = nullptr;

        return true;
    }
    return false;
}

template<class ItemType>
ItemType LinkedStack<ItemType>::peek() const noexcept(false) {
    if (isEmpty()) //enforce precondition
        throw(PrecondViolatedExcep("peek() called with empty stack."));
    return topPtr->getItem(); //stack is not empty, return top
}
