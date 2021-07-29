#ifndef LINKEDSTACK_
#define LINKEDSTACK_

#include "StackInterface.h"
#include "Node.h"

template <class ItemType>
class LinkedStack : public StackInterface<ItemType>{
private:
    Node<ItemType> *topPtr; //pointer to first node in the chain; this node contains the stack top

public:
    //Constructors and destructor:
    LinkedStack(); //default constructor
    LinkedStack(const LinkedStack<ItemType> &aStack); //copy constructor
    virtual ~LinkedStack(); //destructor

    //stack operations:
    bool isEmpty() const;
    bool push(const ItemType &newEntry);
    bool pop();

    /** @throw PrecondViolatedExcep if the stack is empty*/
    ItemType peek() const noexcept(false);
};

#include "LinkedStack.cpp"

#endif //LINKEDSTACK_
