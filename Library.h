#ifndef LIBRARY_H
#define LIBRARY_H

#include "memory"
#include "LinkedList.h"

using namespace std;

class Library {
private:
    string name;
    string address;
    string hours;

public:
    Library();
    ~Library();

    bool addBook(Book aBook);
    LinkedList<Book> availableBooks();

};

#include "Library.cpp"

#endif //LIBRARY_H
