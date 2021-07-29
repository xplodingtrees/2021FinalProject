#ifndef BOOK_H
#define BOOK_H

#include "Patron.h"
#include "Author.h"
#include "memory"
#include "LinkedList.h"
#include "LinkedQueue.h"
#include "vector"

using namespace std;

class Book {
private:
    LinkedList<shared_ptr<Author>> authors;
    LinkedQueue<shared_ptr<Patron>> patronsOnHold;

    shared_ptr<Patron> currentPatron;

    string title;
    int isbn;
    string pubDate;
    string publisher;
    int pages;
    bool isAvailable;

public:
    Book();
    Book(const string &aTitle,const int &aisbn,const string &aPubDate,const string &aPublisher,const int &aPages);
    ~Book();

    /**
    * Queues a patron on the patronOnHold queue
    * @post A patron is either added to the queue or, if the book is available, the patron is set as the current patron
    * @param aPatron The patron going on hold
    * @return returns true on a success.
    */
    bool addHold(shared_ptr<Patron> &aPatron);
    /**
    * Cycles through the queue if the book is available,
    * @pre  There should be someone on hold. Will run either way but it'd be good practice.
    * @post  The next person on hold is set as the new currentPatron and the queue is emptied by 1.
    * @return  True on a successful cycle, and false in any other situation
    */
    bool nextHold();
    /**
    * @returns If there are patrons waiting on hold, returns true. Otherwise returns false.
    */
    bool isOnHold();
    /**
    * Adds an author to the book
    * @returns True if the addition is successful and false otherwise
    */
    bool addAuthor(const shared_ptr<Author> &anAuthor);
    /**
    * Removes an author from the book
    * @returns True if the removal is successful and false otherwise (including if the author is not found)
    */
    bool removeAuthor(const shared_ptr<Author> &anAuthor);

    vector<shared_ptr<Author>> getAuthors() const;

    friend ostream& operator<<(ostream& out, const Book &book);

    //setters/getters
    string getTitle() const;
    int getIsbn() const;
    string getPubDate() const;
    string getPublisher() const;
    int getPages() const;
    bool getIsAvailable() const;
    void setTitle(const string &newTitle);
    void setIsbn(const int &newIsbn);
    void setPubDate(const string &newPubDate);
    void setPublisher(const string &newPublisher);
    void setPages(const int &newPages);
    void setIsAvailable(const bool &status);
    shared_ptr<Patron> getPatron() const;
    void setPatron(const shared_ptr<Patron> &aPatron);
};

#include "Book.cpp"

#endif //BOOK_H
