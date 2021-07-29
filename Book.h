#ifndef BOOK_H
#define BOOK_H

#include "Patron.h"
#include "Author.h"
#include "memory"
#include "LinkedList.h"
#include "LinkedQueue.h"

using namespace std;

class Book {
private:
    unique_ptr<LinkedList<shared_ptr<Author>>> authors;
    unique_ptr<LinkedQueue<shared_ptr<Patron>>> patronsOnHold;

    string title;
    int isbn;
    string pubDate;
    string publisher;
    int pages;
    bool isAvailable;

public:
    Book();
    ~Book();

    bool markAvailable();
    bool markUnavailable();
    Patron getPatron();
    void setPatron(Patron aPatron);
    bool addHold(Patron aPatron);
    bool nextHold();
    bool isOnHold();

    friend ostream& operator<<(ostream& out, const Book &book);

    //setters/getters
    string getTitle();
    int getIsbn();
    string getPubDate();
    string getPublisher();
    int getPages();
    bool getIsAvailable();
    void setTitle(string newTitle);
    void setIsbn(int newIsbn);
    void setPubDate(string newPubDate);
    void setPublisher(string newPublisher);
    void setPages(int newPages);
    void setIsAvailable(bool status);
};

#include "Book.cpp"

#endif //BOOK_H
