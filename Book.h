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
    string getTitle() const;
    int getIsbn() const;
    string getPubDate() const;
    string getPublisher() const;
    int getPages() const;
    bool getIsAvailable() const;
    void setTitle(const string newTitle);
    void setIsbn(const int newIsbn);
    void setPubDate(const string newPubDate);
    void setPublisher(const string newPublisher);
    void setPages(const int newPages);
    void setIsAvailable(const bool status);
};

#include "Book.cpp"

#endif //BOOK_H
