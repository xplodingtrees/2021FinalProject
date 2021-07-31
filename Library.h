#ifndef LIBRARY_H
#define LIBRARY_H

#include "memory"
#include "Patron.h"
#include "vector"
#include "BinarySearchTree.h"
#include "LinkedList.h"
#include "LinkedStack.h"
#include "BookComparator.h"
#include "LinkedBag.h"

#include "fstream"
#include "iostream"
#include "regex"

using namespace std;

class Library {
private:

    shared_ptr<BinarySearchTree<shared_ptr<Book>>> bookIndex;
    shared_ptr<LinkedList<shared_ptr<Patron>>> patrons;
    shared_ptr<LinkedStack<shared_ptr<Book>>> dropBox;
    shared_ptr<LinkedBag<shared_ptr<Author>>> authors;
    shared_ptr<LinkedBag<shared_ptr<Book>>> books;

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
    vector<shared_ptr<Book>>  availableBooks();

    /**
    * Adds a book to the book list and index
    * @return list of checked books
    */
    vector<shared_ptr<Book>> checkedBooks();

    /**
    * Adds a book to the book list and index
    * @return list of patrons
    */
    shared_ptr<LinkedList<shared_ptr<Patron>>> registeredPatrons();

    /**
    * Finds a list of books that match the termm's pattern
    * @param searchTerm
    * @return vector of books that match the search term
    */
    vector<shared_ptr<Book>> searchBookPattern(const string& searchTerm);

    /**
    * Finds an exact match to the book
    * @param searchTerm
    * @return pointer to the matching book or nullpointer if its not found
    */
    shared_ptr<Book> searchBookTitle(const string& searchTerm);

    /**
   * Finds an exact match to a patron
   * @param searchTerm
   * @return pointer to the matching book or nullpointer if its not found
   */
    shared_ptr<Patron> searchPatron(const string& phoneNum);

    //main methods
    /**
    * Takes a book and adds it to the library
    * @pre there should be no patrons on hold for the book when it is added.
    * @param aBook is the book to be added
    * @return true if book added successfully, false if not
    */
    bool addBook(shared_ptr<Book> &aBook);

    /**
    * Removes a book from the list and index
    * @param bookTitle
    * @return true if book removed successfully, false if not
    */
    bool removeBook(const string& bookTitle);

    /**
    * Adds a new patron to the list of registered patrons
    * @param name
    * @param address
    * @param phoneNum
    * @return true if patron was added successfully, false if not
    */
    bool addPatron(const string& name,const string& address,const string& phoneNum);

    /**
    * Removes a book from available books list and adds it to the list of checked out books, setting the book as checked out by the patrons whos phone number is given
    * @pre the book should be available before hand (not strictly required)
    * @param phoneNum patrons number
    * @param bookTitle is books title
    * @return true if book was checked out successfully, false if one of them doesn't exist or the book is on hold (or other failure reasons)
    */
    bool checkOutBook(const string& phoneNum,const string& bookTitle);

    /**
    * Places a book on hold status.
    * @pre book must not be available
    * @param phoneNum of patron
    * @param bookTitle of book
    * @return true if book set on hold successfully, false if either value is not found. Exact match required.
    */
    bool setHold(const string& phoneNum,const string& bookTitle);

    /**
    * Places a book on returned status
    * @param bookTitle
    * @return true if book returned successfully, false if not
    */
    bool returnBook(const string& bookTitle);

    /**
    * Attempts to check in a book from the drop box. If the book is on hold, it checks out the book for that individual
    * @return false if there is no book in the drop box, true on all successful other operations
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

    /**
    * Creates and returns a new author
    * @param name
    * @return returns Author pointer with new (or pre-existing author)
    */
    shared_ptr<Author> createAuthor(const string& name);

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
