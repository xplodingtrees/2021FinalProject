#ifndef CSCI2421_MOVIECOMPARATOR_H
#define CSCI2421_MOVIECOMPARATOR_H

#include "memory"
#include "Book.h"
#include "Comparator.h"

using namespace std;

class BookComparator : public Comparator<shared_ptr<Book>> {
public:
    /**
     * @param lhs
     * @param rhs
     * @return  true when lhs.title < rhs.title. False otherwise.
     */
    bool lessThan(const shared_ptr<Book> &lhs, const shared_ptr<Book> &rhs) noexcept(false) override {
        if (lhs == nullptr || rhs == nullptr)
            throw logic_error("Cant compare NULLPTR");

        return lhs->getTitle() < rhs->getTitle();
    };

    /**
     * @param lhs
     * @param rhs
     * @return  true when lhs.title > rhs.title. False otherwise.
     */
    bool greaterThan(const shared_ptr<Book> &lhs, const shared_ptr<Book> &rhs) noexcept(false) override {
        if (lhs == nullptr || rhs == nullptr)
            throw logic_error("Cant compare NULLPTR");

        return lhs->getTitle() > rhs->getTitle();
    };

    /**
     * @param lhs
     * @param rhs
     * @return  true when lhs.title == rhs.title. False otherwise.
     */
    bool equals(const shared_ptr<Book> &lhs, const shared_ptr<Book> &rhs) noexcept(false) override {
        if (lhs == nullptr || rhs == nullptr)
            throw logic_error("Cant compare NULLPTR");

        return lhs->getTitle() == rhs->getTitle();
    };
};


#endif
