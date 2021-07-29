#ifndef LIBRARY_H
#define LIBRARY_H

#include "memory"
#include "Patron.h"
#include "vector"
#include "BinarySearchTree.h"
#include "LinkedList.h"
#include "LinkedStack.h"

class Library {
private:
    unique_ptr<BinarySearchTree<shared_ptr<Book>>> bookIndex;
    unique_ptr<LinkedList<shared_ptr<Patron>>> patrons;
    unique_ptr<LinkedList<shared_ptr<Book>>> books;
    unique_ptr<LinkedList<shared_ptr<Book>>> booksUnavailable;
    unique_ptr<LinkedList<shared_ptr<Book>>> booksAvailable;
    unique_ptr<LinkedStack<shared_ptr<Book>>> dropBox;

    string name;
    string address;
    string hours;

public:
    Library();
    ~Library();

    LinkedList<Book> availableBooks();
    LinkedList<Book> checkedBooks();
    LinkedList<Patron> registeredPatrons();
    vector<Book> searchBooks(string searchTerm);

    //main methods
    bool addBook(Book aBook);
    bool removeBook(string bookTitle);
    bool addPatron(string name, string address, string phoneNum);
    bool checkOutBook(string phoneNum, string bookTitle);
    bool setHold(string phoneNum, string bookTitle);
    bool returnBook(string bookTitle);
    bool checkInBook();
    void load(string fileName);
    void save(string fileName);

    //setters/getters
    string getName() const;
    string getAddress() const;
    string getHours() const;
    void setName(const string newName);
    void setAddress(const string newAddress);
    void setHours(const string newHours);
};

#include "Library.cpp"

#endif //LIBRARY_H
