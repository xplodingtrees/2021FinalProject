#ifndef LIBRARY_H
#define LIBRARY_H

#include "memory"
#include "Patron.h"
#include "vector"
#include "BinarySearchTree.h"
#include "LinkedList.h"
#include "LinkedStack.h"
#include "BookComparator.h"

#include "fstream"
#include "filesystem"
#include "iostream"

using namespace std;

class Library {
private:

    shared_ptr<BinarySearchTree<shared_ptr<Book>>> bookIndex;
    shared_ptr<LinkedList<shared_ptr<Patron>>> patrons;
    shared_ptr<LinkedList<shared_ptr<Book>>> books;
    shared_ptr<LinkedList<shared_ptr<Book>>> booksUnavailable;
    shared_ptr<LinkedList<shared_ptr<Book>>> booksAvailable;
    shared_ptr<LinkedStack<shared_ptr<Book>>> dropBox;

    string name;
    string address;
    string hours;

public:
    Library();
    Library(const string &name,const string &address,const string &hours);
    ~Library();

    /**
    * Adds a book to the book list and index
    * @return list of available books
    */
    shared_ptr<LinkedList<shared_ptr<Book>>>  availableBooks();

    /**
    * Adds a book to the book list and index
    * @return list of checked books
    */
    shared_ptr<LinkedList<shared_ptr<Book>>> checkedBooks();

    /**
    * Adds a book to the book list and index
    * @return list of patrons
    */
    shared_ptr<LinkedList<shared_ptr<Patron>>> registeredPatrons();

    /**
    * Adds a book to the book list and index
    * @param searchTerm
    * @return vector of books that match the search term
    */
    vector<Book> searchBooks(string searchTerm);


    //main methods
    /**
    * Creates and adds a book to the book list and index
    * @param aBook
    * @return true if book added successfully, false if not
    */
    bool addBook(Book aBook);

    /**
    * Removes a book from the list and index
    * @param bookTitle
    * @return true if book removed successfully, false if not
    */
    bool removeBook(string bookTitle);

    /**
    * Adds a new patron to the list of registered patrons
    * @param name
    * @param address
    * @param phoneNum
    * @return true if patron was added successfully, false if not
    */
    bool addPatron(string name, string address, string phoneNum);

    /**
    * Removes a book from available books list and adds it to the list of checked out books
    * @param phoneNum
    * @param bookTitle
    * @return true if book was checked out successfully, false if not
    */
    bool checkOutBook(string phoneNum, string bookTitle);

    /**
    * Places a book on hold status
    * @param phoneNum
    * @param bookTitle
    * @return true if book set on hold successfully, false if not
    */
    bool setHold(string phoneNum, string bookTitle);

    /**
    * Places a book on returned status
    * @param bookTitle
    * @return true if book returned successfully, false if not
    */
    bool returnBook(string bookTitle);

    /**
    * If book is not on hold, it is added to the list of available books and removed from unavailable books list
    * @param
    * @return true if book was added successfully, false if not
    */
    bool checkInBook();

    /**
    * Loads library data from file
    * @param fileName
    */
    void load(string directory);

    /**
    * Saves library data to file
    * @param fileName
    */
    void save(string directory);

    //setters/getters
    string getName() const;
    string getAddress() const;
    string getHours() const;
    void setName(const string &newName);
    void setAddress(const string &newAddress);
    void setHours(const string &newHours);
};

#include "Library.cpp"

#endif //LIBRARY_H
