#ifndef CSCI2421_COMPARATOR_H
#define CSCI2421_COMPARATOR_H

#include "memory"

using namespace std;

/**
 *
 * Compares to movies by title.
 *
 * This is rudimentary implementation of the Design Pattern Strategy, a full and complete implementation
 * goes beyond the scope of this course.
 *
 * In layman's terms, The Strategy allows to generalize the algorithm to use instead of designing and coding an ADT
 * that ends up including specific details of the implementation.
 *
 * In this case, we will use a BST that relies on a comparator to compare movie objects without even referring to the
 * type movie within the BST code.
 *
 * This class then is generic and customized by usign template class.
 *
 * if you are interested in this, feel free to ask your instructor.
 */
template <class ItemType>
class Comparator {
public:

    virtual bool lessThan (const ItemType& lhs, const ItemType& rhs) noexcept(false) = 0;

    virtual bool greaterThan (const ItemType& lhs, const ItemType& rhs) noexcept(false) = 0;

    virtual bool equals (const ItemType& lhs, const ItemType& rhs) noexcept(false) = 0;
};

#endif